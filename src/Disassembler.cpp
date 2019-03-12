#include "Disassembler.hpp"


void Disassembler::disassemble_instruction(const std::string &instruction_string) const
{
	std::stringstream s_stream(instruction_string);
	std::vector<char> char_vect;
	int number_b10;
	while(s_stream>>number_b10){
		int number_b16 = 16 * number_b10/10 + number_b10%10;
		char_vect.push_back(number_b16);
	}
	for(auto c : char_vect){
		std::cout << std::hex << std::setfill('0') << std::setw(2)<<(int)c<<" "<<std::endl;
	}

}




