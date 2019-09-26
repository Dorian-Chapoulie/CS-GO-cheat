#include "Bunny.h"


Bunny::Bunny(Memory *mem, int *localPlayer, int *client)
{
	this->mem = mem;
	this->localPlayer = *localPlayer;
	this->client = *client;
}


Bunny::~Bunny()
{
	
}


