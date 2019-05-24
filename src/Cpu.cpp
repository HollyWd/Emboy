#include "Cpu.hpp"

Cpu::Cpu(){
    memory = std::vector<char>(MEM_SIZE);
	this->reset();
}

void Cpu::reset(){
    nullset();
    a=1; //GB, not the same for GBC and GBC //not clear in doc so not sure
    f=0xB0;
    pc=0x100;
    set_bc(0x13);
    set_de(0xD8);
    set_hl(0x14D);
    sp=0xFFFE;
    memory[0xFF05] = 0x00; // TIMA   
    memory[0xFF06] = 0x00; // TMA   
    memory[0xFF07] = 0x00; // TAC   
    memory[0xFF10] = 0x80; // NR10   
    memory[0xFF11] = 0xBF; // NR11   
    memory[0xFF12] = 0xF3; // NR12   
    memory[0xFF14] = 0xBF; // NR14   
    memory[0xFF16] = 0x3F; // NR21   
    memory[0xFF17] = 0x00; // NR22   
    memory[0xFF19] = 0xBF; // NR24   
    memory[0xFF1A] = 0x7F; // NR30   
    memory[0xFF1B] = 0xFF; // NR31   
    memory[0xFF1C] = 0x9F; // NR32   
    memory[0xFF1E] = 0xBF; // NR33   
    memory[0xFF20] = 0xFF; // NR41   
    memory[0xFF21] = 0x00; // NR42   
    memory[0xFF22] = 0x00; // NR43   
    memory[0xFF23] = 0xBF; // NR30   
    memory[0xFF24] = 0x77; // NR50   
    memory[0xFF25] = 0xF3; // NR51   
    memory[0xFF26] = 0xF1; // NR52   //GB only 
    memory[0xFF40] = 0x91; // LCDC   
    memory[0xFF42] = 0x00; // SCY   
    memory[0xFF43] = 0x00; // SCX   
    memory[0xFF45] = 0x00; // LYC   
    memory[0xFF47] = 0xFC; // BGP   
    memory[0xFF48] = 0xFF; // OBP0   
    memory[0xFF49] = 0xFF; // OBP1   
    memory[0xFF4A] = 0x00; // WY   
    memory[0xFF4B] = 0x00; // WX   
    memory[0xFFFF] = 0x00; // IE

}

void Cpu::nullset(){
	pc=0x100;
	sp=SP0;
	memory = std::vector<char>(65536,0);	
	a=0;
	b=0;
	d=0;
	h=0;
	f=0;
	c=0;
	e=0;
	l=0;
	flag.reset();
}

//TODO check that cartridge size < 32kB = 32768 octets
void Cpu::load_cartridge(std::vector<char> cartridge){
    assert(cartridge.size()>0);
    this->nullset();
	this->reset();
	// copy cartridge content to memory
	auto cart_end = cartridge.end();
	if (cartridge.size()>CARTRIDGE_SIZE){// case of several banks
		cart_end = cartridge.begin()+CARTRIDGE_SIZE;
	}
	std::copy(cartridge.begin(), cart_end, this->memory.begin());
}

void Cpu::load_cartridge(const char * file_name){
    std::vector<char> char_vect = utils::file_to_byte_vector(file_name);
    load_cartridge(char_vect);
    std::cout << "Cartridge is "<< char_vect.size() <<" bytes long"<<std::endl;
}

