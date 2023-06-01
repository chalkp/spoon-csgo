#include <iostream>
#include "modules.h"
// TODO: write integrated dumper cuz I hate to compile it everytime to use it
//! then change every offsets in every files in ./modules/

int main(int, char**) {
	// setup
	const Memory csgo = Memory("csgo.exe");
	const std::uintptr_t client = csgo.getAddress("client.dll");
	if (client == 0) {
		std::cerr << "client.dll not found!" << std::endl;
		return 1;
	}
	std::cout << "client.dll found: 0x" << std::hex << client << std::endl;


	while (true) {
		
		bhop(csgo, client);
	}
	return 0;
}