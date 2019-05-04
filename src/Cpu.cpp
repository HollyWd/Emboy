#include "Cpu.hpp"

Cpu::Cpu(){
	this->reset();
}

void Cpu::reset(){
	this->pc=0x100;
	this->sp=SP0;
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
	std::cout<<"----------"<<std::endl;
	for (int i=0; i<byte_nb;i++)
	{//std::setw(20) << std::right<<
		std::cout<<"|"<<"  0x"<<std::setw(2) << std::right<< std::hex << (int)memory[sp+i]<<"  |"<<std::endl;
		std::cout<<"----------"<<std::endl;
	}
		std::cout<<"|        | "<<std::endl;
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

		case 0x00 : ob = 1; break;

		//jump
        case 0xc3 : jump(nn()); ob=3; break;

        case 0xC2 : jump(nn(), !flag.z); ob=3; break;
        case 0xCA : jump(nn(),  flag.z); ob=3; break; 
        case 0xD2 : jump(nn(), !flag.c); ob=3; break;
        case 0xDA : jump(nn(),  flag.c); ob=3; break;

        case 0xE9 : jump(get_hl()); ob=1; break;

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

        //return
        case 0xC9 : ob=1; ret(); break; 

        case 0xC0 : ob=1; ret(!flag.z); break; 
        case 0xC8 : ob=1; ret( flag.z); break;  
        case 0xD0 : ob=1; ret(!flag.c); break;  
        case 0xD8 : ob=1; ret( flag.c); break;

        case 0xD9 : ob=1; ret(); break; //Todo enable interrupts

        //8-bit Load
        case 0x16 : ob=2; d=op1(); break; 
        case 0x1E : ob=2; e=op1(); break; 
        case 0x26 : ob=2; h=op1(); break; 
        case 0x2E : ob=2; l=op1(); break; 
        case 0x3E : ob=2; a=op1(); break;
        case 0x36 : ob=2; set_hl_ind(op1());break;
               
        case 0x78 : ob=1; a=b ; break;
        case 0x79 : ob=1; a=c ; break;
        case 0x7A : ob=1; a=d ; break;
        case 0x7B : ob=1; a=e ; break;
        case 0x7C : ob=1; a=h ; break;
        case 0x7D : ob=1; a=l ; break;

        case 0x7F : ob=1; a=a ; break;
        case 0x40 : ob=1; b=b ; break;
        case 0x41 : ob=1; b=c ; break;
        case 0x42 : ob=1; b=d ; break;
        case 0x43 : ob=1; b=e ; break;
        case 0x44 : ob=1; b=h ; break;
        case 0x45 : ob=1; b=l ; break;

        case 0x47 : ob=1; b=a ; break;
        case 0x48 : ob=1; c=b ; break;
        case 0x49 : ob=1; c=c ; break;
        case 0x4A : ob=1; c=d ; break;
        case 0x4B : ob=1; c=e ; break;
        case 0x4C : ob=1; c=h ; break;
        case 0x4D : ob=1; c=l ; break;

        case 0x4F : ob=1; c=a ; break;
        case 0x50 : ob=1; d=b ; break;
        case 0x51 : ob=1; d=c ; break;
        case 0x52 : ob=1; d=d ; break;
        case 0x53 : ob=1; d=e ; break;
        case 0x54 : ob=1; d=h ; break;
        case 0x55 : ob=1; d=l ; break;

        case 0x57 : ob=1; d=a ; break;
        case 0x58 : ob=1; e=b ; break;
        case 0x59 : ob=1; e=c ; break;
        case 0x5A : ob=1; e=d ; break;
        case 0x5B : ob=1; e=e ; break;
        case 0x5C : ob=1; e=h ; break;
        case 0x5D : ob=1; e=l ; break;

        case 0x5F : ob=1; e=a ; break;
        case 0x60 : ob=1; h=b ; break;
        case 0x61 : ob=1; h=c ; break;
        case 0x62 : ob=1; h=d ; break;
        case 0x63 : ob=1; h=e ; break;
        case 0x64 : ob=1; h=h ; break;
        case 0x65 : ob=1; h=l ; break;

        case 0x67 : ob=1; h=a ; break;
        case 0x68 : ob=1; l=b ; break;
        case 0x69 : ob=1; l=c ; break;
        case 0x6A : ob=1; l=d ; break;
        case 0x6B : ob=1; l=e ; break;
        case 0x6C : ob=1; l=h ; break;
        case 0x6D : ob=1; l=l ; break;
        
        case 0x6F : ob=1; l=a ; break;

        case 0x7E : ob=1; a=get_hl_ind(); break;
		case 0x46 : ob=1; b=get_hl_ind(); break;
		case 0x4E : ob=1; c=get_hl_ind(); break;
		case 0x56 : ob=1; d=get_hl_ind(); break;
		case 0x5E : ob=1; e=get_hl_ind(); break;
		case 0x66 : ob=1; h=get_hl_ind(); break;
		case 0x6E : ob=1; l=get_hl_ind(); break;

		case 0x77 : ob=1; set_hl_ind(a); break;
        case 0x70 : ob=1; set_hl_ind(b); break;
        case 0x71 : ob=1; set_hl_ind(c); break;
        case 0x72 : ob=1; set_hl_ind(d); break;
        case 0x73 : ob=1; set_hl_ind(e); break;
        case 0x74 : ob=1; set_hl_ind(h); break;
        case 0x75 : ob=1; set_hl_ind(l); break;
        
        case 0x0A : ob=1; a=get_bc_ind(); break;
        case 0x1A : ob=1; a=get_de_ind(); break;

        case 0x02 : ob=1; set_bc_ind(a); break;
        case 0x12 : ob=1; set_de_ind(a); break;

        case 0xEA : ob=3; set_nn_ind(a); break;//LD (nn),A
        case 0xFA : ob=3; a=get_nn_ind(); break;//LD A,(nn)

        case 0xE2 : ob=1; a=memory[0xFF00+c]; break;
        case 0xF2 : ob=1; memory[0xFF00+c]=a; break;

        case 0x3a : ob=1; a=get_hl_ind(); decrement_hl(); break; //LD A,(HLD)
        case 0x32 : ob=1; set_hl_ind(a); decrement_hl(); break; // LD (HLD),A
    
        case 0x2a : ob=1; a=get_hl_ind(); increment_hl(); break;// LD A,(HLI)
        case 0x22 : ob=1; set_hl_ind(a); increment_hl(); break; // LD (HLI),A

        case 0xE0 : ob=2; memory[0xFF00+op1()]=a; break; //LD (n) A
        case 0xF0 : ob=2; a=memory[0xFF00+op1()]; break;

        
 //        ase 0xff : 
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
	if (dojump){
		pc = pop();
	}
}
