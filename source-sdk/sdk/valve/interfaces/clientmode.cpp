#include "clientmode.hpp"
#include "../../../utils/memory/memory.hpp"

ClientMode* ClientMode::GetClientMode()
{
    using GetClientModeNormal = ClientMode*(__cdecl*)();
    static auto function = reinterpret_cast<GetClientModeNormal>(utils::memory::PatternScan(utils::memory::GetModule("client.dll"), "A1 ?? ?? ?? ?? A8 ?? 75 ?? 83 C8 ?? B9 ?? ?? ?? ?? A3 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B 0D"));
    return function();
}
