#include "Cpu.hpp"

Cpu::Cpu(){
	this->pc=0x100;
	this->memory = std::vector<char>(65536);
}

//TODO check that cartridge size < 32kB = 32768 octets
void Cpu::loadCartridge(std::vector<char> cartridge){

	// copy cartridge content to memory
	std::copy(cartridge.begin(), cartridge.begin()+CARTRIDGE_SIZE, this->memory.begin());
}


void Cpu::print_mem(int start_index, int byte_nb) const{

	int end_index=start_index+byte_nb+1;

	if(start_index==0 && byte_nb==0){
		end_index=MEM_SIZE;
	}
	else if(byte_nb==0){
		end_index=start_index+1;
	}
	// for (int i=start_index; i<end_index; i++){
	// 	std::cout<<std::hex<<std::setfill('0') << std::setw(4)<<i<<"    "<<(int)this->memory[i]<<std::endl;
	// }

	int i = start_index;
	while (i<end_index){
		printf("0x%04x:  ",i);
		for(size_t j=0; j<8; j++){
			if (i>end_index) break;
			std::cout<<std::hex<<std::setfill('0') << std::setw(2)<<(int)this->memory[i]; i++;
			if (i>end_index) break;
			std::cout<<std::hex<<std::setfill('0') << std::setw(2)<<(int)this->memory[i]<<" "; i++;		
		}
		std::cout<<std::endl;		
		//std::cout<<*(buffer+pc)<<std::endl;
	}
}

std::vector<char>::const_iterator Cpu::get_pc_iterator() const{
	return this->memory.begin() + this->pc;
}

void Cpu::emulate(){

	//std::vector<char>::const_iterator it = get_pc_iterator();
 	//int opcode = *it;
    int opbytes = 1; //number of bytes used by the operator

    //std::cout<<"I'm emulating'"<<std::endl;

	 switch(opcode()){
               
 //        //LDaaa"C", *(it+1)); break; 
 //        case 0x16 : opbytes = print_cmd("LD", "D", *(it+1)); break; 
 //        case 0x1E : opbytes = print_cmd("LD", "E", *(it+1)); break; 
 //        case 0x26 : opbytes = print_cmd("LD", "H", *(it+1)); break; 
 //        case 0x2E : opbytes = print_cmd("LD", "L", *(it+1)); break; 
 //        case 0x3E : opbytes = print_cmd("LD", "A", *(it+1)); break;
 //        case 0x36 : opbytes = print_cmd("LD", "(HL)", *(it+1));break;
		case 0x00 : std::cout<<"NOP"<<std::endl; opbytes = 1; break;

		//jump
        case 0xc3 : jump(nn()); return;

        case 0xC2 : jump(nn(), !flag.z); return;
        case 0xCA : jump(nn(),  flag.z); return; 
        case 0xD2 : jump(nn(), !flag.c); return;
        case 0xDA : jump(nn(),  flag.c); return;

        case 0xE9 : jump(hl()); return;

        case 0x18 : jump(pc+op1()); return;

        case 0x20 : jump(pc+op1(), !flag.z); return; 
        case 0x28 : jump(pc+op1(),  flag.z); return;  
        case 0x30 : jump(pc+op1(), !flag.c); return;  
        case 0x38 : jump(pc+op1(),  flag.c); return; 
        

 //        case 0xff : 
 //            std::cout<<"RST ";
 //            add1 = *(it+1) + (*(it+2)<<4); // Less significan byte first
 //            std::cout<<"$38"<<std::endl; //TODO What is $38, the value of a register?
 //            opbytes=1; 
 //            break;

        default:
	        std::cout<<"Instruction not implemented yet"<<std::endl;
    }
 //    if (opbytes<1){
 //        throw "Instruction should not have less than 1 opbyte";
 //    }

   this->pc+=opbytes;
   return;
}

void Cpu::jump(const int addr, const bool dojump){
	if(dojump){
		this->pc = addr;
	}
}
