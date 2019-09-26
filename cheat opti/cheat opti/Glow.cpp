#include "Glow.h"



Glow::Glow(Memory *mem, int &client)
{
	this->mem = mem;
	this->client = client;
	glowObject = mem->read<int>(client + hazedumper::signatures::dwGlowObjectManager);
}


Glow::~Glow()
{
	
}

