#pragma once
#include <thread>
#include "Memory.h"
using namespace std::literals::chrono_literals;

/*Cette classe vas couper les comunication avec le serveur pour X ms, donc les autres joueurs nous verrons à une position outdated*/
class FakeLag
{
public:
	FakeLag(std::chrono::microseconds ms, Memory *mem, int &engine);
	~FakeLag();

	void lag();
	void increaseLagValue(std::chrono::microseconds ms);

private:
	std::chrono::microseconds lagValue = 100ms;
	Memory *mem = nullptr;
	int engine = 0;

	byte sendPacket = 0;
	uintptr_t oldProtect;
};
