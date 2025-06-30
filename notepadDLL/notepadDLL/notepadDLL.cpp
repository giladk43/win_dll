#include <windows.h>
#include <stdio.h>
#include <processthreadsapi.h>
#include <libloaderapi.h>
#include <memoryapi.h>
#define LIBRARY "C:\\Users\\kogan\\Desktop\\From Home\\win_dll\\mydll\\Debug\\my_awesome_dll.dll"
#define NOTEPAD_PID (int)(26804)
//C:\\Users\\kogan\\Desktop\\From Home\\DLL_WINAPI\\Syringe\\my_awesome_dll.dll
typedef void(*PFUNC)(void);

int main()
{
	HANDLE notepad_process = OpenProcess(PROCESS_ALL_ACCESS, false, NOTEPAD_PID);
	if (NULL == notepad_process) {
		printf("Process not found \n");
		return 1;
	}
	LPVOID memory = VirtualAllocEx(notepad_process, NULL,strlen(LIBRARY), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (NULL == memory) {
		printf("Allocated memory not made \n");
		return 2;
	}
	LPVOID loadLibrary = (LPVOID)LoadLibraryA(LIBRARY);
	if (NULL == loadLibrary) {
		printf("Failed to load DLL\n");
		return 3;
	}
	BOOL success = WriteProcessMemory(notepad_process, memory, loadLibrary, strlen(LIBRARY), NULL);
	if (success == 0) {
		printf("Process memory was not written\n");
		return 4;
	}
	HANDLE new_thread = CreateRemoteThread(notepad_process, NULL, strlen(LIBRARY), (LPTHREAD_START_ROUTINE)loadLibrary, memory, 0, NULL);
	if (NULL == new_thread) {
		printf("Create Remote thread failed\n");
		return 5;
	}

	CloseHandle(new_thread);
	CloseHandle(notepad_process);
	return 0;
	/*
	PFUNC pFunc = (PFUNC)GetProcAddress(hModule, "Share");
	if (NULL != pFunc) {
		(*pFunc)();
	}
	else {
		printf("Failed to load Function\n");
	}
	CloseHandle(notepad_process);
	return 0;
	*/
}