#include <vector>
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

const int MEM_SIZE = 65536;
const int CARTRIDGE_SIZE = 32768;

struct Flag{
	uint8_t z; //Zero flag
	uint8_t n; //Substract flag
	uint8_t h; //Half Carry Flag
	uint8_t c; // Carry flag
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

	public :
		Cpu();
		void loadCartridge(std::vector<char> cartridge);
		void emulate();
		void print_mem(int start_index=0, int end_index=0) const;
};