#pragma once
#include <string_view>

#include "../valve/interfaces/cvar.hpp"
#include "../valve/interfaces/panel.hpp"
#include "../valve/interfaces/surface.hpp"
#include "../valve/interfaces/engine.hpp"
#include "../valve/interfaces/playerinfomanager.hpp"
#include "../valve/interfaces/netchannelinfo.hpp"
#include "../valve/interfaces/clientmode.hpp"
#include "../valve/interfaces/enginevgui.hpp"


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
	inline Surface* surface = nullptr;
	inline Panel* panel = nullptr;
	inline Engine* engine = nullptr;
	inline NetChannelInfo* netchannel = nullptr;
	inline ClientMode* clientMode = nullptr;
	inline PlayerInfoManager* playerInfoManager = nullptr;
	inline EngineVGui* engineVGUI = nullptr;
}

// The difference between the 2 versions isn't that big, however, it's almost never inlined on 32 bit (only in module like steamclient.dll) so 
// we will not account for inlined CreateInterfaceInternals on 32bit.
#ifdef WIN32
#define GetInterface(type, moduleName, interfaceName) sdk::interfaces::GetInterface32<type>(moduleName, interfaceName);
#else
#define GetInterface(type, moduleName, interfaceName) sdk::interfaces::GetInterface64<type>(moduleName, interfaceName);
#endif