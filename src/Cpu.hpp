#include <vector>
#include <cstdint>

const MEM_SIZE = 65536;
const CARTRIDGE_SIZE = 32768;

struct Flag{
	Z; //Zero flag
	N; //Substract flag
	H; //Half Carry Flag
	C; // Carry flag
}

class Cpu {
	private : 
		std::vector<char> memory;
		//registers
		uint_8 A;
		uint_8 B;
		uint_8 D;
		uint_8 H;
		uint_8 F;
		uint_8 C;
		uint_8 E;
		uint_8 L;
		uint_16 SP:
		uint_16 PC;
		Flag flag;

	public :
		void Cpu();
		void loadCartridge(std::vector<char> cartridge);
		void emulate();
}