// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#define DLL_EXPORT
#include "mydll.h"


extern "C"
{
    DECLDIR void Share() {
        printf("This is text from outside the DLL \n");
    }

    void Keep() {
        printf("This is text from inside the DLL \n");
    }
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

