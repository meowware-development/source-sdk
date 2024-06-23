#include <Windows.h>
#include <stdexcept>

#include "../format/format.hpp"
#include "memory.hpp"

uintptr_t utils::memory::GetModule(const std::string& moduleName) noexcept
{
	if (modules.contains(moduleName))
		return modules.at(moduleName);

	// We haven't called for that module yet, let's grab it
	uintptr_t moduleAddress = reinterpret_cast<uintptr_t>(GetModuleHandleA(moduleName.data()));
	if (!moduleAddress)
		return 0;

	modules.emplace(std::make_pair(moduleName, moduleAddress));
	return moduleAddress;
}

uint8_t* utils::memory::PatternScan(uintptr_t module, const char* ida)
{
	// Convert from hexadecimal to bytes
	std::vector<int> bytes;

	size_t idaLen = strlen(ida);

	// Parse the string using pointers
	char* current = const_cast<char*>(ida);
	char* end = const_cast<char*>(ida) + idaLen;

	while (current < end) {
		if (*current == '?') {
			current = current + 3; // Skip the ?? and the space after
			bytes.emplace_back(-1); // In order to recognize wildcards

			continue;
		}

		// Convert the TWO hexadecimal chars to decimal integers 
		// Credits for the algorithm: https://stackoverflow.com/questions/10324/convert-a-hexadecimal-string-to-an-integer-efficiently-in-c
		char a = *current, b = *(current + 1);
		a = (a <= '9') ? a - '0' : (a & 0x7) + 9;
		b = (b <= '9') ? b - '0' : (b & 0x7) + 9;

		int dec = static_cast<int>((a << 4) + b);

		bytes.emplace_back(dec);
		current = current + 3;
	}

	// Creepy windows code
	const auto dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(module);
	const auto ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<uint8_t*>(module) + dosHeader->e_lfanew);

	const auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
	auto scanBytes = reinterpret_cast<std::uint8_t*>(module);

	size_t bytesLength = bytes.size();

	for (size_t i = 0; i < sizeOfImage - bytesLength; ++i) { // size - bytesLength because we dont want any overflow
		bool found = true; // Assume we found it

		// Check for the byte sequence starting at position i, ending at i + bytesLength
		for (size_t j = 0; j < bytesLength; ++j) {
			if (bytes[j] == -1) { // Skip over wild cards
				continue;
			}

			if (bytes[j] != scanBytes[i + j]) { // Sequence doesn't match, break
				found = false;
				break;
			}
		}

		if (!found) // Not found, keep searching
			continue;

		return &scanBytes[i];
	}

	// Scan for signatures ONLY in the initialization stage, in order to catch not found signatures.
	throw std::runtime_error(FORMAT("Couldn't find signature: %s", ida));
	return nullptr;
}