#pragma once
#include <string>
#include <unordered_map>

namespace utils::memory {
	__forceinline uintptr_t GetModule(const std::string& moduleName);

	/// <param name="base">Base of the VTable</param>
	/// <param name="address">Address of the function.</param>
	/// <returns>Index of the function</returns>
	__forceinline int GetIndex(uintptr_t base, uintptr_t address);

	/// <returns>Address of the function at specified index in the base vtable</returns>
	__forceinline uintptr_t GetAddress(uintptr_t base, int index);

	template <typename Return>
	__forceinline Return CallVirtualFunction(uintptr_t base, int index, auto&&... args);

	inline std::unordered_map<std::string, uintptr_t> modules;
}

