#pragma once
#include "recvprop.hpp"
#include "recvtable.hpp"

#include "../../../utils/hash/fnv1a.hpp"

#include <unordered_map>
#include <string_view>

namespace sdk {
	namespace netvars {
		void Initialize();

		// Multi level map.
		// Primary key is the prop table
		// Secondary map's key is the field name
		// Value is the offset
		inline std::unordered_map<uint32_t, std::unordered_map<uint32_t, int>> offsetMap;

		int GetOffset(uint32_t table, uint32_t prop);
		std::unordered_map<uint32_t, int>& GetTable(const char* tableName);
	}
}

#define NETVAR(type, name, tableName, propName) type& Get##name() { \
	static int offset = sdk::netvars::GetOffset(utils::hash::fnv1a::hash32(tableName), utils::hash::fnv1a::hash32(propName)); \
	return *reinterpret_cast<type*>(uintptr_t(this) + offset); \
}

#define OFFSET(type, name, base, off) type& Get##name() { \
	static int offset = base + off; \
	return *reinterpret_cast<type*>(uintptr_t(this) + offset); \
}