#pragma once
#define WIN32_MEAN_AND_LEAN
#include <Windows.h>
#include <memory>
#include <vector>

struct VMTHook;

static std::vector<VMTHook*> vmtHooks;

struct VMTHook {
	VMTHook() = default;

	void Initalize(const char* name, void* base, int index, void* detour)
	{
		// Get the vmt and the original function
		void** vmt = *reinterpret_cast<void***>(base);
		void*& function = vmt[index];

		// Save the original function.
		this->original = function;

		// Overwrite memory protections
		DWORD old;
		VirtualProtect(vmt, index * sizeof(void*), PAGE_EXECUTE_READWRITE, &old);

		// Change function
		function = detour;

		// Revert memory protections
		VirtualProtect(vmt, index * sizeof(void*), old, &old);

		this->name = name;
		this->base = base;
		this->detour = detour;
		this->index = index;

		// Add to the list
		vmtHooks.emplace_back(this);
	}

	/// <summary>
	/// Resets the hook, points the vtable pointer back to the original
	/// </summary>
	void Reset()
	{
		void** vmt = *reinterpret_cast<void***>(base);
		void*& function = vmt[index];

		DWORD old;
		VirtualProtect(vmt, index * sizeof(void*), PAGE_EXECUTE_READWRITE, &old);

		function = original;

		VirtualProtect(vmt, index * sizeof(void*), old, &old);
	}

	const char* GetName() const
	{
		return name;
	}

	template<typename Type>
	Type GetOriginal() const
	{
		return static_cast<Type>(original);
	}

	// Call once to reset the hooks back to their original pointer.
	static void Uninitialize()
	{
		for (auto& hook : vmtHooks) {
			hook->Reset();
		}
	}

private:
	void* original;
	int index;
	void* base;
	void* detour;
	const char* name;
};