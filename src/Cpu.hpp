#include <vector>
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

const int MEM_SIZE = 65536;
const int CARTRIDGE_SIZE = 32768;

inline int word(const int lb, const int hb){ return lb + (hb<<8);}

struct Flag{
	bool z; //Zero flag
	bool n; //Substract flag
	bool h; //Half Carry Flag
	bool c; // Carry flag
};

class Cpu {
	private : 
		std::vector<char> memory;
		//registers
		uint8_t a;
		uint8_t b;
		uint8_t d;
		uint8_t h;
		uint8_t f;
		uint8_t c;
		uint8_t e;
		uint8_t l;
		uint16_t sp;
		uint16_t pc;
		Flag flag;

		int hl() const {return (this->h<<8) + this->l;}

		void jump(const int addr, const bool dojump=true);

	public :
		Cpu();
		void loadCartridge(std::vector<char> cartridge);
		void emulate();
		void print_mem(int start_index=0, int byte_nb=0) const;
		std::vector<char>::const_iterator get_pc_iterator() const;
		int get_pc() const { return this->pc;}
		int opcode() const { return this->memory[this->pc];}
		int op1() const { return this->memory[this->pc+1];}
		int op2() const { return this->memory[this->pc+2];}
		int nn() const { return word(op1(), op2());}
		void print_pc() const {std::cout<<"PC "<<this->pc<<std::endl;}

		//int getValue() const { return this->value; } 
};
	
