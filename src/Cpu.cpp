#include "Cpu.hpp"

Cpu::Cpu(){
	this->pc=100;
	this->memory = std::vector<char>(65536);
}

//TODO check that cartridge size < 32kB = 32768 octets
void Cpu::loadCartridge(std::vector<char> cartridge){

	// copy cartridge content to memory
	std::copy(cartridge.begin(), cartridge.begin()+CARTRIDGE_SIZE, this->memory.begin());
}

void Cpu::emulate(){

	std::for_each(this->memory.begin()+0x100, this->memory.begin()+0x150, [](char c){std::cout<<c<<"";});
}

void Cpu::print_mem(int start_index, int end_index) const{
	if(start_index==0 && end_index==0){
		end_index=MEM_SIZE;
	}
	else if(end_index==0){
		end_index=start_index+1;
	}
	// for (int i=start_index; i<end_index; i++){
	// 	std::cout<<std::hex<<std::setfill('0') << std::setw(4)<<i<<"    "<<(int)this->memory[i]<<std::endl;
	// }

	int i = start_index;
	while (i<end_index){
		printf("0x%04x:  ",i);
		for(size_t j=0; j<8; j++){
			if (i>end_index) break;
			std::cout<<std::hex<<std::setfill('0') << std::setw(2)<<(int)this->memory[i]; i++;
			if (i>end_index) break;
			std::cout<<std::hex<<std::setfill('0') << std::setw(2)<<(int)this->memory[i]<<" "; i++;		
		}
		std::cout<<std::endl;		
		//std::cout<<*(buffer+pc)<<std::endl;
	}
}