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

utils::memory::Scan utils::memory::PatternScan(uintptr_t module, const char* ida)
{
	// Convert from hexadecimal to bytes
	std::vector<int> bytes;

	size_t idaLen = strlen(ida);

	// Parse the string, by skipping 3 characters each time
	for (size_t idx = 0; idx < idaLen; idx += 3) {
		if (ida[idx] == '?') {
			bytes.emplace_back(-1); // In order to recognize wildcards
			continue;
		}

		// Convert the TWO hexadecimal chars to decimal integers 
		char a = ida[idx], b = ida[idx + 1];
		a = (a <= '9') ? a - '0' : (a & 0x7) + 9;
		b = (b <= '9') ? b - '0' : (b & 0x7) + 9;

		int dec = static_cast<int>((a << 4) + b);

		bytes.emplace_back(dec);
	}

	size_t bytesLength = bytes.size();

	// Get image headers
	const auto dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(module);
	const auto ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<uint8_t*>(module) + dosHeader->e_lfanew);

	// Get first section
	PIMAGE_SECTION_HEADER currentSection = IMAGE_FIRST_SECTION(ntHeaders);
	size_t sectionIndex = 0;

	// Parse the PE sections
	for (; sectionIndex < ntHeaders->FileHeader.NumberOfSections; currentSection++, sectionIndex++) {
		// We only want the executable ones. In this case, only .text is executable
		if (!(currentSection->Characteristics & IMAGE_SCN_MEM_EXECUTE))
			continue;

		const auto sizeOfSection = currentSection->Misc.VirtualSize;
		auto scanBytes = reinterpret_cast<std::uint8_t*>(module + currentSection->VirtualAddress);

		// Classic linear search
		for (size_t i = 0, j = 0; i < sizeOfSection; ++i) {
			if ((scanBytes[i] == bytes[j] || bytes[j] == -1)) {
				if (j == bytesLength - 1)
					return Scan(&scanBytes[i - bytesLength + 1]);
				else
					++j;
			}
			else {
				if (i > 0 && j > 0) {
					if (scanBytes[i - 1] == bytes[j - 1])
						--i;

					j = 0;
				}
			}
		}
	}

	// Will only work in the initialization stage, so put important stuff there
	throw std::runtime_error(FORMAT("Couldn't find signature: {}", ida));
	return Scan();
}