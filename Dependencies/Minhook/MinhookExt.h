#pragma once
#include <type_traits>
#include "MinHook.h"

template<typename TargetAddr, typename OutPtr>
inline void CreateHook(TargetAddr address, void* detour, OutPtr** trampolinePtr) {
    auto addr = reinterpret_cast<LPVOID>(address);
    MH_CreateHook(addr, detour, reinterpret_cast<PVOID*>(trampolinePtr));
}

template<typename T>
MH_STATUS CreateHookApi(LPCWSTR pszModule, LPCSTR pszProcName, LPVOID pDetour, T** ppOriginal) {
    LPVOID* original = reinterpret_cast<LPVOID*>(ppOriginal);
    return MH_CreateHookApi(pszModule, pszProcName, pDetour, original);
}
