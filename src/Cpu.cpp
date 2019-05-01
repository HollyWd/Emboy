#include "Cpu.hpp"

Cpu::Cpu(){
	this->reset();
}

void Cpu::reset(){
	this->pc=0x100;
	this->memory = std::vector<char>(65536,0);	
}

//TODO check that cartridge size < 32kB = 32768 octets
void Cpu::load_cartridge(std::vector<char> cartridge){
	this->reset();
	// copy cartridge content to memory
	auto cart_end = cartridge.end();
	if (cartridge.size()>CARTRIDGE_SIZE){// case of several banks
		cart_end = cartridge.begin()+CARTRIDGE_SIZE;
	}
	std::copy(cartridge.begin(), cart_end, this->memory.begin());
}

void Cpu::load_debug_cartridge(std::string string_binary_code){
	this->reset();
	std::vector<char> debug_cartridge = utils::string_to_byte_vector(string_binary_code);
	std::copy(debug_cartridge.begin(), debug_cartridge.end(), this->memory.begin());
	this->pc=0x00;
}

void Cpu::print_mem(int start_index, int byte_nb) const{

	int end_index=start_index+byte_nb+1;

	if(start_index==-1){
		end_index=MEM_SIZE;
	}
	// else if(byte_nb==0){
	// 	end_index=start_index+1;
	// }
	// for (int i=start_index; i<end_index; i++){
	// 	std::cout<<std::hex<<std::setfill('0') << std::setw(4)<<i<<"    "<<(int)this->memory[i]<<std::endl;
	// }

	std::cout<<std::endl<<"Memory: "<<std::endl;
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

void Cpu::print_stack(int byte_nb) const{
	std::cout<<std::endl<<"Stack: "<<std::endl;
	std::cout<<"---------------------"<<std::endl;
	for (int i=0; i<byte_nb;i++)
	{
		std::cout<<"|"<<std::dec<<std::setw(20) << std::right << memory[sp-i]<<"|"<<std::endl;
		std::cout<<"---------------------"<<std::endl;
	}
		std::cout<<"|                   | "<<std::endl;
}


std::vector<char>::const_iterator Cpu::get_pc_iterator() const{
	return this->memory.begin() + this->pc;
}


void Cpu::emulate(){

	//std::vector<char>::const_iterator it = get_pc_iterator();
 	//int opcode = *it;
    int ob = 1; //number of bytes used by the operator
    uint16_t pc_before = pc;

    //std::cout<<"I'm emulating'"<<std::endl;

	 switch(opcode()){
               
 //        //LDaaa"C", *(it+1)); break; 
 //        case 0x16 : opbytes = print_cmd("LD", "D", *(it+1)); break; 
 //        case 0x1E : opbytes = print_cmd("LD", "E", *(it+1)); break; 
 //        case 0x26 : opbytes = print_cmd("LD", "H", *(it+1)); break; 
 //        case 0x2E : opbytes = print_cmd("LD", "L", *(it+1)); break; 
 //        case 0x3E : opbytes = print_cmd("LD", "A", *(it+1)); break;
 //        case 0x36 : opbytes = print_cmd("LD", "(HL)", *(it+1));break;
		case 0x00 : ob = 1; break;

		//jump
        case 0xc3 : jump(nn()); ob=3; break;

        case 0xC2 : jump(nn(), !flag.z); ob=3; break;
        case 0xCA : jump(nn(),  flag.z); ob=3; break; 
        case 0xD2 : jump(nn(), !flag.c); ob=3; break;
        case 0xDA : jump(nn(),  flag.c); ob=3; break;

        case 0xE9 : jump(hl()); ob=1; break;

        case 0x18 : jump(pc+op1()); ob=2; break;

        case 0x20 : jump(pc+op1(), !flag.z); ob=2; break; 
        case 0x28 : jump(pc+op1(),  flag.z); ob=2; break;  
        case 0x30 : jump(pc+op1(), !flag.c); ob=2; break;  
        case 0x38 : jump(pc+op1(),  flag.c); ob=2; break; 

        //call
        case 0xCD : ob=3; call(nn(), ob); break; 

        case 0xC4 : ob=3; call(nn(), ob, !flag.z); break; 
        case 0xCC : ob=3; call(nn(), ob,  flag.z); break;  
        case 0xD4 : ob=3; call(nn(), ob, !flag.c); break;  
        case 0xDC : ob=3; call(nn(), ob,  flag.c); break;  

        //restart
        case 0xC7 : ob=1; call(0x00,ob); break;
        case 0xCF : ob=1; call(0x08,ob); break;
        case 0xD7 : ob=1; call(0x10,ob); break;
        case 0xDF : ob=1; call(0x18,ob); break;
        case 0xE7 : ob=1; call(0x20,ob); break;
        case 0xEF : ob=1; call(0x28,ob); break;
        case 0xF7 : ob=1; call(0x30,ob); break;
        case 0xFF : ob=1; call(0x38,ob); break;

        // //returns
        // case 0xC9 : opbytes = print_cmd("RET"); break;

        // case 0xC0 : opbytes = print_cmd("RET","NZ"); break; 
        // case 0xC8 : opbytes = print_cmd("RET","Z"); break;  
        // case 0xD0 : opbytes = print_cmd("RET","NC"); break;  
        // case 0xD8 : opbytes = print_cmd("RET","C"); break;

        // case 0xD9 : opbytes = print_cmd("RETI"); break;
        

 //        case 0xff : 
 //            std::cout<<"RST ";
 //            add1 = *(it+1) + (*(it+2)<<4); // Less significan byte first
 //            std::cout<<"$38"<<std::endl; //TODO What is $38, the value of a register?
 //            opbytes=1; 
 //            break;
// Todo handel opbyte or not -> put in output
        default:
	        std::cout<<"Instruction not implemented yet"<<std::endl;
    }
 //    if (opbytes<1){
 //        throw "Instruction should not have less than 1 opbyte";
 //    }

   if (pc==pc_before){
   	pc+=ob;
   }
   return;
}

void Cpu::jump(const uint16_t addr, const bool dojump){
	if(dojump){
		this->pc = addr;
	}
}

void Cpu::decrement_sp(){
	sp--;
	assert(sp>SPMIN);
}

void Cpu::increment_sp(){
	sp++;
	assert(sp<SPMAX);
}

void Cpu::push(const uint8_t val){
	decrement_sp();
	memory[sp]=val;
}

void Cpu::push(const uint16_t val){
	decrement_sp();
	memory[sp]=val;
	decrement_sp();
	memory[sp]=val<<8;
}

uint16_t Cpu::pop(){
	uint8_t hb = memory[sp];
	increment_sp();
	uint8_t lb = memory[sp];
	increment_sp();
	return (hb<<8) + lb;
}

void Cpu::call(const uint16_t addr, const int opbytes, const bool dojump){
	if (dojump){
		push(uint16_t(pc+opbytes));
		pc=addr;
	}
}

void Cpu::ret(const bool dojump){
	pc = pop();
}
