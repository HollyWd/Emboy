#include<Cpu.hpp>

Cpu Cpu::Cpu(){
	PC=100;
	this.memory = std::vector<char>(65536);
}

//TODO check that cartridge size < 32kB = 32768 octets
void Cpu::loadCartridge(std::vector<char> cartridge){

	// copy cartridge content to memory
	std::copy(cartridge.begin(), cartridge.begin()+CARTRIDGE_SIZE, this.memory.begin());
}

void Cpu::emulate(){
	
}