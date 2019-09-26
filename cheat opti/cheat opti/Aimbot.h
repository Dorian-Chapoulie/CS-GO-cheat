#pragma once
#include "Entity.h"
#include "Memory.h"
#include "offsets.h"
#include "Utils.h"
#include <iostream>
#include <chrono>
#include <thread>
using namespace std::literals::chrono_literals;
/*Classe permetant de viser en temps réel sur un énemie avec un précision flotante.*/
class Aimbot
{
public:
	Aimbot(Memory *memory, int *client);
	~Aimbot();

	/*Cette fonction vas changer les valeurs du vecteur correspondant au curseur, pour le mettre au niveau de la tête de l'énemie passé en parametre.*/
	 void __fastcall aimTo(Entity *me, Entity *target) {

		if (target->getHealth() <= 0) {
			return;
		}
	
		mem->read<Vector2D>(me->getClientState() + hazedumper::signatures::dwClientState_ViewAngles, myAngles);

		target->setBoneMatrice(mem->read<int>(target->getIndex() + hazedumper::netvars::m_dwBoneMatrix));

		ReadProcessMemory(mem->processHandle, (int*)(target->getBoneMatrice() + (0x30 * bone)), &boneMatrix, 3 * 4 * sizeof(float), NULL);

		enemy.x = boneMatrix[0][3];
		enemy.y = boneMatrix[1][3];
		enemy.z = boneMatrix[2][3] - 60;

		angRotation = CalcAngle(&me->position, &enemy);
		
		/*
		if (target->getIsVisible()) {

				mem->write<int>(client + hazedumper::signatures::dwForceAttack, 1);
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
				mem->write<int>(client + hazedumper::signatures::dwForceAttack, 4);

				recoilControl(&angRotation, me);	
				return;
		}
		*/

		if (GetAsyncKeyState(0x2) || GetAsyncKeyState(0x06) || mem->read<int>(me->getIndex() + hazedumper::netvars::m_iShotsFired)) {

			if (myAngles.x >= angRotation.x - fov &&
				myAngles.x <= angRotation.x + fov &&
				myAngles.y >= angRotation.y - fov &&
				myAngles.y <= angRotation.y + fov) {
				
				recoilControl(&angRotation, me);
			}
		
		}

	}

	/*Cette fonction se charge de compenser le recul de l'arme*/
	//Credits to Unkowncheats.eu
	 void __fastcall recoilControl(Vector2D *currentViewAngles, Entity *me) {

		punch = mem->read<Vector2D>(me->getIndex() + hazedumper::netvars::m_aimPunchAngle);

		normAngles.x = currentViewAngles->x - punch.x * 1.97f;
		normAngles.y = currentViewAngles->y - punch.y * 1.97f;

		mem->write<Vector2D>(me->getClientState() + hazedumper::signatures::dwClientState_ViewAngles, normAngles);
	}

private:
	int bone = 8; //L'os n°8 correspond à la tête.
	int fov = 50; //Distance max entre un enemie et notre curseur
	int client;	//Adresse de client.dll

	Memory *mem = nullptr;

	float boneMatrix[3][4] = { 0 };//matrice de la position des os
	Vector3D enemy;
	Vector2D normAngles, punch, angRotation, screenCenter, myAngles;
};

