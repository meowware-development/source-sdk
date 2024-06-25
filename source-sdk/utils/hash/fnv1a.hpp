#pragma once
#include <string>
#include <stdint.h>
#include <sstream>

namespace utils::hash::fnv1a {
	constexpr uint32_t val32Const = 0x811c9dc5;
	constexpr uint32_t prime32Const = 0x1000193;
	constexpr uint64_t val64Const = 0xcbf29ce484222325;
	constexpr uint64_t prime64Const = 0x100000001b3;

	inline constexpr uint32_t hash32(const std::string str, const uint32_t value = val32Const) noexcept {
		return (str[0] == '\0') ? value : hash32(&str[1], (value ^ uint32_t((uint8_t)str[0])) * prime32Const);
	}

	inline constexpr uint64_t hash64(const std::string str, const uint64_t value = val64Const) noexcept {
		return (str[0] == '\0') ? value : hash64(&str[1], (value ^ uint64_t((uint8_t)str[0])) * prime64Const);
	}
}