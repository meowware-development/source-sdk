#include "interfaces.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdexcept>

#include "../../utils/memory/memory.hpp"
#include "../../utils/format/format.hpp"

#include "../signatures.hpp"

template <typename Return>
decltype(auto) sdk::interfaces::GetInterface32(const std::string_view moduleName, const std::string_view interfaceName)
{
	const uintptr_t moduleAddres = utils::memory::GetModule(std::string(moduleName));
	if (!moduleAddres)
		throw std::runtime_error(FORMAT("Failed to get the address of module {}!", moduleName));

	const uintptr_t createInterface = reinterpret_cast<uintptr_t>(GetProcAddress(reinterpret_cast<HMODULE>(moduleAddres), "CreateInterface"));
	if (!createInterface)
		throw std::runtime_error(FORMAT("Module {} doesn't export CreateInterface!", moduleName));

	const uint32_t rva = *reinterpret_cast<uint32_t*>(createInterface + 5);
	const uintptr_t internalFunction = createInterface + 9 + rva;
	InterfaceReg* current = **reinterpret_cast<InterfaceReg***>(internalFunction + 6);

	while (current) {
		if (strstr(current->name, interfaceName.data())) {
			return reinterpret_cast<Return*>(current->createFunction());
		}

		current = current->next;
	}

	throw std::runtime_error(FORMAT("Failed to fetch {} in module {}!", interfaceName, moduleName));
}

void sdk::interfaces::Initialize()
{
	cvar = GetInterface(CvarManager, "vstdlib.dll", "VEngineCvar00");
	surface = GetInterface(Surface, "vguimatsurface.dll", "VGUI_Surface0");
	panel = GetInterface(Panel, "vgui2.dll", "VGUI_Panel0");
	engine = GetInterface(Engine, "engine.dll", "VEngineClient0");
	playerInfoManager = GetInterface(PlayerInfoManager, "server.dll", "PlayerInfoManager002");
	engineVGUI = GetInterface(EngineVGui, "engine.dll", "VEngineVGui00");
	netchannel = engine->GetNetChannelInfo();
}
