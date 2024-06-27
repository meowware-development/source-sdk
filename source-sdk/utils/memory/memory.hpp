#pragma once
#include <string>
#include <unordered_map>

#include "../constants/const.hpp"

namespace utils::memory {
	/// <summary>
	/// If available returns cached module or fetches the module with the specified name
	/// </summary>
	uintptr_t GetModule(const std::string& moduleName) noexcept;

	/// <param name="base">Base of the VTable</param>
	/// <param name="address">Address of the function.</param>
	/// <returns>Index of the function</returns>
	__forceinline int GetIndex(void* base, uintptr_t address) noexcept
	{
		return (static_cast<int>((address - (uintptr_t)base))) / utils::consts::pointerSize;
	}

	/// <returns>Address of the function at specified index in the base vtable</returns>
	__forceinline uintptr_t GetAddress(void* base, int index) noexcept
	{
		return (*reinterpret_cast<uintptr_t**>(base)[index]);
	}

	/// <summary>
	/// Calls function inside at the specified index from the base class vtable
	/// </summary>
	template <typename Return>
	__forceinline Return CallVirtualFunction(void* base, int index, auto && ...args) noexcept
	{
		using Function = Return(__thiscall*)(void*, decltype(args)...);
		Function function = (*reinterpret_cast<Function**>(base))[index];
		return function(reinterpret_cast<void*>(base), std::forward<decltype(args)>(args)...);
	}

	class Scan {
	public:
		Scan() = default;
		Scan(uint8_t* value) : m_ReturnValue(value) {}

		template <typename ReturnType>
		ReturnType Cast(int offset = 0) {
			return reinterpret_cast<ReturnType>(m_ReturnValue + offset);
		}

		template <typename ReturnType>
		ReturnType Relative(int offset = 0) {
			return reinterpret_cast<ReturnType>(m_ReturnValue + 0x1 + offset);
		}

		uint8_t* GetValue() {
			return m_ReturnValue;
		}
	private:
		uint8_t* m_ReturnValue = 0;
	};

	/// <summary>
	/// Scans for IDA-Styled sigs in the specified module. Throws if not found.
	/// Should generally be used in a try-catch scope while debugging.
	/// </summary>
	Scan PatternScan(uintptr_t module, const char* ida);

	inline std::unordered_map<std::string, uintptr_t> modules;
}