void Cpu::print_cartridge_info(){
    std::string title(memory.begin()+0x134, memory.begin()+0x145);
    std::cout<<"Title: "<<title<<std::endl;    

    if (memory[0x143]==0x80){
        std::cout<<"Color Game Boy "<<std::endl;
    }
    else{
        std::cout<<"Not Color Game Boy "<<std::endl;
    }

    std::cout<<"License code (new): "<<std::hex<<word(memory[145], memory[144])<<std::endl;

    switch(memory[0x146]){
        case 00: std::cout<<"Game Boy functions "<<std::endl; break;
        case 03: std::cout<<"Super Game Boy functions"<<std::endl; break;
    }

    std::string cart_type;
    switch(memory[0x147])
    { 
        case 0x0 : cart_type="ROM ONLY"; break;
        case 0x1 : cart_type="ROM+MBC1"; break;
        case 0x2 : cart_type="ROM+MBC1+RAM"; break;
        case 0x3 : cart_type="ROM+MBC1+RAM+BATT"; break;
        case 0x5 : cart_type="ROM+MBC2 "; break;
        case 0x6 : cart_type="ROM+MBC2+BATTERY "; break;
        case 0x8 : cart_type="ROM+RAM"; break;
        case 0x9 : cart_type="ROM+RAM+BATTERY"; break;
        case 0xB : cart_type="ROM+MMM01"; break;
        case 0xC : cart_type="ROM+MMM01+SRAM "; break;
        case 0xD : cart_type="ROM+MMM01+SRAM+BATT"; break;
        case 0xF : cart_type="ROM+MBC3+TIMER+BATT"; break;
        case 0x10 : cart_type="ROM+MBC3+TIMER+RAM+BATT"; break;
        case 0x11 : cart_type="ROM+MBC3"; break;
        case 0x12: cart_type="ROM+MBC3+RAM"; break;
        case 0x13: cart_type="ROM+MBC3+RAM+BATT"; break;
        case 0x19: cart_type="ROM+MBC5"; break;
        case 0x1A: cart_type="ROM+MBC5+RAM"; break;
        case 0x1B: cart_type="ROM+MBC5+RAM+BATT"; break;
        case 0x1C: cart_type="ROM+MBC5+RUMBLE"; break;
        case 0x1D: cart_type="ROM+MBC5+RUMBLE+SRAM"; break;
        case 0x1E: cart_type="ROM+MBC5+RUMBLE+SRAM+BATT"; break;
        case 0x1F: cart_type="Pocket Camera"; break;
        case 0xFD: cart_type="Bandai TAMA5"; break;
        case 0xFE: cart_type="Hudson HuC-3"; break;
        case 0xFF: cart_type="Hudson HuC-1"; break;
    }
    std::cout<<"Cartridge type: "<<cart_type<<std::endl; 

    std::string rom_size;
    switch(memory[0x148]){
         case 0 : rom_size = " 256Kbit =  32KByte =   2 banks"    ;break;        
         case 1 : rom_size = " 512Kbit =  64KByte =   4 banks"    ;break;        
         case 2 : rom_size = "   1Mbit = 128KByte =   8 banks"    ;break;        
         case 3 : rom_size = "   2Mbit = 256KByte =  16 banks"    ;break;        
         case 4 : rom_size = "   4Mbit = 512KByte =  32 banks"    ;break;        
         case 5 : rom_size = "   8Mbit =   1MByte =  64 banks"    ;break;        
         case 6 : rom_size = "  16Mbit =   2MByte = 128 banks"    ;break;      
         case 0x52: rom_size = "   9Mbit = 1.1MByte =  72 banks"  ;break;        
         case 0x53: rom_size = "  10Mbit = 1.2MByte =  80 banks"  ;break;        
         case 0x54: rom_size = "  1.5MByte =  96 banks"           ;break;  
    }
    std::cout<<"ROM size: "<<rom_size<<std::endl; 

    std::string ram_size;
    switch(memory[0x149]){
         case 0 : ram_size = "None" ; break;         
         case 1 : ram_size = " 16kBit =  2kB = 1 bank " ; break;             
         case 2 : ram_size = " 64kBit =  8kB = 1 bank " ; break;             
         case 3 : ram_size = "256kBit = 32kB = 4 banks" ; break;             
         case 4 : ram_size = "  1MBit =128kB =16 banks" ; break;  
    }
    std::cout<<"RAM size: "<<ram_size<<std::endl; 

    switch(memory[0x14A]){
         case 0 : std::cout<<"Destination: Japanese"<<std::endl;  break;             
         case 1 : std::cout<<"Destination: Non-Japanese"<<std::endl;  break;  
    }

    std::cout<<"License code (old): ";
    switch(memory[0x14B]){
         case 0x33 : std::cout<<"See old license code"<<std::endl;  break;             
         case 0x79 : std::cout<<"Accolade"<<std::endl;  break;  
         case 0xA4 : std::cout<<"Konami"<<std::endl;  break; 
         default : std::cout<<"?"<<std::endl;  
    }

}

void Cpu::load_debug_cartridge(std::string string_binary_code){
	this->nullset();
	std::vector<char> debug_cartridge = utils::string_to_byte_vector(string_binary_code);
	std::copy(debug_cartridge.begin(), debug_cartridge.end(), this->memory.begin());
	this->pc=0x00;
}

