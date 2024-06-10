#pragma once
#include <Windows.h>

namespace utils::crashhandler {
	void Initalize();

	LONG WINAPI ExceptionHandler(EXCEPTION_POINTERS* exception);
}