#include "input.hpp"

#include "../debug/debug.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <exception>

namespace utils::input {
	// Microsoft: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nc-winuser-wndproc
	inline WNDPROC original = nullptr;
	inline HWND window = nullptr;
	inline HANDLE update = nullptr;

	unsigned long __stdcall WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		switch (msg) {
		case WM_KEYDOWN: // Handle normal keys
		case WM_SYSKEYDOWN: {
			if (wparam > 0 && wparam < 256) {
				switch (keys[wparam].state) {
				case KeyState::IDLE: keys[wparam].state = KeyState::PRESSED; break;
				case KeyState::PRESSED: keys[wparam].state = KeyState::HELD; break;
				}
			}
			break;
		}
		case WM_KEYUP:
		case WM_SYSKEYUP: {
			if (wparam > 0 && wparam < 256) {
				keys[wparam].state = KeyState::IDLE;
			}
			break;
		}
		case WM_LBUTTONDOWN: // Handle left mouse button
		case WM_LBUTTONDBLCLK: {
			switch (leftMouseButton.state) {
			case KeyState::IDLE: leftMouseButton.state = KeyState::PRESSED; break;
			case KeyState::PRESSED: leftMouseButton.state = KeyState::HELD; break;
			}
			break;
		}
		case WM_LBUTTONUP: {
			leftMouseButton.state = KeyState::IDLE;
			break;
		}
		case WM_RBUTTONDOWN: // Handle right mouse button
		case WM_RBUTTONDBLCLK: {
			switch (rightMouseButton.state) {
			case KeyState::IDLE: rightMouseButton.state = KeyState::PRESSED; break;
			case KeyState::PRESSED: rightMouseButton.state = KeyState::HELD; break;
			}
			break;
		}
		case WM_RBUTTONUP: {
			rightMouseButton.state = KeyState::IDLE;
			break;
		}
		}

		return CallWindowProcW(original, hwnd, msg, wparam, lparam);
	}
}

void utils::input::Update() {
	/* This function has to be called every tick in order to update the key states manually,
	since WndProc only gets called if any key press happens */
	keysMutex.lock();

	for (size_t i = 0; i < 256; ++i) {
		Key& key = keys[i];

		// If the key was already pressed, set it to held
		if (key.lastTickPressed)
			key.state = KeyState::HELD;

		switch (key.state) {
		case KeyState::IDLE: {
			// Key stopped being held
			key.lastTickPressed = false;
			break;
		}
		case KeyState::PRESSED: {
			// Pressed once, about to go to held next tick
			key.lastTickPressed = true;
			break;
		}
		}
	}

	keysMutex.unlock();
}

void utils::input::Initialize()
{
	window = FindWindowA("Valve001", NULL);

	if (!window)
		throw std::exception("Couldn't find game window!");

	original = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));

	if (!original)
		throw std::exception("Couldn't initialize input!");

	LOG(DebugLevel::OK, "Initialized input!");

	HANDLE update = CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Update), 0, 0, 0);

	if (!update)
		throw std::exception("Couldn't initialize utils::input::Update thread!");

	CloseHandle(update);
}

void utils::input::Uninitialize()
{
	SetWindowLongW(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(original));
}
