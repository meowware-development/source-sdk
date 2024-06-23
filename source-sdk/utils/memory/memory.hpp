#pragma once
#include <string>
#include <unordered_map>

namespace utils::memory {
	/// <summary>
	/// If available returns cached module or fetches the module with the specified name
	/// </summary>
	uintptr_t GetModule(const std::string& moduleName) noexcept;

	/// <param name="base">Base of the VTable</param>
	/// <param name="address">Address of the function.</param>
	/// <returns>Index of the function</returns>
	int GetIndex(uintptr_t base, uintptr_t address) noexcept;

	/// <returns>Address of the function at specified index in the base vtable</returns>
	uintptr_t GetAddress(uintptr_t base, int index) noexcept;

	/// <summary>
	/// Calls function inside at the specified index from the base class vtable
	/// </summary>
	template <typename Return>
	Return CallVirtualFunction(uintptr_t base, int index, auto&&... args) noexcept;

	/// <summary>
	/// Scans for IDA-Styled sigs in the specified module. Throws if not found.
	/// Should generally be used in a try-catch scope while debugging.
	/// </summary>
	uint8_t* PatternScan(uintptr_t module, const char* ida);

	inline std::unordered_map<std::string, uintptr_t> modules;
}

