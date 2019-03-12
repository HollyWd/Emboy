#include "Disassembler.hpp"

int main(){
	std::cout<<"Hello world!"<<std::endl;
	Disassembler disassembler;
	disassembler.disassemble_instruction("01 02 03 11 ff");
}