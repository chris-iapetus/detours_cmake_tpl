#include <windows.h>
#include <detours.h>
#include <iostream>

int (WINAPI *pMessageBoxA)(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType) = MessageBoxA;

int WINAPI my_MessageBoxA(
	_In_opt_ HWND hWnd,
	_In_opt_ LPCSTR lpText,
	_In_opt_ LPCSTR lpCaption,
	_In_ UINT uType)
{
	std::cout << "TITLE: [" << lpCaption << "]" << std::endl;
	std::cout << "MESSAGE: [" << lpText << "]" << std::endl;
	return pMessageBoxA(hWnd, lpText, lpCaption, uType);
}

int main()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)pMessageBoxA, my_MessageBoxA);
	DetourTransactionCommit();

	MessageBoxA(NULL,  "Hello World", "OK", MB_OK);
	system("pause");
	return 0;
}
