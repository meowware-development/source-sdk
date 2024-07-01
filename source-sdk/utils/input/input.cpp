#include "input.hpp"

#include "../debug/debug.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <windowsx.h>

#include <exception>

namespace utils::input {
	// Microsoft says: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nc-winuser-wndproc
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
				case KeyState::IDLE: {
					keys[wparam].state = KeyState::PRESSED;
					break;
				}
				}
			}
			break;
		}
		case WM_KEYUP:
		case WM_SYSKEYUP: {
			if (wparam > 0 && wparam < 256) {
				keys[wparam].state = KeyState::IDLE;
				keys[wparam].lastTickPressed = false;
			}
			break;
		}
		case WM_LBUTTONDOWN: // Handle left mouse button
		case WM_LBUTTONDBLCLK: {
			keys[VK_LBUTTON].state = KeyState::PRESSED;
			break;
		}
		case WM_LBUTTONUP: {
			keys[VK_LBUTTON].state = KeyState::IDLE;
			keys[VK_LBUTTON].lastTickPressed = false;
			break;
		}
		case WM_RBUTTONDOWN: // Handle right mouse button
		case WM_RBUTTONDBLCLK: {
			keys[VK_RBUTTON].state = KeyState::PRESSED;
			break;
		}
		case WM_RBUTTONUP: {
			keys[VK_RBUTTON].state = KeyState::IDLE;
			keys[VK_RBUTTON].lastTickPressed = false;
			break;
		}
		case WM_MOUSEMOVE: { // Handle mouse coordonations on the screen
			mouse.xPos = GET_X_LPARAM(lparam);
			mouse.yPos = GET_Y_LPARAM(lparam);
			break;
		}
		case WM_MOUSEWHEEL: { // Handle mouse wheel
			mouse.wheelDelta = GET_WHEEL_DELTA_WPARAM(wparam);
			break;
		}
		}

		return CallWindowProcW(original, hwnd, msg, wparam, lparam);
	}

	bool input::Mouse::Hovering(int x, int y, int width, int height) const
	{
		return (x >= xPos) && (y >= yPos) && (x <= xPos + width) && (y <= yPos + height);
	}

	bool input::Mouse::Clicked(int x, int y, int width, int height) const
	{
		return (x >= xPos) && (y >= yPos) && (x <= xPos + width) && (y <= yPos + height) && keys[VK_LBUTTON].IsPressed();
	}

	bool input::Mouse::RightClicked(int x, int y, int width, int height) const
	{
		return (x >= xPos) && (y >= yPos) && (x <= xPos + width) && (y <= yPos + height) && keys[VK_RBUTTON].IsPressed();
	}

	bool input::Mouse::Held(int x, int y, int width, int height) const
	{
		return (x >= xPos) && (y >= yPos) && (x <= xPos + width) && (y <= yPos + height) && keys[VK_LBUTTON].IsHeld();
	}
}

void utils::input::Update()
{
	/* This function has to be called every tick in order to update the key states manually,
	since WndProc only gets called if any key press happens ONCE, and it doesnt get called if the key is being held (too bad!)

	WARNING: Must be called in the game's thread.
	Tried doing a separate thread but it's just too fast (keys go to KeyState::HELD instantly and are not one time recognized for being at KeyState::PRESSED as they should)
	Best place would be in a rendering function or even CHLClient::HudUpdate() I guess
	*/

	for (size_t i = 0; i < 256; ++i) {
		Key& key = keys[i];

		// If the key was already pressed, set it to held
		if (key.lastTickPressed) {
			key.state = KeyState::HELD;
		} // If it wasn't and it is currently being pressed, set it to true
		else if (key.state == KeyState::PRESSED) {
			key.lastTickPressed = true;
		}
	}
}

void utils::input::Initialize()
{
	// Find game window by the Valve001 class (Can be used in all source games)
	window = FindWindowA("Valve001", NULL);

	if (!window) {
		[[unlikely]]
		throw std::exception("Couldn't find game window!");
	}

	original = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));

	if (!original) {
		[[unlikely]]
		throw std::exception("Couldn't initialize input!");
	}

	LOG(DebugLevel::OK, "Initialized input!");

	initialized = true;
}

void utils::input::Uninitialize()
{
	SetWindowLongW(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(original));

	initialized = false;
}
