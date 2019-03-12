#include "Disassembler.hpp"


void Disassembler::disassemble_instruction(const std::string &instruction_string) const
{
	std::string hexref("0123456789abcdef");

	std::stringstream s_stream(instruction_string);
	std::vector<char> char_vect;
	int number_b10;
	while(s_stream>>number_b10){
		std::cout <<"number_b10 " <<(int)number_b10<<std::endl;
		int number_b16 = 16 * (number_b10/10) + number_b10%10;
		char_vect.push_back(number_b16);
		std::cout <<"number_b16 " <<(int)number_b16<<std::endl;
	}
	for(auto c : char_vect){
		std::cout << std::hex <<(int)c<<" "<<std::endl;
	}
	//TODO : not working for letters...

}




