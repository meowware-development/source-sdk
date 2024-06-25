#define LOG_TO_FILE 0 // Set this to 1, if you want to log the netvar dump into a file called "netvar_dump.txt"

#include "netvar.hpp"
#include "../structures/clientclass.hpp"
#include "../../../utils/debug/debug.hpp"
#include "../../interfaces/interfaces.hpp"

#include <fstream>
#include <format>

void sdk::netvars::Initialize()
{
#if LOG_TO_FILE
	// This is not too clean, but this is the easiest way to do it.
	std::unordered_map<std::string_view, std::unordered_map<std::string_view, uintptr_t>> loggedCache;
#endif

	// Loop through all the classes
	ClientClass* cClass = sdk::interfaces::client->GetAllClasses();

	while (cClass != nullptr) {
		RecvTable* table = cClass->table;

		for (int i = 0; i < table->propCount; i++) {
			RecvProp prop = table->props[i];

			if (prop.type == DPT_DataTable) {
				int offset = prop.offset;
				RecvTable* dataTable = prop.dataTable;
				for (int k = 0; k < dataTable->propCount; k++) {
					RecvProp extraProp = dataTable->props[k];
					// Don't cache, if we don't care about it.
					if (std::string_view(extraProp.varName).find("m_") == std::string::npos)
						continue;

					offsetMap[utils::hash::fnv1a::hash32(table->tableName)][utils::hash::fnv1a::hash32(extraProp.varName)] = offset + extraProp.offset;
#if LOG_TO_FILE
					loggedCache[table->tableName][extraProp.varName] = offset + extraProp.offset;
					LOG(DebugLevel::OK, "Got an \"internal\" prop, from the table {} and prop {}, with the name {} and an offset of {} ({})",
						table->tableName, prop.varName, extraProp.varName, extraProp.offset, offset + extraProp.offset);
#endif
				}
			}

			// Again, don't cache if we don't care about them (at this point, every member of baseclass, localdata, etc.. has been cached above)
			if (std::string_view(prop.varName).find("m_") == std::string::npos)
				continue;

			// Cache them
			offsetMap[utils::hash::fnv1a::hash32(table->tableName)][utils::hash::fnv1a::hash32(prop.varName)] = prop.offset;

#if LOG_TO_FILE
			loggedCache[table->tableName][prop.varName] = prop.offset;
			LOG(DebugLevel::OK, "Got a prop from the table {} with the name {} and an offset of {}!", table->tableName, prop.varName, prop.offset);
#endif
		}
		cClass = cClass->next;
	}

	LOG(DebugLevel::OK, "Initialized netvars!");

#if LOG_TO_FILE 
	std::ofstream dump("netvar_dump.txt");

	for (auto& [table, props] : loggedCache) {
		dump << std::format("{}\n    ", table);
		for (auto& [propName, offset] : props) {
			dump << std::format("[{}] - 0x{:x}\n    ", propName, offset);
		}
		dump << "\n\n";
	}

	dump.close();
#endif
}

int sdk::netvars::GetOffset(uint32_t table, uint32_t prop)
{
	if (!offsetMap.contains(table))
		throw std::runtime_error(std::format("{} table doesn't exist!", table));

	if (!offsetMap[table].contains(prop))
		throw std::runtime_error(std::format("{} table doesn't contain prop {}!", table, prop));

	return offsetMap[table][prop];
}

std::unordered_map<uint32_t, int>& sdk::netvars::GetTable(const char* tableName)
{
	return offsetMap[utils::hash::fnv1a::hash32(tableName)];
}

