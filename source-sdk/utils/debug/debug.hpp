#pragma once
#include <string_view>
#include <cstdarg>

namespace utils::debug {
	void Initialize(std::string_view title) noexcept;
	void Release() noexcept;

	enum class Level {
		NONE,
		OK,
		ERR,
	};

	template <typename ... Args>
	void Log(utils::debug::Level level, const char* format, ...) noexcept {

		switch (level) {
		case Level::NONE: {
			printf("[\033[97m...\033[0m] ");
			break;
		}
		case Level::OK: {
			printf("[\033[92mOK\033[0m] ");
			break;
		}
		case Level::ERR: {
			printf("[\033[31mERROR\033[0m] ");
			break;
		}
		}

		va_list args;
		va_start(args, format);
		vprintf(format, args);
		va_end(args);

		printf("\n");
	}
}

#define LOG(level, format, ...) utils::debug::Log(utils::debug::Level::level, format, __VA_ARGS__)