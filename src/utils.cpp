#include "utils.hpp"


//Expects a valid filename
//store a bynary file in a byte vector
const std::vector<char> utils::file_to_byte_vector(const char* filename){

	std::ifstream myfilestream(filename, std::ios::binary | std::ios::in);
	std::istreambuf_iterator<char> file_it_start(myfilestream), file_it_end;

	return std::vector<char>(file_it_start, file_it_end);	
}

const std::vector<char> utils::string_to_byte_vector(const std::string instruction_string){
	std::vector<char> byte_vect;  
	std::string sconvert("0123456789ABCDEF");

	std::istringstream iss(instruction_string);

    while(iss){
        std::string op_byte("");
        iss >> op_byte; // get the next byte from the stream
        
        if(op_byte==""){
            break; //end of string
        }
        
        std::cout<<"code read "<<op_byte<<std::endl;

        if (op_byte.size()!=2){
          std::cerr<<"Error : the input code is expected to be 2 digits hexadecimal byte separated by spaces "<<std::endl;
          return byte_vect;
        }

        unsigned int hb = sconvert.find(op_byte[0]);
        unsigned int lb = sconvert.find(op_byte[1]);

        if (hb==std::string::npos || lb==std::string::npos){
          std::cerr<<"Error : invalid opcode character, must be among {0123456789ABCDEF} "<<std::endl;
          return byte_vect;
        }

        int val = hb*16+lb;
        byte_vect.push_back(val);
        //std::cout<<"value "<<val<<std::endl;        
    }

    return byte_vect;
}





