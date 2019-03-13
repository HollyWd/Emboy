#include <vector>
#include <cstdint>

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
		Cpu();
		loadCartridge(std::vector<char> cartridge);
		emulate();
}