void Cpu::print_mem(int start_index, int byte_nb, bool table) const{

	int end_index=start_index+byte_nb+1;

	if(start_index==-1){
		end_index=MEM_SIZE;
	}

	

	// if(!table){
	// 	int i = start_index;
	// 	while (i<end_index){
	// 		printf("0x%04x:  ",i);
	// 		for(size_t j=0; j<8; j++){
	// 			if (i>end_index) break;
	// 			std::cout<<std::hex<<std::setfill('0') << std::setw(2)<<(int)this->memory[i]; i++;
	// 			if (i>end_index) break;
	// 			std::cout<<std::hex<<std::setfill('0') << std::setw(2)<<(int)this->memory[i]<<" "; i++;		
	// 		}
	// 		std::cout<<std::endl;		
	// 		//std::cout<<*(buffer+pc)<<std::endl;
	// 	}
	// }
    
    if(!table){
        int i = start_index;
        printf("0x%04x:  ",i);
        while (i<end_index){          
            if (i>end_index) break;
            std::cout<<std::hex<<std::setfill('0') << std::setw(2)<<(int)this->memory[i] <<" "; i++;
        }
            std::cout<<" ";//std::endl;       
            //std::cout<<*(buffer+pc)<<std::endl;        
    } 

	else{
        std::cout<<std::endl<<"Memory: "<<std::endl;
		const char * c1f = "      "; //col1 fill
		const char * c2f1 = "----------"; //col2 fill 1
		const char * c2f2 = "|        |"; //col2 fill 2
		const char * gs = "\033[1;32m"; //green string
		const char * gse = "\033[0m"; //end green string

		int i = start_index;
		if(i>0){std::cout<<c1f<<c2f2<<std::endl;}
        std::cout<<c1f<<c2f1<<std::endl;
		for (i= start_index; i<end_index;i++)
		{			
			if(i==pc){std::cout<<gs;}
            std::cout<<std::setw(4) << std::right<< std::hex <<"0x"<< i<<" ";
			std::cout<<"|"<<"  0x"<<std::setw(2) << std::right<< std::hex << (int)memory[i]<<"  |";
			if(i==pc){ std::cout<<" <- Program counter"<<gse;}
            std::cout<<std::endl<<c1f<<c2f1<<std::endl;
		}
			std::cout<<c1f<<c2f2<<std::endl<<std::endl;
	}	
}

void Cpu::print_stack(int byte_nb) const{

    const char * c1f1 = "----------"; //col1 fill 1
    const char * c1f2 = "|        |"; //col1 fill 2
    const char * bs = "\033[1;36m"; //blue string
    const char * bse = "\033[0m"; //end blue string

	std::cout<<std::endl<<"Stack: "<<std::endl;
	std::cout<<c1f1<<std::endl;
	for (int i=0; i<byte_nb;i++)
	{//std::setw(20) << std::right<<
		if(i==0){std::cout<<bs;}
		std::cout<<"|"<<"  0x"<<std::setw(2) << std::right<< std::hex << (int)memory[sp+i]<<"  |";
		if(i==0){std::cout<<" <- Stack Pointer"<<bse;}
        std::cout<<std::endl<<c1f1<<std::endl;

	}
		std::cout<<c1f2<<std::endl;
}


std::vector<char>::const_iterator Cpu::get_pc_iterator() const{
	return this->memory.begin() + this->pc;
}

void Cpu::print_reg() const{
    std::cout<<std::endl<<"Registers: "<<std::endl;
    std::cout<<std::setfill('0');
    std::cout<<"A : "<<"  0x"<<std::setw(2) << std::right<< std::hex << (int)a<<"    ";
    std::cout<<"F : "<<"  0x"<<std::setw(2) << std::right<< std::hex << (int)f<<std::endl;
    std::cout<<"B : "<<"  0x"<<std::setw(2) << std::right<< std::hex << (int)b<<"    ";
    std::cout<<"C : "<<"  0x"<<std::setw(2) << std::right<< std::hex << (int)c<<std::endl;
    std::cout<<"D : "<<"  0x"<<std::setw(2) << std::right<< std::hex << (int)d<<"    ";
    std::cout<<"E : "<<"  0x"<<std::setw(2) << std::right<< std::hex << (int)e<<std::endl;
    std::cout<<"H : "<<"  0x"<<std::setw(2) << std::right<< std::hex << (int)h<<"    ";
    std::cout<<"L : "<<"  0x"<<std::setw(2) << std::right<< std::hex << (int)l<<std::endl;
    std::cout<<"    SP : "<<"  0x"<<std::setw(2) << std::hex << (int)sp<<std::endl;
    std::cout<<"    PC : "<<"  0x"<<std::setw(2) << std::hex << (int)pc<<std::endl;
        
}

