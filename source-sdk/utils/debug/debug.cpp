#include "debug.hpp"

#include <Windows.h>

void utils::debug::Initialize(std::string_view title) noexcept
{
#ifdef _DEBUG
	AllocConsole();

	freopen_s(reinterpret_cast<_iobuf**>(__acrt_iob_func(0)), "conin$", "r", static_cast<_iobuf*>(__acrt_iob_func(0)));
	freopen_s(reinterpret_cast<_iobuf**>(__acrt_iob_func(1)), "conout$", "w", static_cast<_iobuf*>(__acrt_iob_func(1)));
	freopen_s(reinterpret_cast<_iobuf**>(__acrt_iob_func(2)), "conout$", "w", static_cast<_iobuf*>(__acrt_iob_func(2)));

	// In order to enable ANSII Color Codes
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_VIRTUAL_TERMINAL_INPUT);
	SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

	SetConsoleTitleA(title.data());
#endif
}

void utils::debug::Release() noexcept
{
#ifdef _DEBUG
	fclose(static_cast<_iobuf*>(__acrt_iob_func(0)));
	fclose(static_cast<_iobuf*>(__acrt_iob_func(1)));
	fclose(static_cast<_iobuf*>(__acrt_iob_func(2)));

	FreeConsole();
#endif
}
