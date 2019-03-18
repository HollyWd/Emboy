#include "Cpu.hpp"

int main(int argc, char* argv[]){

	//int a:
	//int b;

	std::cout << "Test Cpu class!"<<std::endl;

	//Read file
    std::cout << "Cartridge file is "<< argv[1]<<std::endl;

	std::ifstream myfilestream(argv[1], std::ios::binary | std::ios::in);

	std::istreambuf_iterator<char> file_it_start(myfilestream), file_it_end;
	std::vector<char> char_vect(file_it_start, file_it_end);

	std::cout << "Cartridge is "<< char_vect.size() <<" bytes long"<<std::endl;;

	Cpu cpu;
	cpu.loadCartridge(char_vect);
	cpu.emulate();

	// for (auto c : cpu.memory){
	// 	std::cout << c;
	// }

	return 0 ;
}