void Cpu::print_flag() const{
    std::cout<<std::endl<<"Flags: "<<std::endl;
    std::cout<<"Z  N  H  C"<<std::endl;
    std::cout<<(int)flag.z<<"  ";
    std::cout<<(int)flag.n<<"  ";
    std::cout<<(int)flag.h<<"  ";
    std::cout<<(int)flag.c<<"  "<<std::endl;
}

//todo set some values as signed 
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

        case 0x18 : jump(pc+op1_signed()); ob=2; break;

        case 0x20 : ob=2; jump(pc+ob+op1_signed(), !flag.z); break; 
        case 0x28 : ob=2; jump(pc+ob+op1_signed(),  flag.z); break;  
        case 0x30 : ob=2; jump(pc+ob+op1_signed(), !flag.c); break;  
        case 0x38 : ob=2; jump(pc+ob+op1_signed(),  flag.c); break; 

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
        case 0x06 : ob=2; b=op1(); break;
        case 0x0e : ob=2; c=op1(); break;
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

        //16-bits Loads
        case 0x01 : ob=3; set_bc(nn()); break;       
        case 0x11 : ob=3; set_de(nn()); break;
        case 0x21 : ob=3; set_hl(nn()); break;
        case 0x31 : ob=3; set_sp(nn()); break;

        case 0xF9 : ob=1; set_sp(get_hl()); break;

        case 0xF8 : ob=2; set_hl(get_sp()+op1()); break;

        case 0x08 : ob=3; memory[nn()]=memory[sp]; break;

        //ALU
        //ADD      
        case 0x87 : ob=1; add_8(a,a); break;
        case 0x80 : ob=1; add_8(a,b); break;
        case 0x81 : ob=1; add_8(a,c); break;
        case 0x82 : ob=1; add_8(a,d); break;
        case 0x83 : ob=1; add_8(a,e); break;
        case 0x84 : ob=1; add_8(a,h); break;
        case 0x85 : ob=1; add_8(a,l); break;
        case 0x86 : ob=1; add_8(a,get_hl_ind()); break;
        case 0xC6 : ob=2; add_8(a,op1()); break;

        case 0x8F : ob=1; add_8_c(a,a); break;
        case 0x88 : ob=1; add_8_c(a,b); break;
        case 0x89 : ob=1; add_8_c(a,c); break;
        case 0x8A : ob=1; add_8_c(a,d); break;
        case 0x8B : ob=1; add_8_c(a,e); break;
        case 0x8C : ob=1; add_8_c(a,h); break;
        case 0x8D : ob=1; add_8_c(a,l); break;
        case 0x8E : ob=1; add_8_c(a,get_hl_ind()); break;
        case 0xCE : ob=2; add_8_c(a,op1()); break;

        case 0x97 : ob=1; sub_8(a,a); break;
        case 0x90 : ob=1; sub_8(a,b); break;
        case 0x91 : ob=1; sub_8(a,c); break;
        case 0x92 : ob=1; sub_8(a,d); break;
        case 0x93 : ob=1; sub_8(a,e); break;
        case 0x94 : ob=1; sub_8(a,h); break;
        case 0x95 : ob=1; sub_8(a,l); break;
        case 0x96 : ob=1; sub_8(a,get_hl_ind()); break;
        case 0xD6 : ob=2; sub_8(a,op1()); break;

        case 0x9F : ob=1; sub_8_c(a,a); break;
        case 0x98 : ob=1; sub_8_c(a,b); break;
        case 0x99 : ob=1; sub_8_c(a,c); break;
        case 0x9A : ob=1; sub_8_c(a,d); break;
        case 0x9B : ob=1; sub_8_c(a,e); break;
        case 0x9C : ob=1; sub_8_c(a,h); break;
        case 0x9D : ob=1; sub_8_c(a,l); break;
        case 0x9E : ob=1; sub_8_c(a,get_hl_ind()); break;
        case 0xDE : ob=2; sub_8_c(a,op1()); break;

        case 0xA7 : ob=1; and_8(a,a); break;
        case 0xA0 : ob=1; and_8(a,b); break;
        case 0xA1 : ob=1; and_8(a,c); break;
        case 0xA2 : ob=1; and_8(a,d); break;
        case 0xA3 : ob=1; and_8(a,e); break;
        case 0xA4 : ob=1; and_8(a,h); break;
        case 0xA5 : ob=1; and_8(a,l); break;
        case 0xA6 : ob=1; and_8(a,get_hl_ind()); break;
        case 0xE6 : ob=2; and_8(a,op1()); break;

        case 0xB7 : ob=1; or_8(a,a); break;
        case 0xB0 : ob=1; or_8(a,b); break;
        case 0xB1 : ob=1; or_8(a,c); break;
        case 0xB2 : ob=1; or_8(a,d); break;
        case 0xB3 : ob=1; or_8(a,e); break;
        case 0xB4 : ob=1; or_8(a,h); break;
        case 0xB5 : ob=1; or_8(a,l); break;
        case 0xB6 : ob=1; or_8(a,get_hl_ind()); break;
        case 0xF6 : ob=2; or_8(a,op1()); break;

        case 0xAF : ob=1; xor_8(a,a); break;
        case 0xA8 : ob=1; xor_8(a,b); break;
        case 0xA9 : ob=1; xor_8(a,c); break;
        case 0xAA : ob=1; xor_8(a,d); break;
        case 0xAB : ob=1; xor_8(a,e); break;
        case 0xAC : ob=1; xor_8(a,h); break;
        case 0xAD : ob=1; xor_8(a,l); break;
        case 0xAE : ob=1; xor_8(a,get_hl_ind()); break;
        case 0xEE : ob=2; xor_8(a,op1()); break;

        case 0xBF : ob=1; cp_8(a,a); break;
        case 0xB8 : ob=1; cp_8(a,b); break;
        case 0xB9 : ob=1; cp_8(a,c); break;
        case 0xBA : ob=1; cp_8(a,d); break;
        case 0xBB : ob=1; cp_8(a,e); break;
        case 0xBC : ob=1; cp_8(a,h); break;
        case 0xBD : ob=1; cp_8(a,l); break;
        case 0xBE : ob=1; cp_8(a,get_hl_ind()); break;
        case 0xFE : ob=2; cp_8(a,op1()); break;

        case 0x3C : ob=1; inc_8(a); break;
        case 0x04 : ob=1; inc_8(b); break;
        case 0x0C : ob=1; inc_8(c); break;
        case 0x14 : ob=1; inc_8(d); break;
        case 0x1C : ob=1; inc_8(e); break;
        case 0x24 : ob=1; inc_8(h); break;
        case 0x2C : ob=1; inc_8(l); break;
        case 0x34 : ob=1; inc_8(hl_ind()); break;

        case 0x3D : ob=1; dec_8(a); break;
        case 0x05 : ob=1; dec_8(b); break;
        case 0x0D : ob=1; dec_8(c); break;
        case 0x15 : ob=1; dec_8(d); break;
        case 0x1D : ob=1; dec_8(e); break;
        case 0x25 : ob=1; dec_8(h); break;
        case 0x2D : ob=1; dec_8(l); break;
        case 0x35 : ob=1; dec_8(hl_ind()); break;

        //POP PUSH
        case 0xF5 : ob = 1; push(get_af()); break;
        case 0xC5 : ob = 1; push(get_bc()); break;
        case 0xD5 : ob = 1; push(get_de()); break;
        case 0xE5 : ob = 1; push(get_hl()); break;

        case 0xF1 : ob = 1; set_af(pop()); break;
        case 0xC1 : ob = 1; set_bc(pop()); break;
        case 0xD1 : ob = 1; set_de(pop()); break;
        case 0xE1 : ob = 1; set_hl(pop()); break;

        //Bit opcodes
        case 0xCB :{
            ob=2;
            switch (op1()){
                case 0x47 : bit(0,a); break;
                case 0x40 : bit(0,b); break;
                case 0x41 : bit(0,c); break;
                case 0x42 : bit(0,d); break;
                case 0x43 : bit(0,e); break;
                case 0x44 : bit(0,h); break;
                case 0x45 : bit(0,l); break;
                case 0x46 : bit(0, get_hl_ind()); break;

                case 0xC7 : set(0,a); break;
                case 0xC0 : set(0,b); break;
                case 0xC1 : set(0,c); break;
                case 0xC2 : set(0,d); break;
                case 0xC3 : set(0,e); break;
                case 0xC4 : set(0,h); break;
                case 0xC5 : set(0,l); break;
                case 0xC6 : set(0, hl_ind()); break;

                case 0x87 : res(0,a); break;
                case 0x80 : res(0,b); break;
                case 0x81 : res(0,c); break;
                case 0x82 : res(0,d); break;
                case 0x83 : res(0,e); break;
                case 0x84 : res(0,h); break;
                case 0x85 : res(0,l); break;
                case 0x86 : res(0, hl_ind()); break;
            }
            break;
        }


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
	memory[sp]=val & 0x00ff;
	decrement_sp();
	memory[sp]=val>>8;
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

