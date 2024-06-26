#include "interfaces.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdexcept>

#include "../../utils/memory/memory.hpp"
#include "../../utils/format/format.hpp"
#include "../../utils/debug/debug.hpp"

#include "../signatures.hpp"

template <typename Return>
decltype(auto) sdk::interfaces::GetInterface32(const std::string_view moduleName, const std::string_view interfaceName)
{
	const uintptr_t moduleAddres = utils::memory::GetModule(std::string(moduleName));
	if (!moduleAddres)
		throw std::runtime_error(FORMAT("Failed to get the address of module {}!", moduleName));

	// Get CreateInterface export from the module
	const uintptr_t createInterface = reinterpret_cast<uintptr_t>(GetProcAddress(reinterpret_cast<HMODULE>(moduleAddres), "CreateInterface"));
	if (!createInterface)
		throw std::runtime_error(FORMAT("Module {} doesn't export CreateInterface!", moduleName));

	// Get pointer to the interface single linked list
	const uint32_t rva = *reinterpret_cast<uint32_t*>(createInterface + 5);
	const uintptr_t internalFunction = createInterface + 9 + rva;
	InterfaceReg* current = **reinterpret_cast<InterfaceReg***>(internalFunction + 6);

	// Parse the linked list
	while (current) {
		// Check if interfaceName is included in current->name
		if (strstr(current->name, interfaceName.data())) {
			LOG(DebugLevel::OK, "Found interface {} in module {}!", current->name, moduleName);
			return reinterpret_cast<Return*>(current->createFunction());
		}

		current = current->next;
	}

	// Thorw if not found
	throw std::exception(FORMAT("Failed to fetch {} in module {}!", interfaceName, moduleName));
}

#ifdef WIN32
#define INTERFACE(type, moduleName, interfaceName) sdk::interfaces::GetInterface32<type>(moduleName, interfaceName);
#define SIGNATURE(type, moduleName, sig, offset) **utils::memory::PatternScan(utils::memory::GetModule(moduleName), sig).Cast<type***>(offset);
#else
#define INTERFACE(type, moduleName, interfaceName) sdk::interfaces::GetInterface64<type>(moduleName, interfaceName);
#endif

void sdk::interfaces::Initialize()
{
	// Get all interfaces
	client = INTERFACE(CHLClient, "client.dll", "VClient01");
	cvar = INTERFACE(CvarManager, "vstdlib.dll", "VEngineCvar00");
	surface = INTERFACE(Surface, "vguimatsurface.dll", "VGUI_Surface0");
	panel = INTERFACE(Panel, "vgui2.dll", "VGUI_Panel0");
	engine = INTERFACE(Engine, "engine.dll", "VEngineClient0");
	playerInfoManager = INTERFACE(PlayerInfoManager, "server.dll", "PlayerInfoManager002");
	engineVGUI = INTERFACE(EngineVGui, "engine.dll", "VEngineVGui00");
	entityList = INTERFACE(ClientEntityList, "client.dll", "VClientEntityList00");
	traceSystem = INTERFACE(TraceSystem, "engine.dll", "EngineTraceClient00");
	gameEventManager = INTERFACE(GameEventManager, "engine.dll", "GAMEEVENTSMANAGER002");
	modelInfo = INTERFACE(ModelInfo, "engine.dll", "VModelInfoClient00");
	movement = INTERFACE(GameMovement, "client.dll", "GameMovement0");
	prediction = INTERFACE(Prediction, "client.dll", "VClientPrediction00");

	// Scan for pointers
	clientMode = SIGNATURE(ClientMode, "client.dll", sdk::signatures::client::clientMode::sig, sdk::signatures::client::clientMode::offset);
	gameRules = SIGNATURE(GameRules, "client.dll", "C7 05 ?? ?? ?? ?? ?? ?? ?? ?? E9 ?? ?? ?? ?? CC CC CC", 2);

	// GetGlobalVars can be called anywhere in the game thread, so this can be easily removed if wanted
	globalVars = playerInfoManager->GetGlobalVars();

	LOG(DebugLevel::OK, "Initialized interfaces!");
}
