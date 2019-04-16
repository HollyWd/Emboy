#include <vector>
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <cassert>

const int MEM_SIZE = 65536;
const int CARTRIDGE_SIZE = 32768;
const int SP0 = 0xE000;
const int SPMAX = 0xDFFF;
const int SPMIN = 0xC000;

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
		uint16_t sp=SP0;
		uint16_t pc;
		Flag flag;

		uint16_t hl() const {return (this->h<<8) + this->l;}
		
		uint8_t opcode() const { return this->memory[this->pc];}
		uint8_t op1() const { return this->memory[this->pc+1];}
		uint8_t op2() const { return this->memory[this->pc+2];}
		uint16_t nn() const { return word(op1(), op2());}

		void decrement_sp();

		void jump(const uint16_t addr, const bool dojump=true);
		void push(const uint8_t val);
		void push(const uint16_t val);
		void call(const uint16_t addr, const bool dojump=true);

	public :
		Cpu();
		void loadCartridge(std::vector<char> cartridge);
		void emulate();
		void print_mem(int start_index=0, int byte_nb=0) const;
		std::vector<char>::const_iterator get_pc_iterator() const;
		int get_pc() const { return this->pc;}	
		void print_pc() const {std::cout<<"PC "<<this->pc<<std::endl;}


		//int getValue() const { return this->value; } 
};
	