void Cpu::bit(const uint8_t b, const uint8_t n){
    uint8_t bit_index = b&0x0F;
    assert((bit_index>=0) || (bit_index<=7));
    flag.z=n&1<<bit_index;
    flag.n=0;
    flag.h=1;
}

template<class T> void Cpu::set(const uint8_t b, T & n){
    uint8_t bit_index = b&0x0F;
    assert((bit_index>=0) || (bit_index<=7));
    n = n | 1<<bit_index;
}

template<class T> void Cpu::res(const uint8_t b, T & n){
    uint8_t bit_index = b&0x0F;
    assert((bit_index>=0) || (bit_index<=7));
    n = n &  ~(1<<bit_index);
}


void Cpu::add_8(uint8_t & dest, const uint8_t val){
    uint16_t res = dest+val;

    if (res==0) flag.z=0;
    flag.n=0;
    flag.h = ((dest&0x0f) + (val&0x0f)) & 0x10; //set if not null
    flag.c = (dest+val)&0x0100; //set if not null

    assert(res<=0x01ff);
    dest = (uint8_t)(res & 0x00FF);
}

//Todo What about the case where dest=val=0xff
//then dest+val+1 = 0x0200
void Cpu::add_8_c(uint8_t & dest, const uint8_t val){
    add_8(dest, val);
    add_8(dest, flag.c);
}

