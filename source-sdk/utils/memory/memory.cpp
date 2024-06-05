#include "memory.hpp"
#include <exception>
#include <Windows.h>
#include <utility>

#include "../format/format.hpp"
#include "../constants/const.hpp"
#include "../debug/debug.hpp"

uintptr_t utils::memory::GetModule(const std::string& moduleName)
{
	if (modules.contains(moduleName))
		return modules.at(moduleName);

	// We haven't called for that module yet, let's grab it
	uintptr_t moduleAddress = reinterpret_cast<uintptr_t>(GetModuleHandleA(moduleName.data()));
	if (!moduleAddress)
		LOG(DebugLevel::ERR, "Failed to grab module {}!", moduleName);

	modules.try_emplace(moduleName, moduleAddress);
	return moduleAddress;
}

int utils::memory::GetIndex(uintptr_t base, uintptr_t address)
{
	return (static_cast<int>((address - base))) / utils::consts::pointerSize;
}

uintptr_t utils::memory::GetAddress(uintptr_t base, int index)
{
	return (*reinterpret_cast<uintptr_t**>(base)[index]);
}

template<typename Return>
Return utils::memory::CallVirtualFunction(uintptr_t base, int index, auto&&... args)
{
	using Function = Return(__thiscall*)(void*, decltype(args)...);
	Function function = reinterpret_cast<Function>(*reinterpret_cast<void**>(base)[index]);
	return function(reinterpret_cast<void*>(base), std::forward<decltype(args)>(args)...);
}