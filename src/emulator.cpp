#include "Cpu.hpp"
#include "Disassembler.hpp"
#include "utils.hpp"
#include <vector>
#include <string>

int main(int argc, char* argv[]){

	// Create objects
	std::cout << "Let's emulate!"<<std::endl;
	Disassembler dis;
	Cpu cpu;

	//Read input file
    std::cout << "Cartridge file is "<< argv[1]<<std::endl;
    std::vector<char> char_vect = utils::file_to_byte_vector(argv[1]);
	std::cout << "Cartridge is "<< char_vect.size() <<" bytes long"<<std::endl;;

	//Load cartidge into CPU memory
	cpu.loadCartridge(char_vect);
	std::cout << "Cartridge loaded!"<<std::endl;
	//cpu.print_mem(0x100, 2);

	//Emulate and debug
	std::cout << "Starting emulation..."<<std::endl<<std::endl;
	
	char input=0;
	char cmd='v';

	while(true){
		input = std::cin.get();	
					
		if(input!='\n'){
			cmd=input; //if enter is pressed directly, the cmd do not change
		}

		switch (cmd){
			case 'n' : cpu.emulate(); break; //emulate next operation
			case 'd' : dis.disassemble_next_op(cpu.get_pc_iterator()); break; //disassemble next operation
			case 'm' : cpu.print_mem(cpu.get_pc(), 4); break; //print memory
			case 'v' : //verbose display
				cpu.print_mem(cpu.get_pc(), 4);
				dis.disassemble_next_op(cpu.get_pc_iterator()); 
				cpu.emulate(); 
				break;
		}
	}

	return 0 ;
}