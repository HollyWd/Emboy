#include <iostream>
#include <fstream>
#include <iomanip>      // std::setfill, std::setw
#include <string> 
#include <vector> 
#include <iterator>

std::string string_to_hex(const std::string& input)
{
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();

    std::string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = input[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
}

void print_char_vect(std::vector<char>& vect){

	unsigned int i =0;
	while (i<vect.size()){
		printf("%04x:  ",i);
		for(size_t j=0; j<8; j++){
			std::cout<<std::hex<<std::setfill('0') << std::setw(2)<<(int)vect[i]; i++;
			std::cout<<std::hex<<std::setfill('0') << std::setw(2)<<(int)vect[i]<<" "; i++;		
		}
		std::cout<<std::endl;		
		//std::cout<<*(buffer+pc)<<std::endl;
	}
}

// char char_to_byte(char c){
// 	return (int)c;
// }

int dissasemble_LD(char arg1, int arg2){
	std::cout<<"LD "<<arg1<<",$"<<arg2<<std::endl; 
	return 2; //opbytes
}

int dissasemble_LD(char arg1, char arg2){
	std::cout<<"LD "<<arg1<<","<<arg2<<std::endl; 
	return 1; //opbytes
}

int dissasemble_LD(char arg1, const char * arg2){
	std::cout<<"LD "<<arg1<<","<<arg2<<std::endl; 
	return 1; //opbytes
}

int dissasemble_LD(const char *arg1, int arg2){
	std::cout<<"LD "<<arg1<<",$"<<arg2<<std::endl; 
	return 2; //opbytes
}

int dissasemble_LD(const char *arg1, char arg2){
	std::cout<<"LD "<<arg1<<","<<arg2<<std::endl; 
	return 1; //opbytes
}

int disassemble(std::vector<char>::iterator& it){
	
	//std::cout<<"opcode = "<<std::hex << opcode <<std::endl; 
	int opcode = *it;
	int opbytes = 1; //number of bytes used by the operator
	int add1 = 0;

	switch(opcode){
		case 0x00 : std::cout<<"NOP"<<std::endl; break;

		//LD
		case 0x06 : opbytes = dissasemble_LD('B', (int)*(it+1)); break;	
		case 0x0e : opbytes = dissasemble_LD('C', (int)*(it+1)); break;	
		case 0x16 : opbytes = dissasemble_LD('D', (int)*(it+1)); break;	
		case 0x1E : opbytes = dissasemble_LD('E', (int)*(it+1)); break;	
		case 0x26 : opbytes = dissasemble_LD('H', (int)*(it+1)); break;	
		case 0x2E : opbytes = dissasemble_LD('L', (int)*(it+1)); break;	
		case 0x3E : opbytes = dissasemble_LD('A', (int)*(it+1));break;
		case 0x36 : std::cout<<"(HL),$"<<(int)*(it+1)<<std::endl; opbytes = 2; break;
		

		
		case 0x78 : opbytes = dissasemble_LD('A', 'B'); break;
		case 0x79 : opbytes = dissasemble_LD('A', 'C'); break;
		case 0x7A : opbytes = dissasemble_LD('A', 'D'); break;
		case 0x7B : opbytes = dissasemble_LD('A', 'E'); break;
		case 0x7C : opbytes = dissasemble_LD('A', 'H'); break;
		case 0x7D : opbytes = dissasemble_LD('A', 'L'); break;
		case 0x7E : opbytes = dissasemble_LD('A', "(HL)"); break;
		case 0x7F : opbytes = dissasemble_LD('A', 'A'); break;
		case 0x40 : opbytes = dissasemble_LD('B', 'B'); break;
		case 0x41 : opbytes = dissasemble_LD('B', 'C'); break;
		case 0x42 : opbytes = dissasemble_LD('B', 'D'); break;
		case 0x43 : opbytes = dissasemble_LD('B', 'E'); break;
		case 0x44 : opbytes = dissasemble_LD('B', 'H'); break;
		case 0x45 : opbytes = dissasemble_LD('B', 'L'); break;
		case 0x46 : opbytes = dissasemble_LD('B', "(HL)"); break;
		case 0x47 : opbytes = dissasemble_LD('B', 'A'); break;
		case 0x48 : opbytes = dissasemble_LD('C', 'B'); break;
		case 0x49 : opbytes = dissasemble_LD('C', 'C'); break;
		case 0x4A : opbytes = dissasemble_LD('C', 'D'); break;
		case 0x4B : opbytes = dissasemble_LD('C', 'E'); break;
		case 0x4C : opbytes = dissasemble_LD('C', 'H'); break;
		case 0x4D : opbytes = dissasemble_LD('C', 'L'); break;
		case 0x4E : opbytes = dissasemble_LD('C', "(HL)"); break;
		case 0x4F : opbytes = dissasemble_LD('C', 'A'); break;
		case 0x50 : opbytes = dissasemble_LD('D', 'B'); break;
		case 0x51 : opbytes = dissasemble_LD('D', 'C'); break;
		case 0x52 : opbytes = dissasemble_LD('D', 'D'); break;
		case 0x53 : opbytes = dissasemble_LD('D', 'E'); break;
		case 0x54 : opbytes = dissasemble_LD('D', 'H'); break;
		case 0x55 : opbytes = dissasemble_LD('D', 'L'); break;
		case 0x56 : opbytes = dissasemble_LD('D', "(HL)"); break;
		case 0x57 : opbytes = dissasemble_LD('D', 'A'); break;
		case 0x58 : opbytes = dissasemble_LD('E', 'B'); break;
		case 0x59 : opbytes = dissasemble_LD('E', 'C'); break;
		case 0x5A : opbytes = dissasemble_LD('E', 'D'); break;
		case 0x5B : opbytes = dissasemble_LD('E', 'E'); break;
		case 0x5C : opbytes = dissasemble_LD('E', 'H'); break;
		case 0x5D : opbytes = dissasemble_LD('E', 'L'); break;
		case 0x5E : opbytes = dissasemble_LD('E', "(HL)"); break;
		case 0x5F : opbytes = dissasemble_LD('E', 'A'); break;
		case 0x60 : opbytes = dissasemble_LD('H', 'B'); break;
		case 0x61 : opbytes = dissasemble_LD('H', 'C'); break;
		case 0x62 : opbytes = dissasemble_LD('H', 'D'); break;
		case 0x63 : opbytes = dissasemble_LD('H', 'E'); break;
		case 0x64 : opbytes = dissasemble_LD('H', 'H'); break;
		case 0x65 : opbytes = dissasemble_LD('H', 'L'); break;
		case 0x66 : opbytes = dissasemble_LD('H', "(HL)"); break;
		case 0x67 : opbytes = dissasemble_LD('H', 'A'); break;
		case 0x68 : opbytes = dissasemble_LD('L', 'B'); break;
		case 0x69 : opbytes = dissasemble_LD('L', 'C'); break;
		case 0x6A : opbytes = dissasemble_LD('L', 'D'); break;
		case 0x6B : opbytes = dissasemble_LD('L', 'E'); break;
		case 0x6C : opbytes = dissasemble_LD('L', 'H'); break;
		case 0x6D : opbytes = dissasemble_LD('L', 'L'); break;
		case 0x6E : opbytes = dissasemble_LD('L', "(HL)"); break;
		case 0x6F : opbytes = dissasemble_LD('L', 'A'); break;
		case 0x70 : opbytes = dissasemble_LD("(HL)", 'B'); break;
		case 0x71 : opbytes = dissasemble_LD("(HL)", 'C'); break;
		case 0x72 : opbytes = dissasemble_LD("(HL)", 'D'); break;
		case 0x73 : opbytes = dissasemble_LD("(HL)", 'E'); break;
		case 0x74 : opbytes = dissasemble_LD("(HL)", 'H'); break;
		case 0x75 : opbytes = dissasemble_LD("(HL)", 'L'); break;
		case 0x77 : opbytes = dissasemble_LD("(HL)",'A'); break;

		case 0x0A : opbytes = dissasemble_LD('A',"(BC)"); break;
		case 0x1A : opbytes = dissasemble_LD('A',"(DE)"); break;


		case 0x02 : opbytes = dissasemble_LD("(BC)",'A'); break;
		case 0x12 : opbytes = dissasemble_LD("(DE)",'A'); break;
		
		case 0xEA : 
		{	//LD (nn),A
			int nn=*(it+1)+(*(it+2)<<8);
			std::cout<< "LD $(" << nn << "),A" << std::endl; opbytes = 3; 
			break;
		}
		case 0xFA : // LD A nn
			{	//LD A,(nn)
			int nn=*(it+1)+(*(it+2)<<8);
			std::cout<< "LD A,$(" << nn << ")"<<std::endl; opbytes = 3; 
			break;
		}
				
		case 0xE2 : opbytes = dissasemble_LD("($FF00+C)",'A'); break;
		case 0xF2 : opbytes = dissasemble_LD('A',"($FF00+C)"); break;

		case 0x3a : opbytes = dissasemble_LD('A',"(HLD)"); break;
		case 0x32 : opbytes = dissasemble_LD("(HLD)",'A'); break;
	
		case 0x2a : opbytes = dissasemble_LD('A',"(HLI)"); break;
		case 0x22 : opbytes = dissasemble_LD("(HLI)",'A'); break;

		case 0xE0 : 
		{
			int n=*(it+1);
			std::cout<< "LD ($FF00+" << n << "),A" << std::endl; opbytes = 2; 
			break;
		}
		case 0xF0 : 		
		{
			int n=*(it+1);
			std::cout<< "LD A, ($FF00+" << n << ")" << std::endl; opbytes = 2; 
			break;
		}


		//LD 16
		case 0x01 : dissasemble_LD("BC", (int)(*(it+1)+(*(it+2)<<8))); opbytes = 3; break;
		case 0x11 : dissasemble_LD("DE", (int)(*(it+1)+(*(it+2)<<8))); opbytes = 3; break;
		case 0x21 : dissasemble_LD("HL", (int)(*(it+1)+(*(it+2)<<8))); opbytes = 3; break;
		case 0x31 : dissasemble_LD("SP", (int)(*(it+1)+(*(it+2)<<8))); opbytes = 3; break;

		case 0xF9 : std::cout<<"LDHL SP, HL"<<std::endl; opbytes = 1; break;

		case 0xF8 : std::cout<<"LDHL SP,$"<<(int)*(it+1)<<std::endl; opbytes = 2; break;

		case 0x08 : {
			int nn = *(it+1)+(*(it+2)<<8);
			std::cout<<"LD $"<<nn<<",SP"<<std::endl;
			opbytes = 3;
			break;
		}

		//POP PUSH

		case 0xF5 : std::cout<<"PUSH AF"<<std::endl; opbytes = 1; break;
		case 0xC5 : std::cout<<"PUSH BC"<<std::endl; opbytes = 1; break;
		case 0xD5 : std::cout<<"PUSH DE"<<std::endl; opbytes = 1; break;
		case 0xE5 : std::cout<<"PUSH HL"<<std::endl; opbytes = 1; break;

		case 0xF1 : std::cout<<"POP AF"<<std::endl; opbytes = 1; break;
		case 0xC1 : std::cout<<"POP BC"<<std::endl; opbytes = 1; break;
		case 0xD1 : std::cout<<"POP DE"<<std::endl; opbytes = 1; break;
		case 0xE1 : std::cout<<"POP HL"<<std::endl; opbytes = 1; break;

		//ADD		
		case 0x87 : std::cout<<"ADD A,A"<<std::endl; opbytes = 1; break;
		case 0x80 : std::cout<<"ADD A,B"<<std::endl; opbytes = 1; break;
		case 0x81 : std::cout<<"ADD A,C"<<std::endl; opbytes = 1; break;
		case 0x82 : std::cout<<"ADD A,D"<<std::endl; opbytes = 1; break;
		case 0x83 : std::cout<<"ADD A,E"<<std::endl; opbytes = 1; break;
		case 0x84 : std::cout<<"ADD A,H"<<std::endl; opbytes = 1; break;
		case 0x85 : std::cout<<"ADD A,L"<<std::endl; opbytes = 1; break;
		case 0x86 : std::cout<<"ADD A,(HL)"<<std::endl; opbytes = 1; break;
		case 0xC6 : std::cout<<"ADD A,$"<<(int)*(it+1)<<std::endl; opbytes = 2; break;

		case 0x8F : std::cout<<"ADC A,A"<<std::endl; opbytes = 1; break;
		case 0x88 : std::cout<<"ADC A,B"<<std::endl; opbytes = 1; break;
		case 0x89 : std::cout<<"ADC A,C"<<std::endl; opbytes = 1; break;
		case 0x8A : std::cout<<"ADC A,D"<<std::endl; opbytes = 1; break;
		case 0x8B : std::cout<<"ADC A,E"<<std::endl; opbytes = 1; break;
		case 0x8C : std::cout<<"ADC A,H"<<std::endl; opbytes = 1; break;
		case 0x8D : std::cout<<"ADC A,L"<<std::endl; opbytes = 1; break;
		case 0x8E : std::cout<<"ADC A,(HL)"<<std::endl; opbytes = 1; break;
		case 0xCE : std::cout<<"ADC A,$"<<(int)*(it+1)<<std::endl; opbytes = 2; break;

		//ALU
		case 0x97 : std::cout<<"SUB A"<<std::endl; opbytes = 1; break;
		case 0x90 : std::cout<<"SUB B"<<std::endl; opbytes = 1; break;
		case 0x91 : std::cout<<"SUB C"<<std::endl; opbytes = 1; break;
		case 0x92 : std::cout<<"SUB D"<<std::endl; opbytes = 1; break;
		case 0x93 : std::cout<<"SUB E"<<std::endl; opbytes = 1; break;
		case 0x94 : std::cout<<"SUB H"<<std::endl; opbytes = 1; break;
		
		case 0x95 : std::cout<<"SUB L"<<std::endl; opbytes = 1; break;
		case 0x96 : std::cout<<"SUB (HL)"<<std::endl; opbytes = 1; break;
		case 0xD6 : std::cout<<"SUB "<<(int)*(it+1)<<std::endl; opbytes = 2; break;

		case 0x9F : std::cout<<"SBC A,A"<<std::endl; opbytes = 1; break;
		case 0x98 : std::cout<<"SBC A,B"<<std::endl; opbytes = 1; break;
		case 0x99 : std::cout<<"SBC A,C"<<std::endl; opbytes = 1; break;
		case 0x9A : std::cout<<"SBC A,D"<<std::endl; opbytes = 1; break;
		case 0x9B : std::cout<<"SBC A,E"<<std::endl; opbytes = 1; break;
		case 0x9C : std::cout<<"SBC A,H"<<std::endl; opbytes = 1; break;
		case 0x9D : std::cout<<"SBC A,L"<<std::endl; opbytes = 1; break;
		case 0x9E : std::cout<<"SBC A,(HL)"<<std::endl; opbytes = 1; break;
		case 0xDE : std::cout<<"SBC A,$"<<(int)*(it+1)<<std::endl; opbytes = 2; break;

		case 0xA7 : std::cout<<"AND A"<<std::endl; opbytes = 1; break;
		case 0xA0 : std::cout<<"AND B"<<std::endl; opbytes = 1; break;
		case 0xA1 : std::cout<<"AND C"<<std::endl; opbytes = 1; break;
		case 0xA2 : std::cout<<"AND D"<<std::endl; opbytes = 1; break;
		case 0xA3 : std::cout<<"AND E"<<std::endl; opbytes = 1; break;
		case 0xA4 : std::cout<<"AND H"<<std::endl; opbytes = 1; break;
		case 0xA5 : std::cout<<"AND L"<<std::endl; opbytes = 1; break;
		case 0xA6 : std::cout<<"AND (HL)"<<std::endl; opbytes = 1; break;
		case 0xE6 : std::cout<<"AND $"<<(int)*(it+1)<<std::endl; opbytes = 2; break;

		case 0xB7 : std::cout<<"OR A"<<std::endl; opbytes = 1; break;
		case 0xB0 : std::cout<<"OR B"<<std::endl; opbytes = 1; break;
		case 0xB1 : std::cout<<"OR C"<<std::endl; opbytes = 1; break;
		case 0xB2 : std::cout<<"OR D"<<std::endl; opbytes = 1; break;
		case 0xB3 : std::cout<<"OR E"<<std::endl; opbytes = 1; break;
		case 0xB4 : std::cout<<"OR H"<<std::endl; opbytes = 1; break;
		case 0xB5 : std::cout<<"OR L"<<std::endl; opbytes = 1; break;
		case 0xB6 : std::cout<<"OR (HL)"<<std::endl; opbytes = 1; break;
		case 0xF6 : std::cout<<"OR $"<<(int)*(it+1)<<std::endl; opbytes = 2; break;

		case 0xAF : std::cout<<"XOR A"<<std::endl; opbytes = 1; break;
		case 0xA8 : std::cout<<"XOR B"<<std::endl; opbytes = 1; break;
		case 0xA9 : std::cout<<"XOR C"<<std::endl; opbytes = 1; break;
		case 0xAA : std::cout<<"XOR D"<<std::endl; opbytes = 1; break;
		case 0xAB : std::cout<<"XOR E"<<std::endl; opbytes = 1; break;
		case 0xAC : std::cout<<"XOR H"<<std::endl; opbytes = 1; break;
		case 0xAD : std::cout<<"XOR L"<<std::endl; opbytes = 1; break;
		case 0xAE : std::cout<<"XOR (HL)"<<std::endl; opbytes = 1; break;
		case 0xEE : std::cout<<"XOR $"<<(int)*(it+1)<<std::endl; opbytes = 2; break;

		case 0xBF : std::cout<<"CP  A"<<std::endl; opbytes = 1; break;
		case 0xB8 : std::cout<<"CP  B"<<std::endl; opbytes = 1; break;
		case 0xB9 : std::cout<<"CP  C"<<std::endl; opbytes = 1; break;
		case 0xBA : std::cout<<"CP  D"<<std::endl; opbytes = 1; break;
		case 0xBB : std::cout<<"CP  E"<<std::endl; opbytes = 1; break;
		case 0xBC : std::cout<<"CP  H"<<std::endl; opbytes = 1; break;
		case 0xBD : std::cout<<"CP  L"<<std::endl; opbytes = 1; break;
		case 0xBE : std::cout<<"CP  (HL)"<<std::endl; opbytes = 1; break;
		case 0xFE : std::cout<<"CP  $"<<(int)*(it+1)<<std::endl; opbytes = 2; break;

		case 0x3C : std::cout<<"INC A"<<std::endl; opbytes = 1; break;
		case 0x04 : std::cout<<"INC B"<<std::endl; opbytes = 1; break;
		case 0x0C : std::cout<<"INC C"<<std::endl; opbytes = 1; break;
		case 0x14 : std::cout<<"INC D"<<std::endl; opbytes = 1; break;
		case 0x1C : std::cout<<"INC E"<<std::endl; opbytes = 1; break;
		case 0x24 : std::cout<<"INC H"<<std::endl; opbytes = 1; break;
		case 0x2C : std::cout<<"INC L"<<std::endl; opbytes = 1; break;
		case 0x34 : std::cout<<"INC (HL)"<<std::endl; opbytes = 1; break;

		case 0x3D : std::cout<<"DEC A"<<std::endl; opbytes = 1; break;
		case 0x05 : std::cout<<"DEC B"<<std::endl; opbytes = 1; break;
		case 0x0D : std::cout<<"DEC C"<<std::endl; opbytes = 1; break;
		case 0x15 : std::cout<<"DEC D"<<std::endl; opbytes = 1; break;
		case 0x1D : std::cout<<"DEC E"<<std::endl; opbytes = 1; break;
		case 0x25 : std::cout<<"DEC H"<<std::endl; opbytes = 1; break;
		case 0x2D : std::cout<<"DEC L"<<std::endl; opbytes = 1; break;
		case 0x35 : std::cout<<"DEC (HL)"<<std::endl; opbytes = 1; break;

		//JP
		case 0xc3 : 
			std::cout<<"JP ";
			add1 = *(it+1) + (*(it+2)<<8); // Less significan byte first TODO, test the jump adress, is it correct?
			std::cout<<"$"<<std::hex<<std::setfill('0') << std::setw(4)<<add1<<std::endl;
			opbytes=3; 
			break;

		case 0xff : 
			std::cout<<"RST ";
			add1 = *(it+1) + (*(it+2)<<4); // Less significan byte first
			std::cout<<"$38"<<std::endl; //TODO What is $38, the value of a register?
			opbytes=1; 
			break;

	    default:
	        std::cout<<"Instruction not implemented yet"<<std::endl;
	}
	return opbytes;
}

int main(int argc, char *argv[]) {


	//*******Load file into memory

	std::cout << "Hello, World!"<<std::endl;
    std::cout << "Input is "<< argv[1]<<std::endl;

	std::ifstream myfilestream(argv[1], std::ios::binary | std::ios::in);

	// char c = myfilestream.get();
	// while (myfilestream.good()) {
	// std::cout << c;
	// 	c = myfilestream.get();
	// }

	std::istreambuf_iterator<char> file_it_start(myfilestream), file_it_end;
	std::vector<char> char_vect(file_it_start, file_it_end);

	std::cout << "File is "<< char_vect.size() <<" bytes long"<<std::endl;;

	//Hexadecimal dump to stdout
	//print_char_vect(char_vect);

	std::vector<char>::iterator it = char_vect.begin();

	while (it!=char_vect.end()){
		try{
			std::cout<<"0x"<<std::hex<<std::setfill('0') << std::setw(2)<<(int)*it<<" ";
			it+=disassemble(it);
			//check that it do not overpass end
			if (size_t(it - char_vect.begin())>char_vect.size()){
				throw "Try to disassemble instruction outside of memory bounds";
			}
		}
		catch(const char * c){
			std::cerr << "Fatal error: " << c << std::endl;
			return 1;
		}
	}


    return 0;
}

