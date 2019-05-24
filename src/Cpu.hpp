#include <vector>
#include <cstdint>

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <cassert>
#include "utils.hpp"

const int MEM_SIZE = 0x10000;
const int CARTRIDGE_SIZE = 0x8000;
const int SP0 = 0xFFFE;
const int SPMAX = 0xDFFF;
const int SPMIN = 0xC000;

inline uint16_t word(const uint8_t lb, const uint8_t hb){ return lb + (hb<<8);}

struct Flag{
	bool z; //Zero flag
	bool n; //Substract flag
	bool h; //Half Carry Flag
	bool c; // Carry flag

	void reset(){
		z=false;
		n=false;
		h=false;
		c=false;
	};
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

		void nullset();
		void reset();/// set all Cpu values to zero

		void set_hl(const uint16_t nn){h=((nn & 0xFF00)>>8); l=(nn & 0x00FF);}
		void set_af(const uint16_t nn){a=((nn & 0xFF00)>>8); f=(nn & 0x00FF);}
		void set_bc(const uint16_t nn){b=((nn & 0xFF00)>>8); c=(nn & 0x00FF);}
		void set_de(const uint16_t nn){d=((nn & 0xFF00)>>8); e=(nn & 0x00FF);}
		void set_sp(const uint16_t nn){sp=nn;}

		char & hl_ind(){return memory[get_hl()];} //

		///Get the value stored at adress in HL (indirect adressing mode)
		uint8_t get_hl_ind() const {return memory[get_hl()];}
		///Get the value stored at adress in BC (indirect adressing mode)
		uint8_t get_bc_ind() const {return memory[get_bc()];}
		///Get the value stored at adress in DE (indirect adressing mode)
		uint8_t get_de_ind() const {return memory[get_de()];}		

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
		signed char op1_signed() const { return (signed char)op1();}
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
		///The less significant byte is pushed first
		void push(const uint16_t val);
		///Return the 16 bit value at sp and increment it twice.
		/// the most significant bit is poped first
		uint16_t pop();
		void call(const uint16_t addr, int op, const bool dojump=true);
		void ret(const bool dojump=true);

		void bit(const uint8_t b, const uint8_t n);

		template<class T> void set(const uint8_t b, T & n);
		template<class T> void res(const uint8_t b, T & n);

		void add_8(uint8_t & dest, const uint8_t val);
		void add_8_c(uint8_t & dest, const uint8_t val);
		void sub_8(uint8_t & dest, const uint8_t val);
		void sub_8_c(uint8_t & dest, const uint8_t val);
		void and_8(uint8_t & dest, const uint8_t val);
		void or_8(uint8_t & dest, const uint8_t val);
		void xor_8(uint8_t & dest, const uint8_t val);
		void cp_8(uint8_t val1, const uint8_t val2);

		template<class T> void inc_8(T & val);
		template<class T> void dec_8(T & dest);

	public :
		Cpu();

		void load_cartridge(std::vector<char> cartridge);
		void load_cartridge(const char* file_name);

		void print_cartridge_info();
		///Load the string code in memory at PC. 
		///The opcode should be in minuscule with spaces between the words. Exp: 01 0a ff.
		void load_debug_cartridge(std::string binary_string);
		void emulate();
		
		const std::vector<char> & get_memory() const {return this->memory;}
		std::vector<char>::const_iterator get_pc_iterator() const;
		uint16_t get_pc() const { return this->pc;}
		uint16_t get_sp() const { return this->sp;}

		///Bool table displays the memory as a table if true, inline if false
		uint8_t get_mem(const uint16_t addr) const { return memory[addr];}
		uint8_t get_stack(int offset=0) const {return (int)memory[sp+offset];}	
		uint8_t get_a() const{return a;}
		uint8_t get_b() const{return b;}
		uint8_t get_d() const{return d;}
		uint8_t get_h() const{return h;}
		uint8_t get_f() const{return f;}
		uint8_t get_c() const{return c;}
		uint8_t get_e() const{return e;}
		uint8_t get_l() const{return l;}

		uint16_t get_hl() const {return word(l,h);}
		uint16_t get_bc() const {return word(c,b);}
		uint16_t get_de() const {return word(e,d);}
		uint16_t get_af() const {return word(f,a);}

		void print_mem(int start_index=-1, int byte_nb=1, bool table=false) const;
		void print_pc() const {std::cout<<"Program counter: "<<pc<<std::endl;}
		void print_sp() const{std::cout<<"Stack pointer:: "<<sp<<std::endl;}
		void print_stack(int offset=1) const ;
		void print_reg() const;
		void print_flag() const;

		//int getValue() const { return this->value; } 
};
	
