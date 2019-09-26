#include "Memory.h"
#include <Windows.h>
#include <TlHelp32.h>


Memory::Memory(LPCWSTR windowName)
{
	this->windowName = windowName;
	setPID();
	processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->processID);
}

Memory::~Memory()
{
}
//Credits to Unkowncheats.eu
void Memory::setPID() {

	HWND windowHandle = FindWindowW(NULL, windowName);
	DWORD* processID = new DWORD;

	if (GetWindowThreadProcessId(windowHandle, processID)) {	
		this->processID = *processID;
	}

	delete processID;
}

DWORD Memory::getModuleAddress(LPCSTR ModuleName)
{

	HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, this->processID);
	MODULEENTRY32 mEntry;
	mEntry.dwSize = sizeof(mEntry);
	do {
		if (!lstrcmp(mEntry.szModule, ModuleName))
		{
			CloseHandle(hModule);
			return (DWORD)mEntry.modBaseAddr;
		}
	} while (Module32Next(hModule, &mEntry));

	return 0;
}


