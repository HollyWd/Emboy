#include "Disassembler.hpp"


void Disassembler::disassemble_instruction(const std::string &instruction_string) const
{
  std::vector<char> byte_vect;
//Convert string to a vector of byte
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
          return 1;
        }

        int hb = sconvert.find(op_byte[0]);
        int lb = sconvert.find(op_byte[1]);

        int val = hb*16+lb;
        byte_vect.push_back(val);
        std::cout<<"value "<<val<<std::endl;        
    }
	//TODO disassemble(byte_vector)
    return 0;
}
    //// to test do
    //std::string s;
    //std::getline(std::cin,s);
    //disassemble_instruction(s);
    //
    //return 0;


