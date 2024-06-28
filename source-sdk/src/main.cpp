#include "../globals.hpp"
#include "hooks/hooks.hpp"

void Initialization()
{
	try {
		utils::debug::Initialize("source-sdk");
		utils::input::Initialize();
		utils::crashhandler::Initalize();

		sdk::interfaces::Initialize();

		sdk::netvars::Initialize();

		utils::renderer::Initialize();

		sdk::events::Initialize();

		// Initalize globals
		globals::moveData = *utils::memory::PatternScan(utils::memory::GetModule("client.dll"), "FF 35 ?? ?? ?? ?? 8B 4D ?? FF 75").Cast<MoveData**>(2);
		LOG(DebugLevel::OK, "g_pMoveData: 0x{:X}", reinterpret_cast<uintptr_t>(globals::moveData));
	}
	catch (const std::exception& error) {
		LOG(DebugLevel::ERR, "Exception: {}", error.what());
		if (MessageBoxA(NULL, error.what(), "Exception!", MB_ICONERROR))
			globals::shouldUnload = true;
	}

	src::hooks::Initalize();

	LOG(DebugLevel::OK, "Initialization finished!");
}

void Attach(HINSTANCE instance)
{
	// Wait for the game to fully load
	while (!GetModuleHandleA(utils::consts::lastLoadedModule))
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

	// Start the initialization procedure
	Initialization();

	// Wait till the user presses VK_END to start the unload procedure
	// @TODO: Replace with own input from wndproc after properly updating the keys in game thread
	while (utils::input::keys[VK_END].IsIdle() && !globals::shouldUnload) {
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}

	// Exit thread, DllMain will be called with DLL_PROCESS_DETACH
	FreeLibraryAndExitThread(instance, EXIT_SUCCESS);
}

void Detach()
{
	// Do any cleaning here.
	src::hooks::Uninitalize();

	utils::debug::Release();

	utils::input::Uninitialize();

	sdk::events::Uninitialize();
}

BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved)
{
	DisableThreadLibraryCalls(instance);

	switch (reason) {
	case DLL_PROCESS_ATTACH: {
		HANDLE threadHandle = CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Attach), instance, 0, 0);

		if (!threadHandle) {
			MessageBoxA(NULL, FORMAT("CreateThread Failed! Error code: {}", GetLastError()), "Exception!", MB_ICONERROR);
		}
		else {
			CloseHandle(threadHandle);
		}

		break;
	}
	case DLL_PROCESS_DETACH: {
		Detach();
		break;
	}
	}

	return TRUE;
}