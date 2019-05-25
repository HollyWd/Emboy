#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>      // std::setfill, std::setw

class Disassembler{

	private:

		//CMD 1
		int print_cmd(const char * cmd, const int arg1) const;
		//CMD 1,2
		int print_cmd(const char * cmd, const int arg1_lb, const int arg1_ub) const;//CMD A,1
		// CMD (A)(,B)
		int print_cmd(const char * cmd, const char * arg1=NULL, const char * arg2=NULL) const;

		int print_cmd(const char * cmd, const char * arg1, const int arg2) const;
		//CMD A,12
		int print_cmd(const char * cmd, const char * arg1, const int arg2_lb, const int arg2_ub) const;
		//CMD 1,A
		int print_cmd(const char * cmd, const int arg1, const char * arg2) const;

	public:
		/**
		 * @brief Desassemble instruction from memory
		 * @details Print the assembly code of the instruction at index pc in the memory and return the number of opbytes used by this instruction.
		 * 
		 * @param memory Memory to read from. It is a vector of char.
		 * @param pc Memory index to read from.
		 * 
		 * @return number of opbytes used by the instruction (1 to 3 usually)
		 */
		//int disassemble_instruction(const std::vector<uint8_t> &memory, int pc);
		int disassemble_next_op(std::vector<uint8_t>::const_iterator it) const;
		int disassemble_instruction(const std::string & instruction) const;
		int disassemble_all(std::vector<uint8_t>) const;
		
};