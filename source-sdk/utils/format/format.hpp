#pragma once
#include <format>

#define FORMAT(string, ...) std::format(string, __VA_ARGS__).data()