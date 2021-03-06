// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "PauseLayer.h"
#include "MenuLayer.h"

DWORD WINAPI gdware_thread(void* hModule) {
    if (MH_Initialize() != MH_OK) {
        FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(hModule), 0);
    }
    MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x1E4620), PauseLayer::hook, reinterpret_cast<void**>(&PauseLayer::init));
    MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x1907B0), MenuLayer::hook, reinterpret_cast<void**>(&MenuLayer::init));
    MH_EnableHook(MH_ALL_HOOKS);
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0x1000, gdware_thread, hModule, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

