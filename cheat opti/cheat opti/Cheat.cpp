#include "Cheat.h"
#include "Utils.h"
#include <iostream>
#include <vector>
using namespace std::literals::chrono_literals;

Cheat::Cheat() 
{
	mem = new Memory(L"Counter-Strike: Global Offensive");
	init();
	start();
}

Cheat::~Cheat()
{
	delete mem;
	delete[] entitys;
	delete player;
	delete bunny;
	delete glow;
	delete aimbot;
	delete fakeLag;
	delete threadBunny;
	delete threadGlow;
	delete threadReadPlayer;
	delete threadAimbot;
	delete threadGetClosest;
	delete threadReadEntitys;
	delete threadFakeLag;
}

/*Initialisation de certaines variales, et les différents instances*/
void Cheat::init()
{
	client = mem->getModuleAddress("client_panorama.dll");
	engine = mem->getModuleAddress("engine.dll");
	mem->read(client + hazedumper::signatures::dwLocalPlayer, localPlayer);

	bunny = new Bunny(mem, &localPlayer, &client);
	glow = new Glow(mem, client);
	player = new Entity(mem->read<int>(client + hazedumper::signatures::dwLocalPlayer));
	aimbot = new Aimbot(mem, &client);
	//fakeLag = new FakeLag(std::chrono::microseconds(70ms), mem, engine);

}
/*Thread qui vas stocker l'Index de l'entitée la plus proche du viseur dans la variable 'closestIndex'*/
void Cheat::getClosestEntity() {
	std::cout << "Starting thread: " << std::this_thread::get_id() << " getClosestEntity" << std::endl;
	
	while (getClosestEnabled) {
		closestIndex = getClosest(entitys, mem, client, maxPlayers );
		std::this_thread::sleep_for(10ms);
	}
	std::cout << "Thread " << std::this_thread::get_id() << " getClosestEntity termine." << std::endl;
}
/*Thread qui vas nous permettre d'exploiter le bug du moteur physique, qui nous feras courrir plus vite.*/
void Cheat::bunnyLoop() {
	std::cout << "Starting thread: " << std::this_thread::get_id() << " bunnyLoop" << std::endl;
	while (isBunnyEnabled) {
		//Si on est au sol et qu'on appuis sur la touche espace, alors on saute
		if (bunny->isOnFloor() && GetAsyncKeyState(0x20)) {
			bunny->forceJump(6);
		}

		std::this_thread::sleep_for(10ms);
	}
	std::cout << "Thread " << std::this_thread::get_id() << " bunnyLoop termine." << std::endl;
}
/*Thread qui vas nous permettre de voir les enemies à travers les murs*/
void Cheat::glowLoop() {
	std::cout << "Starting thread: " << std::this_thread::get_id() << " glowLoop" << std::endl;
	while (isGlowEnabled) {

			for (int i = 0; i < maxPlayers; i++) {

				if (entitys[i].getIndex() != closestIndex && entitys[i].getIndex() != 0) {
					glow->glow(entitys[i].getIndex(), 255.0f, 0.f, 0.f);
				}
				else {
					glow->glow(entitys[closestIndex].getIndex(), 0.0f, 255.f, 0.0f);
				}
			}
			std::this_thread::sleep_for(10ms);
	}

	std::cout << "Thread " << std::this_thread::get_id() << " glowLoop termine." << std::endl;
}
/*Thread qui vas lire les infos du joueur local (nous)*/
void Cheat::basePlayerLoop() {
	std::cout << "Starting thread: " << std::this_thread::get_id() << " basePlayerLoop" << std::endl;
	int index = 0;
	while (isBasePlayerLoop) {
		
		index = mem->read<int>(client + hazedumper::signatures::dwLocalPlayer);
		player->setIndex(index);
		player->setTeam(mem->read<int>(index + hazedumper::netvars::m_iTeamNum) );
		//player->setTaille(mem->read<float>(index + 0x108));
		//std::cout << player->getTaille() << std::endl;
		//player->setTaille(60);
		
		player->setClientState(mem->read<int>(engine + hazedumper::signatures::dwClientState));
		player->position = mem->read<Vector3D>(index + hazedumper::netvars::m_vecOrigin);

		std::this_thread::sleep_for(10ms);
	}
	std::cout << "Thread " << std::this_thread::get_id() << " basePlayerLoop termine." << std::endl;
}
/*Thread qui vas nous permettre de viser l'enemie le plus proche de notre viseur avec une très bonne précision*/
void Cheat::aimbotLoop() {
	std::cout << "Starting thread: " << std::this_thread::get_id() << " aimbotLoop" << std::endl;
	while (isAimbotEnabled) {

		if (GetAsyncKeyState(0x02) || GetAsyncKeyState(0x06) || GetAsyncKeyState(0x01)) {
			aimbot->aimTo(player, &entitys[closestIndex]);
		}
		std::this_thread::sleep_for(10ms);
	}
	std::cout << "Thread " << std::this_thread::get_id() << " aimbotLoop termine." << std::endl;
}
/*Thread permettant de couper les comunications avec le serveur pour X ms*/
void Cheat::fakeLagLoop() {
	std::cout << "Starting thread: " << std::this_thread::get_id() << " fakeLagLoop" << std::endl;
	while (isFakeLagEnabled) {
		
		fakeLag->lag();
		std::this_thread::sleep_for(10ms);

		if (GetAsyncKeyState(0x46) && GetAsyncKeyState(0x61)) { //F & 1
			fakeLag->increaseLagValue(std::chrono::microseconds(10ms));
			std::this_thread::sleep_for(150ms);
		}

		if (GetAsyncKeyState(0x46) && GetAsyncKeyState(0x63)) { //F & 3
			fakeLag->increaseLagValue(std::chrono::microseconds(-10ms));
			std::this_thread::sleep_for(150ms);
		}
		
	}

	std::cout << "Thread " << std::this_thread::get_id() << " fakeLagLoop termine." << std::endl;
}

