#pragma once
#include "Memory.h"
#include "offsets.h"

/*Cette Classe vas créer un contour de lumiere autour d'une entitée.
Cette Classe peut être optimisé en créant une classe / struct car les offsets ce suivent.*/

class Glow
{
public:
	Glow(Memory *mem, int &client);
	~Glow();

	__forceinline void __fastcall glow(int index) {
		int glowIndex = mem->read<int>(index + hazedumper::netvars::m_iGlowIndex);

		mem->write<float>(glowObject + (glowIndex * 0x38 + 0x4), red / 255.f);
		mem->write<float>(glowObject + (glowIndex * 0x38 + 0x8), green / 255.f);
		mem->write<float>(glowObject + (glowIndex * 0x38 + 0xC), blue / 255.f);
		mem->write<float>(glowObject + (glowIndex * 0x38 + 0x10), alpha);
		mem->write<bool>(glowObject + (glowIndex * 0x38 + 0x24), true);
		mem->write<bool>(glowObject + (glowIndex * 0x38 + 0x25), false);
	}
	__forceinline void __fastcall glow(int index, float red, float green, float blue) {
		int glowIndex = mem->read<int>(index + hazedumper::netvars::m_iGlowIndex);
		
		mem->write<float>(glowObject + (glowIndex * 0x38 + 0x4), red / 255.f);
		mem->write<float>(glowObject + (glowIndex * 0x38 + 0x8), green / 255.f);
		mem->write<float>(glowObject + (glowIndex * 0x38 + 0xC), blue / 255.f);
		mem->write<float>(glowObject + (glowIndex * 0x38 + 0x10), alpha);
		mem->write<bool>(glowObject + (glowIndex * 0x38 + 0x24), true);
		mem->write<bool>(glowObject + (glowIndex * 0x38 + 0x25), false);
		
	}

private:
	float red = 0.0f;
	float green = 0.0f;
	float blue = 0.0f;
	float alpha = 1.0f;

	int glowObject = 0;
	int client = 0;

	Memory *mem = nullptr;

};

