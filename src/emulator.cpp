#include "Cpu.hpp"
#include "Disassembler.hpp"
#include "utils.hpp"
#include <vector>
#include <string>

		void m(Cpu c, uint16_t addr){std::cout<< (int)c.get_mem(addr);}
		void m(Cpu c){c.print_mem(c.get_pc(), 5, true);}
		void r(Cpu c){ c.print_reg();}
		void fl(Cpu c){c.print_flag();}
		void s(Cpu c){c.print_stack(5);}
		void prc(Cpu c){c.print_pc();}


int main(int argc, char* argv[]){

	// Create objects
	std::cout << "Let's emulate!"<<std::endl;
	Disassembler dis;
	Cpu cpu;
	Cpu & c=cpu;

	//Read input file
    std::cout << "Cartridge file is "<< argv[1]<<std::endl;
    std::vector<char> char_vect = utils::file_to_byte_vector(argv[1]);
	std::cout << "Cartridge is "<< char_vect.size() <<" bytes long"<<std::endl;

	//Load cartidge into CPU memory
	cpu.load_cartridge(char_vect);
	std::cout << "Cartridge loaded!"<<std::endl<<std::endl;

	cpu.print_cartridge_info();
	//cpu.print_mem(0x100, 2);

	//Emulate and debug
	std::cout << "Starting emulation..."<<std::endl<<std::endl;
	
	std::string input="";
	std::string cmd="s";

	//dis.disassemble_next_op(cpu.get_pc_iterator());  

	while(true){
		// std::cin>>input;
		// cmd=input;
		// if(std::cin.get()!='\n'){
		//  	cmd=input; //if enter is pressed directly, the cmd do not change
		// }
		// else{

		// }
								
		//std::cout << "Entered  "<< input <<std::endl;

		// if (cmd=="e") cpu.emulate(); //emulate next operation
		// else if (cmd=="d") dis.disassemble_next_op(cpu.get_pc_iterator()); //disassemble next operation
		// //case "mem" : cpu.print_mem(cpu.get_pc(), 4); break; //print memory
		// else if (cmd=="mem") cpu.print_mem(cpu.get_pc(), 5, true);
		// //else if (cmd=="*pc") cpu.print_mem(cpu.get_pc(), 4);
		// else if (cmd=="stack" || cmd=="st") cpu.print_stack(5);
		// else if (cmd=="reg" || cmd=="r") cpu.print_reg();
		// else if (cmd=="flag" || cmd=="f") cpu.print_flag();
		// else { //(cmd=="s") //verbose display
		// 	cpu.print_mem(cpu.get_pc(), 4);
		// 	dis.disassemble_next_op(cpu.get_pc_iterator()); 
		// 	cpu.emulate(); 
		// }
		// 
			// 	cpu.print_mem(cpu.get_pc(), 4);	
		
		cpu.print_mem(cpu.get_pc(), 2);	
		dis.disassemble_next_op(cpu.get_pc_iterator()) 	;  
		cpu.emulate();
	}


	return 0 ;
}