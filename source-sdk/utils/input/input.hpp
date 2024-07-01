#pragma once

#include <array>
#include <mutex>

namespace utils::input {
	enum class KeyState : uint8_t {
		IDLE,
		PRESSED,
		HELD
	};

	struct Key {
		bool lastTickPressed = false;
		KeyState state = KeyState::IDLE;

		bool IsIdle() const { return state == KeyState::IDLE; }
		bool IsPressed() const { return state == KeyState::PRESSED; }
		bool IsHeld() const { return state == KeyState::HELD; }
		bool IsDown() const { return !IsIdle(); }
		bool IsUp() const { return IsIdle(); }
	};

	void Initialize();
	void Uninitialize();

	void Update();

	struct Mouse {
		int xPos = 0, yPos = 0;
		// If > 0 => mouse wheel is scrolling up, otherwise it is scrolling down, and if it's 0 its just not moving at all.
		int wheelDelta = 0;

		bool Hovering(int x, int y, int width, int height) const;
		bool Held(int x, int y, int width, int height) const;
		bool Clicked(int x, int y, int width, int height) const;
		bool RightClicked(int x, int y, int width, int height) const;
	} inline mouse;

	inline std::array<Key, 256> keys;
	inline std::mutex keysMutex;
	inline bool initialized = false;
}