#include "Cpu.hpp"
#include "Disassembler.hpp"
#include "utils.hpp"
#include <vector>

int main(int argc, char* argv[]){

	//int a:
	//int b;

	std::cout << "Let's emulate!"<<std::endl;

	//Read file
    std::cout << "Cartridge file is "<< argv[1]<<std::endl;

    std::vector<char> char_vect = utils::file_to_byte_vector(argv[1]);

	std::cout << "Cartridge is "<< char_vect.size() <<" bytes long"<<std::endl;;

	Cpu cpu;
	cpu.loadCartridge(char_vect);
	cpu.print_mem(0x100, 0x103);
	//cpu.emulate();

	//TODO
	//Actually emulate
	//Code debug step by step tool

	return 0 ;
}