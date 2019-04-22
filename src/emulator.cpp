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
	std::cout << "Cartridge is "<< char_vect.size() <<" bytes long"<<std::endl;

	//Load cartidge into CPU memory
	cpu.loadCartridge(char_vect);
	std::cout << "Cartridge loaded!"<<std::endl;
	//cpu.print_mem(0x100, 2);

	//Emulate and debug
	std::cout << "Starting emulation..."<<std::endl<<std::endl;
	
	std::string input="";
	std::string cmd="s";

	while(true){
		std::cin>>input;
		cmd=input;
		// if(std::cin.get()!='\n'){
		//  	cmd=input; //if enter is pressed directly, the cmd do not change
		// }
		// else{

		// }
								
		//std::cout << "Entered  "<< input <<std::endl;

		if (cmd=="e") cpu.emulate(); //emulate next operation
		else if (cmd=="d") dis.disassemble_next_op(cpu.get_pc_iterator()); //disassemble next operation
		//case "mem" : cpu.print_mem(cpu.get_pc(), 4); break; //print memory
		else if (cmd=="pc") cpu.print_pc();
		else if (cmd=="*pc") cpu.print_mem(cpu.get_pc(), 4);
		else if (cmd=="sp") cpu.print_sp();
		else if (cmd=="*sp") cpu.print_sp_content();
		else { //(cmd=="s") //verbose display
			cpu.print_mem(cpu.get_pc(), 4);
			dis.disassemble_next_op(cpu.get_pc_iterator()); 
			cpu.emulate(); 
		}
	}


	return 0 ;
}