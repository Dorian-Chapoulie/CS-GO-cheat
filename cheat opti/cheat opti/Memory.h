#pragma once
#include <Windows.h>
#include <TlHelp32.h>

/*Classe permettant d'�crire / lire � un emplacement m�moire donn� / d'un fichier donn�*/
class Memory
{
public:
	Memory(LPCWSTR windowName);
	~Memory();

	template <typename T>
	__forceinline void __fastcall read(int address, T &var) {
		ReadProcessMemory(processHandle, (DWORD*)address, &var, sizeof(var), NULL);
	}
	
	template <typename U>
	__forceinline U __fastcall read(int address) {
		U var;
		ReadProcessMemory(processHandle, (DWORD*)address, &var, sizeof(var), NULL);
		return var;
	}
	
	template <typename V>
	__forceinline void __fastcall write(int address, V *var) {
		WriteProcessMemory(processHandle, (DWORD*)address, var, sizeof(var), NULL);
	}

	template <typename W>
	__forceinline void __fastcall write(int address, W var) {
		WriteProcessMemory(processHandle, (DWORD*)address, &var, sizeof(var), NULL);
	}

	DWORD		getModuleAddress(LPCSTR ModuleName);

//private:
	LPCWSTR		windowName = 0;
	DWORD		processID = 0;
	HANDLE		processHandle = 0;

	void		setPID();
};

