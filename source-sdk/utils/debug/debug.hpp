#pragma once
#include <string_view>
#include <cstdarg>
//#include <print>
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
		switch (level) {
		case DebugLevel::NONE: {
			printf("[\033[97m...\033[0m] ");
			break;
		}
		case DebugLevel::OK: {
			printf("[\033[92mOK\033[0m] ");
			break;
		}
		case DebugLevel::ERR: {
			printf("[\033[31mERROR\033[0m] ");
			break;
		}
		}

		// std::println(std::runtime_format(format), std::forward<decltype(args)>(args)...);

		// Fix until runtime_format comes to msvc
		std::cout << std::vformat(format, std::make_format_args(args...)) << "\n";
	}
}

#ifdef _DEBUG
#define LOG(level, format, ...) utils::debug::Log(level, format, __VA_ARGS__)
#else
#define LOG(level, format, ...) 
#endif // _DEBUG