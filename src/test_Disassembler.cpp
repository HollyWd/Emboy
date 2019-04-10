#include "Disassembler.hpp"

int main(){
	std::cout<<"Hello world!"<<std::endl;
	Disassembler disassembler;
	disassembler.disassemble_instruction("01 02 03 0A A0 11 FF 000 a0");

	//todo understand why iterator makes compilation issue in dissasemble function..
}