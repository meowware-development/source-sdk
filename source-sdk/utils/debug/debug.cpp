#include "debug.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

void utils::debug::Initialize(const std::string_view title) noexcept
{
#ifdef _DEBUG
	AllocConsole();

	// Open all io buffers (stdin, stdout, stderr)
	freopen_s(reinterpret_cast<_iobuf**>(stdin), "conin$", "r", static_cast<_iobuf*>(stdin));
	freopen_s(reinterpret_cast<_iobuf**>(stdout), "conout$", "w", static_cast<_iobuf*>(stdout));
	freopen_s(reinterpret_cast<_iobuf**>(stderr), "conout$", "w", static_cast<_iobuf*>(stderr));

	// In order to enable ANSII Color Codes
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_VIRTUAL_TERMINAL_INPUT);
	SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

	SetConsoleTitleA(title.data());
#endif
}

void utils::debug::Release() noexcept
{
#ifdef _DEBUG
	// Close all io buffers (stdin, stdout, stderr)
	fclose(static_cast<_iobuf*>(stdin));
	fclose(static_cast<_iobuf*>(stdout));
	fclose(static_cast<_iobuf*>(stderr));

	FreeConsole();
#endif
}
