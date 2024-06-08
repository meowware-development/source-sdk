#pragma once
#include <string_view>
#include <iostream>

enum class DebugLevel : uint8_t {
	NONE,
	OK,
	ERR,
};

namespace utils::debug {
	void Initialize(const std::string_view title) noexcept;
	void Release() noexcept;

	void Log(DebugLevel level, std::string_view format, auto&&... args) noexcept
	{
#ifdef _DEBUG
		// https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
		switch (level) {
		case DebugLevel::NONE: {
			std::cout << "[\033[97m...\033[0m] ";
			break;
		}
		case DebugLevel::OK: {
			std::cout << "[\033[92mOK\033[0m] ";
			break;
		}
		case DebugLevel::ERR: {
			std::cout << "[\033[31mERROR\033[0m] ";
			break;
		}
		}

		// std::println(std::runtime_format(format), std::forward<decltype(args)>(args)...);

		// Fix until runtime_format comes to msvc
		std::cout << std::vformat(format, std::make_format_args(args...)) << '\n';
	}
#endif
}

#ifdef _DEBUG
#define LOG(level, format, ...) utils::debug::Log(level, format, __VA_ARGS__)
#else
#define LOG(level, format, ...) 
#endif // _DEBUG