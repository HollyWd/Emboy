#include <vector>
#include <cstdint>

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <cassert>
#include "utils.hpp"

const int MEM_SIZE = 65536;
const int CARTRIDGE_SIZE = 32768;
const int SP0 = 0xE000;
const int SPMAX = 0xDFFF;
const int SPMIN = 0xC000;

inline uint16_t word(const uint8_t lb, const uint8_t hb){ return lb + (hb<<8);}

struct Flag{
	bool z; //Zero flag
	bool n; //Substract flag
	bool h; //Half Carry Flag
	bool c; // Carry flag
};

/*! Class emulating a gameboy processor */
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
		uint16_t sp=SP0;///<Stack pointer
		uint16_t pc;///<Program counter
		Flag flag;///<Processor flag


		uint16_t get_hl() const {return word(l,h);}
		void set_hl(uint16_t nn){h=((nn && 0xF0)<<8); l=(nn && 0x0F);}

		uint16_t get_bc() const {return word(c,b);}
		uint16_t get_de() const {return word(e,d);}

		///Get the value stored at adress in HL (indirect adressing mode)
		uint16_t get_hl_ind() const {return memory[get_hl()];}
		///Get the value stored at adress in BC (indirect adressing mode)
		uint16_t get_bc_ind() const {return memory[get_bc()];}
		///Get the value stored at adress in DE (indirect adressing mode)
		uint16_t get_de_ind() const {return memory[get_de()];}		

		///Set the value stored at adress in HL (indirect adressing mode)
		void set_hl_ind(uint8_t n) {memory[get_hl()] = n;}
		///Set the value stored at adress in BC (indirect adressing mode)
		void set_bc_ind(uint8_t n) {memory[get_bc()] = n;}
		///Set the value stored at adress in DE (indirect adressing mode)
		void set_de_ind(uint8_t n) {memory[get_de()] = n;}

		///Returns the byte stored at the program counter address in the memory
		uint8_t opcode() const { return this->memory[this->pc];}
		///Returns the byte stored at program counter + 1 in the memory
		uint8_t op1() const { return this->memory[this->pc+1];}
		///Returns the byte stored at program counter + 2 in the memory
		uint8_t op2() const { return this->memory[this->pc+2];}
		///Returns the word stored at program counter + 1 in the memory
		uint16_t nn() { return word(op1(), op2());}
		///Returns the byte content at the adress strored at program counter + 1 in the memory
		uint16_t get_nn_ind() const { return word(op1(), op2());}
		///Write n at the adress strored at program counter + 1 in the memory
		void set_nn_ind(uint8_t n) { memory[word(op1(), op2())]=n;}

		void decrement_sp();
		void increment_sp();

		void decrement_hl(){set_hl(get_hl()-1);};
		void increment_hl(){set_hl(get_hl()+1);};

		///Set Cpu::sp at addr if dojump is true.
		void jump(const uint16_t addr, const bool dojump=true);
		///Store 8bit val at address Cpu::sp and decrement sp
		void push(const uint8_t val);
		///Store 16 bit val at address Cpu::sp and decrement sp twice
		///The most significant byte is pushed first
		void push(const uint16_t val);
		///Return the 16 bit value at sp and increment it twice.
		/// the most significant bit is poped first
		uint16_t pop();
		void call(const uint16_t addr, int op, const bool dojump=true);
		void ret(const bool dojump=true);

	public :
		Cpu();
		void reset();
		void load_cartridge(std::vector<char> cartridge);
		///Load the string code in memory at PC. 
		///The opcode should be in minuscule with spaces between the words. Exp: 01 0a ff.
		void load_debug_cartridge(std::string binary_string);
		void emulate();
		void print_mem(int start_index=-1, int byte_nb=1) const;
		std::vector<char>::const_iterator get_pc_iterator() const;
		int get_pc() const { return this->pc;}
		int get_sp() const { return this->sp;}
		int get_mem(const uint8_t addr) const { return memory[sp];}
		int get_stack(int offset=0) const {return (int)memory[sp+offset];}	
		void print_pc() const {std::cout<<"Program counter: "<<pc<<std::endl;}
		void print_sp() const{std::cout<<"Stack pointer:: "<<sp<<std::endl;}
		void print_stack(int offset=1) const ;


		//int getValue() const { return this->value; } 
};
	
