#include "../globals.hpp"

void Initialization()
{
	try {
		utils::debug::Initialize("source-sdk");
	}
	catch (const std::exception& error) {
		LOG(DebugLevel::ERR, "Exception: {}", error.what());
		if (MessageBoxA(NULL, error.what(), "Exception!", MB_ICONERROR))
			globals::shouldUnload = true;
	}

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
	while (!GetAsyncKeyState(VK_END) && !globals::shouldUnload)
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

	// Exit thread, DllMain will be called with DLL_PROCESS_DETACH
	FreeLibraryAndExitThread(instance, EXIT_SUCCESS);
}

void Detach()
{
	// Do any cleaning here.

	utils::debug::Release();
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