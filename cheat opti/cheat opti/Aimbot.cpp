#include "Aimbot.h"

Aimbot::Aimbot(Memory *memory, int *client)
{
	mem = memory;
	this->client = *client;
	screenCenter.x = 1920 / 2;
	screenCenter.y = 1080 / 2;
	ZeroMemory(boneMatrix, 3 * 4 * sizeof(float));
}


Aimbot::~Aimbot()
{

}