/*Fonction qui vas créer les différents threads*/
//TO-DO: mutex & conditions
void Cheat::start()
{
	entitys = new Entity[maxPlayers];
	Sleep(30);
	threadReadPlayer = new std::thread(&Cheat::basePlayerLoop, this);
	Sleep(30);
	threadReadEntitys = new std::thread(&Cheat::readEntitys, this);
	Sleep(30);
	threadBunny = new std::thread(&Cheat::bunnyLoop, this);
	Sleep(30);
	threadGlow = new std::thread(&Cheat::glowLoop, this);
	Sleep(30);
	threadAimbot = new std::thread(&Cheat::aimbotLoop, this);
	Sleep(30);
	threadGetClosest = new std::thread(&Cheat::getClosestEntity, this);
	//Sleep(30);
	//threadFeatures = new std::thread(&Cheat::nameEsp, this);
	//threadFakeLag = new std::thread(&Cheat::fakeLagLoop, this);


}

/*Fonction incomplete*/
void Cheat::nameEsp()
{
	while (true) {

		//mem->write<Vector2D>(me->getClientState() + hazedumper::signatures::dwClientState_ViewAngles, normAngles);
		if (GetAsyncKeyState(0x01)) {
			mem->write<float>(player->getClientState() + hazedumper::netvars::m_viewPunchAngle, -90.0f);
			mem->write<float>(player->getClientState() + hazedumper::signatures::dwClientState_ViewAngles, 90.0f);

			std::cout << mem->read<float>(player->getClientState() + hazedumper::netvars::m_viewPunchAngle) << std::endl;
		}
		
		std::this_thread::sleep_for(10ms);
	}

}

int Cheat::getMaxPlayer()
{
	return this->maxPlayers;
}


/*Thread qui vas ajouter toutes les entitées valides dans un tableau*/
void Cheat::readEntitys() {
	std::cout << "Starting thread: " << std::this_thread::get_id() << " readEntitysLoop" << std::endl;

	while (isReadEntsEnabled) {

		for (int i = 0; i < maxPlayers; i++) {
			int index = mem->read<int>(client + hazedumper::signatures::dwEntityList + (i * 0x10));
			int team = mem->read<int>(index + hazedumper::netvars::m_iTeamNum);


			if (team != player->getTeam() ) {

				entitys[i].setIndex(index);		
				entitys[i].setHealth(mem->read<int>(index + hazedumper::netvars::m_iHealth));
				//entitys[i].setClassID(mem->read<int>(mem->read<int>(mem->read<int>(mem->read<int>(index + 0x8) + 0x8) + 0x1) + 0x14));
				//entitys[i].setClassID(35);
				entitys[i].setTeam(team);
				entitys[i].position = mem->read<Vector3D>(index + hazedumper::netvars::m_vecOrigin);

				entitys[i].setVisible(true/*mem->read<bool>(index + hazedumper::netvars::m_bSpotted)*/);

			}

		}

		std::this_thread::sleep_for(10ms);
	}

	std::cout << "Thread " << std::this_thread::get_id() << " readEntitys termine." << std::endl;
}

std::vector<std::thread*> Cheat::getThreads() {

	std::vector<std::thread*> myThreads;
	myThreads.reserve(6);

	//myThreads.emplace_back(threadBunny);  
	myThreads.emplace_back(threadGlow);
	myThreads.emplace_back(threadReadPlayer);
	myThreads.emplace_back(threadAimbot);
	myThreads.emplace_back(threadGetClosest);
	myThreads.emplace_back(threadReadEntitys);

	return myThreads;

}


void Cheat::enableFeatures()
{
	

}
