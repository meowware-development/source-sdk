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
#include "../valve/interfaces/chlclient.hpp"
#include "../valve/interfaces/entitylist.hpp"
#include "../valve/interfaces/tracesystem.hpp"
#include "../valve/interfaces/eventmanager.hpp"
#include "../valve/interfaces/modelinfo.hpp"
#include "../valve/interfaces/gamemovement.hpp"
#include "../valve/interfaces/prediction.hpp"
#include "../valve/interfaces/movehelper.hpp"
#include "../valve/interfaces/gamerules.hpp"

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
	inline ClientMode* clientMode = nullptr;
	inline PlayerInfoManager* playerInfoManager = nullptr;
	inline EngineVGui* engineVGUI = nullptr;
	inline CHLClient* client = nullptr;
	inline ClientEntityList* entityList = nullptr;
	inline TraceSystem* traceSystem = nullptr;
	inline GameEventManager* gameEventManager = nullptr;
	inline ModelInfo* modelInfo = nullptr;
	inline GameMovement* movement = nullptr;
	inline Prediction* prediction = nullptr;
	inline GlobalVars* globalVars = nullptr;
	inline GameRules* gameRules = nullptr;
}