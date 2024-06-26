// Set this to 1 to dump netvars and clientclass ids into files stored in the game directory
#define DUMP 0

#include "netvar.hpp"
#include "../structures/clientclass.hpp"
#include "../../../utils/debug/debug.hpp"
#include "../../interfaces/interfaces.hpp"

#include <fstream>
#include <format>

void sdk::netvars::Initialize()
{
#if DUMP
	std::unordered_map<std::string_view, std::unordered_map<std::string_view, uintptr_t>> loggedCache;
#endif

	// Loop through all the classes
	ClientClass* cClass = sdk::interfaces::client->GetAllClasses();

#if DUMP 
	std::ofstream client_ids("client_ids.txt");
	client_ids << "enum class ClassIDS : int {\n";
#endif

	while (cClass != nullptr) {
#if DUMP 
		client_ids << '\t' << cClass->networkName << " = " << static_cast<int>(cClass->classId) << ",\n";
#endif

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
#if DUMP
					loggedCache[table->tableName][extraProp.varName] = offset + extraProp.offset;
					//	LOG(DebugLevel::OK, "Got an \"internal\" prop, from the table {} and prop {}, with the name {} and an offset of {} ({})",
					//		table->tableName, prop.varName, extraProp.varName, extraProp.offset, offset + extraProp.offset);
#endif
				}
			}

			// Again, don't cache if we don't care about them (at this point, every member of baseclass, localdata, etc.. has been cached above)
			if (std::string_view(prop.varName).find("m_") == std::string::npos)
				continue;

			// Cache them
			offsetMap[utils::hash::fnv1a::hash32(table->tableName)][utils::hash::fnv1a::hash32(prop.varName)] = prop.offset;

#if DUMP
			loggedCache[table->tableName][prop.varName] = prop.offset;
			//LOG(DebugLevel::OK, "Got a prop from the table {} with the name {} and an offset of {}!", table->tableName, prop.varName, prop.offset);
#endif
		}
		cClass = cClass->next;
	}

	LOG(DebugLevel::OK, "Initialized netvars!");

#if DUMP 
	client_ids << "};";

	client_ids.close();

	std::ofstream netvar_dump("netvar_dump.txt");

	for (auto& [table, props] : loggedCache) {
		netvar_dump << std::format("{}\n    ", table);
		for (auto& [propName, offset] : props) {
			netvar_dump << std::format("[{}] - 0x{:x}\n    ", propName, offset);
		}
		netvar_dump << "\n\n";
	}

	netvar_dump.close();
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

