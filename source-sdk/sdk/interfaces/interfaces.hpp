#pragma once
#include <string_view>
#include <d3d9.h>

#include "../valve/interfaces/icvar.hpp"
#include "../valve/interfaces/ipanel.hpp"
#include "../valve/interfaces/isurface.hpp"

// To get a list of interfaces for any source game: https://github.com/PancakeWithPotato/meowware-interfacewalker

using InterfaceCreateFunction = void* (__thiscall*)();

struct InterfaceReg {
	InterfaceCreateFunction createFunction;
	const char* name;
	InterfaceReg* next;
};

namespace sdk::interfaces {
	template <typename Return>
	decltype(auto) GetInterface32(const std::string_view moduleName, const std::string_view interfaceName);
	decltype(auto) GetInterface64(const std::string_view moduleName, const std::string_view interfaceName);

	void Initialize();

	inline CvarManager* cvar = nullptr;
	inline Surface* surface = nullptr; // @TODO: Add ISurface to the sdk
	inline Panel* panel = nullptr;
	inline IDirect3DDevice9* directx9 = nullptr;
}

// The difference between the 2 versions isn't that big, however, it's almost never inlined on 32 bit (only in module like steamclient.dll) so 
// we will not account for inlined CreateInterfaceInternals on 32bit.
#ifdef WIN32
#define GetInterface(type, moduleName, interfaceName) sdk::interfaces::GetInterface32<type>(moduleName, interfaceName);
#else
#define GetInterface(type, moduleName, interfaceName) sdk::interfaces::GetInterface64<type>(moduleName, interfaceName);
#endif