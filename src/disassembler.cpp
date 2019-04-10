#include <iostream>
#include <fstream>
#include <iomanip>      // std::setfill, std::setw
#include <string> 
#include <vector> 
#include <iterator>

#include "Disassembler.hpp"

std::string string_to_hex(const std::string& input)
{
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();

    std::string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = input[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
}

void print_char_vect(std::vector<char>& vect){

	unsigned int i =0;
	while (i<vect.size()){
		printf("%04x:  ",i);
		for(size_t j=0; j<8; j++){
			std::cout<<std::hex<<std::setfill('0') << std::setw(2)<<(int)vect[i]; i++;
			std::cout<<std::hex<<std::setfill('0') << std::setw(2)<<(int)vect[i]<<" "; i++;		
		}
		std::cout<<std::endl;		
		//std::cout<<*(buffer+pc)<<std::endl;
	}
}



int main(int argc, char *argv[]) {


	//*******Load file into memory

	std::cout << "Hello, World!"<<std::endl;
    std::cout << "Input is "<< argv[1]<<std::endl;

	std::ifstream myfilestream(argv[1], std::ios::binary | std::ios::in);

	// char c = myfilestream.get();
	// while (myfilestream.good()) {
	// std::cout << c;
	// 	c = myfilestream.get();
	// }

	std::istreambuf_iterator<char> file_it_start(myfilestream), file_it_end;
	std::vector<char> char_vect(file_it_start, file_it_end);

	std::cout << "File is "<< char_vect.size() <<" bytes long"<<std::endl;

	//Hexadecimal dump to stdout
	//print_char_vect(char_vect);

	std::vector<char>::iterator it = char_vect.begin();

	Disassembler disassembler;

	while (it!=char_vect.end()){
		try{
			//std::cout<<"0x"<<std::hex<<std::setfill('0') << std::setw(2)<<(int)*it<<" ";
			std::cout<<"0x"<<std::hex<<std::setfill('0') << std::setw(2)<<it - char_vect.begin()<<" ";
			it+=disassembler.disassemble(it);

			//check that it do not overpass end
			if (size_t(it - char_vect.begin())>char_vect.size()){
				throw "Try to disassemble instruction outside of memory bounds";
			}
		}
		catch(const char * c){
			std::cerr << "Fatal error: " << c << std::endl;
			return 1;
		}
	}


    return 0;
}

