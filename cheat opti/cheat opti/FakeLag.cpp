#include "FakeLag.h"
#include "offsets.h"


FakeLag::FakeLag(std::chrono::microseconds ms, Memory *mem, int &engine)
{
	this->lagValue = ms;
	this->mem = mem;
	this->engine = engine;
}


FakeLag::~FakeLag()
{
	
}

//Credits to Unkowncheats.eu
void FakeLag::lag() {
	
	sendPacket = 0;
	VirtualProtectEx(mem->processHandle, (LPVOID)(engine + hazedumper::signatures::dwbSendPackets), sizeof(sendPacket), PAGE_EXECUTE_READWRITE, reinterpret_cast<DWORD*>(&oldProtect));
	mem->write<byte>(engine + hazedumper::signatures::dwbSendPackets, sendPacket);
	VirtualProtectEx(mem->processHandle, (LPVOID)(engine + hazedumper::signatures::dwbSendPackets), sizeof(sendPacket), oldProtect, NULL);

	std::this_thread::sleep_for(this->lagValue);
	sendPacket = 1;

	VirtualProtectEx(mem->processHandle, (LPVOID)(engine + hazedumper::signatures::dwbSendPackets), sizeof(sendPacket), PAGE_EXECUTE_READWRITE, reinterpret_cast<DWORD*>(&oldProtect));
	mem->write<byte>(engine + hazedumper::signatures::dwbSendPackets, sendPacket);
	VirtualProtectEx(mem->processHandle, (LPVOID)(engine + hazedumper::signatures::dwbSendPackets), sizeof(sendPacket), oldProtect, NULL);
}

void FakeLag::increaseLagValue(std::chrono::microseconds ms) {
	lagValue += ms;
}