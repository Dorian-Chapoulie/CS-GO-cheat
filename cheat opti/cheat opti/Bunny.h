#pragma once
#include "Memory.h"
#include "offsets.h"

/*Cette classe vas nous permetre de sauter automatiquement lorsque nous somme au sol, afin d'exploiter un bug du moteur physique, qui nous feras
courrir beacoup plus vite.*/
class Bunny
{
public:
	Bunny(Memory *m, int *localPlayer, int *client);

	~Bunny();

	__forceinline bool isOnFloor()
	{
		return mem->read<int>(localPlayer + hazedumper::netvars::m_fFlags) == 257;
	}
	__forceinline void __fastcall forceJump(int i)
	{
		mem->write<int>(client + hazedumper::signatures::dwForceJump, i);
	}

private:
	Memory	*mem;
	int client = 0;
	int localPlayer = 0; //Adresse de l'instance du joueur local (nous)
};

