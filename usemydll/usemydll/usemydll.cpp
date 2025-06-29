#include <windows.h>
#include <stdio.h>
#define LIBRARY "C:\\Users\\kogan\\Desktop\\From Home\\win_dll\\mydll\\Debug\\mydll.dll"

typedef void(*PFUNC)(void);

int main()
{
	HMODULE hModule = LoadLibraryA(LIBRARY);
	if (NULL == hModule) {
		printf("Failed to load DLL\n");
		return 0;
	}
	PFUNC pFunc = (PFUNC)GetProcAddress(hModule, "Share");
	if (NULL != pFunc) {
		(*pFunc)();
	}
	else {
		printf("Failed to load Function\n");
	}
	return 0;
}