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
	};

	void Initialize();
	void Uninitialize();

	void Update();

	inline Key leftMouseButton, rightMouseButton;
	inline std::array<Key, 256> keys;
	inline std::mutex keysMutex;
}