#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>      // std::setfill, std::setw

class Disassembler{

	private:

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

		void disassemble_instruction(const std::string& instruction) const;
};