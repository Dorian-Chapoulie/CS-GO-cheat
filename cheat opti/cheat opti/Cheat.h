#pragma once
#include "Bunny.h"
#include "Glow.h"
#include "Aimbot.h"
#include "Memory.h"
#include "Entity.h"
#include "FakeLag.h"
#include <thread>
#include <vector>

/*Classe regroupant toutes les features*/
class Cheat
{
public: 
	Cheat();
	~Cheat();

	/*Thread principal*/
	void	start(); 
	/*Renvois le pseudo du joueur ayant l'ID passé en parametre, NE FONCTIONNE PAS*/
	void	nameEsp();
	int		getMaxPlayer();

	/*Retourne la liste des threads*/
	std::vector<std::thread*> getThreads();

	void enableFeatures();

private:

	void	init();
	/*Lit toutes les informations des entitées présentes (vie, position etc)*/
	void	readEntitys();
	/*Retourne l'index de l'entitée la plus proche du viseur*/
	void	getClosestEntity();

	Memory	*mem	 =	nullptr;
	Entity	*entitys =	nullptr , *player = nullptr;
	Bunny	*bunny   =	nullptr;
	Glow	*glow	 =	nullptr;
	Aimbot	*aimbot  =	nullptr;
	FakeLag *fakeLag =	nullptr;

	
	int		client			=	0;
	int		engine			=	0;
	int		maxPlayers		=	20;
	int		localPlayer		=	0;
	int		closestIndex	=	-1;

	/*Bunny*/
	void	bunnyLoop();

	/*Glow*/
	void	glowLoop();

	/*Aimbot*/
	void	aimbotLoop();

	/*Base player infos*/
	void	basePlayerLoop();

	/*Fake lag*/
	void	fakeLagLoop();

	/*Toggles*/
	bool	isBunnyEnabled	= true;
	bool	isGlowEnabled	= true;
	bool	isAimbotEnabled = true;
	bool	isFakeLagEnabled = true;
	bool	getClosestEnabled = true;
	bool	isBasePlayerLoop = true;
	bool	isReadEntsEnabled = true;

	/*Threads*/
	std::thread	*threadBunny =		nullptr;
	std::thread	*threadGlow =		nullptr;
	std::thread *threadReadPlayer = nullptr;
	std::thread *threadAimbot =		nullptr;
	std::thread *threadGetClosest = nullptr;
	std::thread *threadReadEntitys= nullptr;
	std::thread *threadFakeLag =	nullptr;
	std::thread *threadFeatures =	nullptr;
};

