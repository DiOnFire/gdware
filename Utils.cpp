#include "Utils.h"
#include <vector>

void write_bytes(uintptr_t const address, std::vector<uint8_t> const& bytes) {
	WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(address), bytes.data(), bytes.size(), NULL);
}
