#pragma once
#include <math.h>
#include "Vector2D.h"
#include "Vector3D.h"
#include <Windows.h>
#include <algorithm>

/*Clamp les angles pour ne pas avoir des angles invalide en jeu*/
//Credits to Unkowncheats.eu
__forceinline Vector2D __fastcall CalcAngle(Vector3D *src, Vector3D *dst)
{

	Vector2D angles;
	float delta[3] = { (src->x - dst->x), (src->y - dst->y), (src->z - dst->z) };
	float hyp = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);

	angles.x = (float)(asinf(delta[2] / hyp) * 57.295779513082f);
	angles.y = (float)(atanf(delta[1] / delta[0]) * 57.295779513082f);

	if (delta[0] >= 0.0)
	{
		angles.y += 180.0f;
	}


	if (angles.x > 89)
	{
		angles.x = 89;
	}
	if (angles.x < -89)
	{
		angles.x = -89;
	}
	if (angles.y > 180)
	{
		angles.y -= 360;
	}
	if (angles.y < -180)
	{
		angles.y += 360;
	}

	return angles;
}


__forceinline float __fastcall get2dDistance(Vector2D posX1, Vector2D posX2)
{
	return sqrt(
		pow((float)(posX2.x - posX1.x), 2.0) +
		pow((float)(posX2.y - posX1.y), 2.0));
}


/*Transforme une position 3D en 2D grace a la matrice de vue.*/
//Credits to Unkowncheats.eu
__forceinline bool __fastcall worldToScreen(Vector3D *vStart, Vector2D *vOut, Memory *mem, int client) {

	float flMatrix[16] = { 0 };
	ReadProcessMemory(mem->processHandle, (PBYTE*)(client + hazedumper::signatures::dwViewMatrix), &flMatrix, sizeof(flMatrix), NULL);

	vOut->x = flMatrix[0] * vStart->x + flMatrix[1] * vStart->y + flMatrix[2] * vStart->z + flMatrix[3];
	vOut->y = flMatrix[4] * vStart->x + flMatrix[5] * vStart->y + flMatrix[6] * vStart->z + flMatrix[7];

	float flTemp = flMatrix[12] * vStart->x + flMatrix[13] * vStart->y + flMatrix[14] * vStart->z + flMatrix[15];

	if (flTemp < 0.01f)
		return false;

	float invFlTemp = 1.f / flTemp;
	vOut->x *= invFlTemp;
	vOut->y *= invFlTemp;

	float x = 1920 / 2.f;
	float y = 1080 / 2.f;

	x += 0.5f * vOut->x * 1920 + 0.5f;
	y -= 0.5f * vOut->y * 1080 + 0.5f;

	vOut->x = x;
	vOut->y = y;

	return true;
}

/*Retourne l'entitée la plus proche du viseur*/
const Vector2D screen(1920/2,1080/2);

 inline int __fastcall getClosest(Entity *e, Memory *mem, int client, int max) {
	
	int ret = 0;
	
	float index = 999999;

	for (int i = 1; i < max; i++) {
	
		if (worldToScreen(&e[i].position, &e[i].screenPosition, mem, client)  && e[i].getHealth() > 0  && get2dDistance(screen, e[i].screenPosition) < index && /* e[i].getClassID() == 35 &&*/ e[i].getIsVisible() ) {
			index = get2dDistance(screen, e[i].screenPosition);
			ret = i;
		}

	}
	return ret;
}