void Cpu::sub_8(uint8_t & dest, const uint8_t val){
    uint16_t res_c = dest + ~val + 1;

    if ((res_c&0x00ff)==0) flag.z=0;
    flag.n=1;
    flag.h = ((dest&0xf) + ((~val)&0xf) + 1)&0x10; //set if no borrow
    flag.c = res_c & 0x0100; //set if no borrow

    dest = res_c&0x00ff;
}
void Cpu::sub_8_c(uint8_t & dest, const uint8_t val){
    sub_8_c(dest, val);
    sub_8_c(dest, flag.c);
}

void Cpu::and_8(uint8_t & dest, const uint8_t val){
    dest=dest&val;
    if (dest==0) flag.z=0;
    flag.n=0;
    flag.h=1;
    flag.c=0;
}

void Cpu::or_8(uint8_t & dest, const uint8_t val){
    dest=dest|val;
    if (dest==0) flag.z=0;
    flag.n=0;
    flag.h=0;
    flag.c=0;
}

void Cpu::xor_8(uint8_t & dest, const uint8_t val){
    dest=dest^val;
    if (dest==0) flag.z=0;
    flag.n=0;
    flag.h=0;
    flag.c=0;
}

void Cpu::cp_8(uint8_t val1, const uint8_t val2){
    sub_8(val1, val2); //ompare A with n. This is basically an A - n  subtraction instruction but the results are thrown  away
}

template<class T>
void Cpu::inc_8(T & val){
    uint16_t res = val+1;

    if (res==0) flag.z=0;
    flag.n=0;
    flag.h = ((val&0x0f) + 1) & 0x10; //set if not null

    val=res;
}

template<class T>
void Cpu::dec_8(T & dest){
    uint8_t val=1;
    uint16_t res_c = dest + ~val + 1;

    if ((res_c&0x00ff)==0) flag.z=0;
    flag.n=1;
    flag.h = ((dest&0xf) + ((~val)&0xf) + 1)&0x10; //set if no borrow

    dest = res_c&0x00ff;
}