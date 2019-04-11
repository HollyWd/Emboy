#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>      // std::setfill, std::setw

class Disassembler{

	private:
		int print_cmd(const char * cmd, const char * arg1="", const char * arg2="") const;
		int print_cmd(const char * cmd, const char * arg1, const int arg2) const;
		int print_cmd(const char * cmd, const char * arg1, const int arg2_lb, const int arg2_ub) const;


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
		//int disassemble_instruction(const std::vector<char> &memory, int pc);
		int disassemble_next_op(std::vector<char>::iterator it) const;
		int disassemble_instruction(const std::string & instruction) const;
		int disassemble_all(std::vector<char>) const;
		
};