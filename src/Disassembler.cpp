#include "Disassembler.hpp"
#include "utils.hpp"


int Disassembler::disassemble_instruction(const std::string &instruction_string) const
{
  
    //Convert input string to a vector of byte
    std::vector<char> byte_vect = utils::string_to_byte_vector(instruction_string);  
    //Disassemble the vector of byte
    disassemble_next_op(byte_vect.begin());

    return 0;
}

//Todo handle separatly the 3 cases
int Disassembler::print_cmd(const char * cmd, const char * arg1, const char * arg2) const{
        std::cout<<cmd;
        if (arg1!=NULL) std::cout<<" "<<arg1;
        if (arg2!=NULL) std::cout<<","<<arg2;
        std::cout<<std::endl;
        return 1; 
}

int Disassembler::print_cmd(const char * cmd, const int arg1) const{
        std::cout<<cmd<<" $"<<arg1<<std::endl; 
        return 2; 
}

int Disassembler::print_cmd(const char * cmd, const int arg1_lb, const int arg1_ub) const{
        std::cout<<cmd<<" $";
        std::cout<<"0x"<<std::hex<<std::setfill('0') << std::setw(4);
        std::cout<<(int)(arg1_lb+(arg1_ub<<8))<<std::endl; 
        return 3; 
}

int Disassembler::print_cmd(const char * cmd, const char * arg1, const int arg2) const{
        std::cout<<cmd<<" "<<arg1<<",$"<<arg2<<std::endl; 
        return 2; 
}


int Disassembler::print_cmd(const char * cmd, const int arg1, const char * arg2) const{
        std::cout<<cmd<<" $"<<arg1<<","<<arg2<<std::endl; 
        return 2; 
}

int Disassembler::print_cmd(const char * cmd, const char * arg1, const int arg2_lb, const int arg2_ub) const{
        std::cout<<cmd<<" "<<arg1<<",$";
        std::cout<<"0x"<<std::hex<<std::setfill('0') << std::setw(4);
        std::cout<<(int)(arg2_lb+(arg2_ub<<8))<<std::endl; 
        return 3; 
}

int Disassembler::disassemble_next_op(std::vector<char>::const_iterator it) const{
    
    //std::cout<<"opcode = "<<std::hex << opcode <<std::endl; 
    int opcode = *it;
    int opbytes = 1; //number of bytes used by the operator

    switch(opcode){
               
        //LDaaa"C", *(it+1)); break; 
        case 0x06 : opbytes = print_cmd("LD", "B", *(it+1)); break; 
        case 0x0E : opbytes = print_cmd("LD", "C", *(it+1)); break; 
        case 0x16 : opbytes = print_cmd("LD", "D", *(it+1)); break; 
        case 0x1E : opbytes = print_cmd("LD", "E", *(it+1)); break; 
        case 0x26 : opbytes = print_cmd("LD", "H", *(it+1)); break; 
        case 0x2E : opbytes = print_cmd("LD", "L", *(it+1)); break; 
        case 0x3E : opbytes = print_cmd("LD", "A", *(it+1)); break;
        case 0x36 : opbytes = print_cmd("LD", "(HL)", *(it+1));break;
        

        
        case 0x78 : opbytes = print_cmd("LD", "A", "B"); break;
        case 0x79 : opbytes = print_cmd("LD", "A", "C"); break;
        case 0x7A : opbytes = print_cmd("LD", "A", "D"); break;
        case 0x7B : opbytes = print_cmd("LD", "A", "E"); break;
        case 0x7C : opbytes = print_cmd("LD", "A", "H"); break;
        case 0x7D : opbytes = print_cmd("LD", "A", "L"); break;
        case 0x7E : opbytes = print_cmd("LD", "A", "(HL)"); break;
        case 0x7F : opbytes = print_cmd("LD", "A", "A"); break;
        case 0x40 : opbytes = print_cmd("LD", "B", "B"); break;
        case 0x41 : opbytes = print_cmd("LD", "B", "C"); break;
        case 0x42 : opbytes = print_cmd("LD", "B", "D"); break;
        case 0x43 : opbytes = print_cmd("LD", "B", "E"); break;
        case 0x44 : opbytes = print_cmd("LD", "B", "H"); break;
        case 0x45 : opbytes = print_cmd("LD", "B", "L"); break;
        case 0x46 : opbytes = print_cmd("LD", "B", "(HL)"); break;
        case 0x47 : opbytes = print_cmd("LD", "B", "A"); break;
        case 0x48 : opbytes = print_cmd("LD", "C", "B"); break;
        case 0x49 : opbytes = print_cmd("LD", "C", "C"); break;
        case 0x4A : opbytes = print_cmd("LD", "C", "D"); break;
        case 0x4B : opbytes = print_cmd("LD", "C", "E"); break;
        case 0x4C : opbytes = print_cmd("LD", "C", "H"); break;
        case 0x4D : opbytes = print_cmd("LD", "C", "L"); break;
        case 0x4E : opbytes = print_cmd("LD", "C", "(HL)"); break;
        case 0x4F : opbytes = print_cmd("LD", "C", "A"); break;
        case 0x50 : opbytes = print_cmd("LD", "D", "B"); break;
        case 0x51 : opbytes = print_cmd("LD", "D", "C"); break;
        case 0x52 : opbytes = print_cmd("LD", "D", "D"); break;
        case 0x53 : opbytes = print_cmd("LD", "D", "E"); break;
        case 0x54 : opbytes = print_cmd("LD", "D", "H"); break;
        case 0x55 : opbytes = print_cmd("LD", "D", "L"); break;
        case 0x56 : opbytes = print_cmd("LD", "D", "(HL)"); break;
        case 0x57 : opbytes = print_cmd("LD", "D", "A"); break;
        case 0x58 : opbytes = print_cmd("LD", "E", "B"); break;
        case 0x59 : opbytes = print_cmd("LD", "E", "C"); break;
        case 0x5A : opbytes = print_cmd("LD", "E", "D"); break;
        case 0x5B : opbytes = print_cmd("LD", "E", "E"); break;
        case 0x5C : opbytes = print_cmd("LD", "E", "H"); break;
        case 0x5D : opbytes = print_cmd("LD", "E", "L"); break;
        case 0x5E : opbytes = print_cmd("LD", "E", "(HL)"); break;
        case 0x5F : opbytes = print_cmd("LD", "E", "A"); break;
        case 0x60 : opbytes = print_cmd("LD", "H", "B"); break;
        case 0x61 : opbytes = print_cmd("LD", "H", "C"); break;
        case 0x62 : opbytes = print_cmd("LD", "H", "D"); break;
        case 0x63 : opbytes = print_cmd("LD", "H", "E"); break;
        case 0x64 : opbytes = print_cmd("LD", "H", "H"); break;
        case 0x65 : opbytes = print_cmd("LD", "H", "L"); break;
        case 0x66 : opbytes = print_cmd("LD", "H", "(HL)"); break;
        case 0x67 : opbytes = print_cmd("LD", "H", "A"); break;
        case 0x68 : opbytes = print_cmd("LD", "L", "B"); break;
        case 0x69 : opbytes = print_cmd("LD", "L", "C"); break;
        case 0x6A : opbytes = print_cmd("LD", "L", "D"); break;
        case 0x6B : opbytes = print_cmd("LD", "L", "E"); break;
        case 0x6C : opbytes = print_cmd("LD", "L", "H"); break;
        case 0x6D : opbytes = print_cmd("LD", "L", "L"); break;
        case 0x6E : opbytes = print_cmd("LD", "L", "(HL)"); break;
        case 0x6F : opbytes = print_cmd("LD", "L", "A"); break;
        case 0x70 : opbytes = print_cmd("LD", "(HL)", "B"); break;
        case 0x71 : opbytes = print_cmd("LD", "(HL)", "C"); break;
        case 0x72 : opbytes = print_cmd("LD", "(HL)", "D"); break;
        case 0x73 : opbytes = print_cmd("LD", "(HL)", "E"); break;
        case 0x74 : opbytes = print_cmd("LD", "(HL)", "H"); break;
        case 0x75 : opbytes = print_cmd("LD", "(HL)", "L"); break;
        case 0x77 : opbytes = print_cmd("LD", "(HL)","A"); break;

        case 0x0A : opbytes = print_cmd("LD", "A","(BC)"); break;
        case 0x1A : opbytes = print_cmd("LD", "A","(DE)"); break;


        case 0x02 : opbytes = print_cmd("LD", "(BC)","A"); break;
        case 0x12 : opbytes = print_cmd("LD", "(DE)","A"); break;
        
        case 0xEA : 
        {   //LD (nn),A
            int nn=*(it+1)+(*(it+2)<<8);
            std::cout<< "LD $(" << nn << "),A" << std::endl; opbytes = 3; 
            break;
        }
        case 0xFA : // LD A nn
            {   //LD A,(nn)
            int nn=*(it+1)+(*(it+2)<<8);
            std::cout<< "LD A,$(" << nn << ")"<<std::endl; opbytes = 3; 
            break;
        }
                
        case 0xE2 : opbytes = print_cmd("LD", "($FF00+C)","A"); break;
        case 0xF2 : opbytes = print_cmd("LD", "A","($FF00+C)"); break;

        case 0x3a : opbytes = print_cmd("LD", "A","(HLD)"); break;
        case 0x32 : opbytes = print_cmd("LD", "(HLD)","A"); break;
    
        case 0x2a : opbytes = print_cmd("LD", "A","(HLI)"); break;
        case 0x22 : opbytes = print_cmd("LD", "(HLI)","A"); break;

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
        //case 0x01 : print_cmd("LD", "BC", (int)(*(it+1)+(*(it+2)<<8))); opbytes = 3; break;
        case 0x01 : opbytes = print_cmd("LD", "BC", *(it+1), *(it+2)); break;       
        case 0x11 : opbytes = print_cmd("LD", "DE", *(it+1), *(it+2) ); break;
        case 0x21 : opbytes = print_cmd("LD", "HL", *(it+1), *(it+2) ); break;
        case 0x31 : opbytes = print_cmd("LD", "SP", *(it+1), *(it+2) ); break;

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

        case 0xBF : std::cout<<"CP A, A"<<std::endl; opbytes = 1; break;
        case 0xB8 : std::cout<<"CP A, B"<<std::endl; opbytes = 1; break;
        case 0xB9 : std::cout<<"CP A, C"<<std::endl; opbytes = 1; break;
        case 0xBA : std::cout<<"CP A, D"<<std::endl; opbytes = 1; break;
        case 0xBB : std::cout<<"CP A, E"<<std::endl; opbytes = 1; break;
        case 0xBC : std::cout<<"CP A, H"<<std::endl; opbytes = 1; break;
        case 0xBD : std::cout<<"CP A, L"<<std::endl; opbytes = 1; break;
        case 0xBE : std::cout<<"CP A, (HL)"<<std::endl; opbytes = 1; break;
        case 0xFE : std::cout<<"CP A, $"<<(int)*(it+1)<<std::endl; opbytes = 2; break;

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

        //16 bit arithmetic
        case 0x09 : std::cout<<"ADD HL,BC"<<std::endl; opbytes = 1; break;
        case 0x19 : std::cout<<"ADD HL,DE"<<std::endl; opbytes = 1; break;
        case 0x29 : std::cout<<"ADD HL,HL"<<std::endl; opbytes = 1; break;
        case 0x39 : std::cout<<"ADD HL,SP"<<std::endl; opbytes = 1; break;

        case 0xE8 : std::cout<<"ADD SP,$"<<(int)*(it+1)<<std::endl; opbytes = 2; break;

        case 0x03 : std::cout<<"INC BC"<<std::endl; opbytes = 1; break;
        case 0x13 : std::cout<<"INC DE"<<std::endl; opbytes = 1; break;
        case 0x23 : std::cout<<"INC HL"<<std::endl; opbytes = 1; break;
        case 0x33 : std::cout<<"INC SP"<<std::endl; opbytes = 1; break;

        case 0x0B : std::cout<<"DEC BC"<<std::endl; opbytes = 1; break;
        case 0x1B : std::cout<<"DEC DE"<<std::endl; opbytes = 1; break;
        case 0x2B : std::cout<<"DEC HL"<<std::endl; opbytes = 1; break;
        case 0x3B : std::cout<<"DEC SP"<<std::endl; opbytes = 1; break;

        //Miscellaneous
        case 0xCB :{
            int n= *(it+1);
            opbytes=2;
            switch (n){
                case 0x37 : print_cmd("SWAP", "A"); break;
                case 0x30 : print_cmd("SWAP", "B"); break;
                case 0x31 : print_cmd("SWAP", "C"); break;
                case 0x32 : print_cmd("SWAP", "D"); break;
                case 0x33 : print_cmd("SWAP", "E"); break;
                case 0x34 : print_cmd("SWAP", "H"); break;
                case 0x35 : print_cmd("SWAP", "L"); break;
                case 0x36 : print_cmd("SWAP", "(HL)"); break;

                //rotates and shifts
                case 0x07 : print_cmd("RLC","A"); break;
                case 0x00 : print_cmd("RLC","B"); break;
                case 0x01 : print_cmd("RLC","C"); break;
                case 0x02 : print_cmd("RLC","D"); break;
                case 0x03 : print_cmd("RLC","E"); break;
                case 0x04 : print_cmd("RLC","H"); break;
                case 0x05 : print_cmd("RLC","L"); break;
                case 0x06 : print_cmd("RLC","(HL)"); break;

                case 0x17 : print_cmd("RL","A"); break;
                case 0x10 : print_cmd("RL","B"); break;
                case 0x11 : print_cmd("RL","C"); break;
                case 0x12 : print_cmd("RL","D"); break;
                case 0x13 : print_cmd("RL","E"); break;
                case 0x14 : print_cmd("RL","H"); break;
                case 0x15 : print_cmd("RL","L"); break;
                case 0x16 : print_cmd("RL","(HL)"); break;

                case 0x0F : print_cmd("RRC","A"); break;
                case 0x08 : print_cmd("RRC","B"); break;
                case 0x09 : print_cmd("RRC","C"); break;
                case 0x0A : print_cmd("RRC","D"); break;
                case 0x0B : print_cmd("RRC","E"); break;
                case 0x0C : print_cmd("RRC","H"); break;
                case 0x0D : print_cmd("RRC","L"); break;
                case 0x0E : print_cmd("RRC","(HL)"); break;

                case 0x1F : print_cmd("RL","A"); break;
                case 0x18 : print_cmd("RL","B"); break;
                case 0x19 : print_cmd("RL","C"); break;
                case 0x1A : print_cmd("RL","D"); break;
                case 0x1B : print_cmd("RL","E"); break;
                case 0x1C : print_cmd("RL","H"); break;
                case 0x1D : print_cmd("RL","L"); break;
                case 0x1E : print_cmd("RL","(HL)"); break;

                case 0x27 : print_cmd("SLA","A"); break;
                case 0x20 : print_cmd("SLA","B"); break;
                case 0x21 : print_cmd("SLA","C"); break;
                case 0x22 : print_cmd("SLA","D"); break;
                case 0x23 : print_cmd("SLA","E"); break;
                case 0x24 : print_cmd("SLA","H"); break;
                case 0x25 : print_cmd("SLA","L"); break;
                case 0x26 : print_cmd("SLA","(HL)"); break;

                case 0x2F : print_cmd("SRA","A"); break;
                case 0x28 : print_cmd("SRA","B"); break;
                case 0x29 : print_cmd("SRA","C"); break;
                case 0x2A : print_cmd("SRA","D"); break;
                case 0x2B : print_cmd("SRA","E"); break;
                case 0x2C : print_cmd("SRA","H"); break;
                case 0x2D : print_cmd("SRA","L"); break;
                case 0x2E : print_cmd("SRA","(HL)"); break;

                case 0x3F : print_cmd("SRL","A"); break;
                case 0x38 : print_cmd("SRL","B"); break;
                case 0x39 : print_cmd("SRL","C"); break;
                case 0x3A : print_cmd("SRL","D"); break;
                case 0x3B : print_cmd("SRL","E"); break;
                case 0x3C : print_cmd("SRL","H"); break;
                case 0x3D : print_cmd("SRL","L"); break;
                case 0x3E : print_cmd("SRL","(HL)"); break;

                //bit opcodes
                default :{
                    //Get info from opcode
                    uint8_t upper = (*(it+1)>>4)&0x0f;
                    uint8_t lower = (*(it+1))&0x0f;

                    std::vector<char const *> nb_to_reg(16);
                    nb_to_reg[0]="B";       nb_to_reg[8]="B";   
                    nb_to_reg[1]="C";       nb_to_reg[9]="C";   
                    nb_to_reg[2]="D";       nb_to_reg[10]="D";   
                    nb_to_reg[3]="E";       nb_to_reg[11]="E";   
                    nb_to_reg[4]="H";       nb_to_reg[12]="H";   
                    nb_to_reg[5]="L";       nb_to_reg[13]="L";   
                    nb_to_reg[6]="(HL)";    nb_to_reg[14]="(HL)";
                    nb_to_reg[7]="A";       nb_to_reg[15]="A";   



                    char const * ins="";
                    if(upper>=4 && upper<8){
                        ins = "BIT";
                    }
                    else if(upper>=8 && upper<12){
                        ins = "RES";
                    }
                    else if(upper>=12 && upper<16){
                        ins = "SET";
                    }
                    else{
                        std::cout<<"Instruction not disassembled yet"<<std::endl;
                        throw "instruction not disassembled";
                    }

                    //print instruction
                    uint8_t byte_index = ((upper-4)*2+(lower/8))%8;
                    print_cmd(ins, byte_index, nb_to_reg[lower]);

                    // }
                    // case 0x47 : print_cmd("BIT",0,"A"); break;
                    // case 0x40 : print_cmd("BIT",0,"B"); break;
                    // case 0x41 : print_cmd("BIT",0,"C"); break;
                    // case 0x42 : print_cmd("BIT",0,"D"); break;
                    // case 0x43 : print_cmd("BIT",0,"E"); break;
                    // case 0x44 : print_cmd("BIT",0,"H"); break;
                    // case 0x45 : print_cmd("BIT",0,"L"); break;
                    // case 0x46 : print_cmd("BIT",0,"(HL)"); break;

                    // case 0xC7 : print_cmd("SET",0,"A"); break;
                    // case 0xC0 : print_cmd("SET",0,"B"); break;
                    // case 0xC1 : print_cmd("SET",0,"C"); break;
                    // case 0xC2 : print_cmd("SET",0,"D"); break;
                    // case 0xC3 : print_cmd("SET",0,"E"); break;
                    // case 0xC4 : print_cmd("SET",0,"H"); break;
                    // case 0xC5 : print_cmd("SET",0,"L"); break;
                    // case 0xC6 : print_cmd("SET",0,"(HL)"); break;

                    // case 0x87 : print_cmd("RES",0,"A"); break;
                    // case 0x80 : print_cmd("RES",0,"B"); break;
                    // case 0x81 : print_cmd("RES",0,"C"); break;
                    // case 0x82 : print_cmd("RES",0,"D"); break;
                    // case 0x83 : print_cmd("RES",0,"E"); break;
                    // case 0x84 : print_cmd("RES",0,"H"); break;
                    // case 0x85 : print_cmd("RES",0,"L"); break;
                    // case 0x86 : print_cmd("RES",0,"(HL)"); break;

                }

            }break;
        }

        case 0x27 : std::cout<<"DAA "<<std::endl; opbytes = 1; break;
        case 0x2F : std::cout<<"CPL "<<std::endl; opbytes = 1; break;
        case 0x3F : std::cout<<"CCF "<<std::endl; opbytes = 1; break;
        case 0x37 : std::cout<<"SCF "<<std::endl; opbytes = 1; break;
        case 0x00 : std::cout<<"NOP"<<std::endl; opbytes = 1; break;
        case 0x76 : std::cout<<"HALT "<<std::endl; opbytes = 1; break;
        case 0x10 : std::cout<<"STOP $"<<(int)*(it+1)<<std::endl; opbytes =2; break;
        case 0xF3 : std::cout<<"DI "<<std::endl; opbytes = 1; break;
        case 0xFB : std::cout<<"EI "<<std::endl; opbytes = 1; break;

        //rotates and shifts
        case 0x17 : opbytes = print_cmd("RLCA"); break; 
        case 0x0F : opbytes = print_cmd("RLA"); break; 
        case 0x07 : opbytes = print_cmd("RRCA"); break; 
        case 0x1F : opbytes = print_cmd("RRA"); break;


        //JP

        // case 0xc3 : 
        //     std::cout<<"JP ";
        //     add1 = *(it+1) + (*(it+2)<<8); // Less significan byte first TODO, test the jump adress, is it correct?
        //     std::cout<<"$"<<std::hex<<std::setfill('0') << std::setw(4)<<add1<<std::endl;
        //     opbytes=3; 
        //     break;
        case 0xC3 : opbytes = print_cmd("JP",*(it+1),*(it+2)); break; 

        case 0xC2 : opbytes = print_cmd("JP","NZ",*(it+1),*(it+2)); break; 
        case 0xCA : opbytes = print_cmd("JP","Z",*(it+1),*(it+2)); break;  
        case 0xD2 : opbytes = print_cmd("JP","NC",*(it+1),*(it+2)); break;  
        case 0xDA : opbytes = print_cmd("JP","C",*(it+1),*(it+2)); break; 

        case 0xE9 : opbytes = print_cmd("JP","(HL)"); break;

        case 0x18 : opbytes = print_cmd("JR",*(it+1)); break; 

        case 0x20 : opbytes = print_cmd("JR","NZ",*(it+1)); break; 
        case 0x28 : opbytes = print_cmd("JR","Z",*(it+1)); break;  
        case 0x30 : opbytes = print_cmd("JR","NC",*(it+1)); break;  
        case 0x38 : opbytes = print_cmd("JR","C",*(it+1)); break; 

        //call
        case 0xCD : opbytes = print_cmd("CALL",*(it+1),*(it+2)); break;

        case 0xC4 : opbytes = print_cmd("CALL","NZ",*(it+1),*(it+2)); break; 
        case 0xCC : opbytes = print_cmd("CALL","Z",*(it+1),*(it+2)); break;  
        case 0xD4 : opbytes = print_cmd("CALL","NC",*(it+1),*(it+2)); break;  
        case 0xDC : opbytes = print_cmd("CALL","C",*(it+1),*(it+2)); break;  

        //restart

        case 0xC7 : opbytes = print_cmd("RST","00H"); break;
        case 0xCF : opbytes = print_cmd("RST","08H"); break;
        case 0xD7 : opbytes = print_cmd("RST","10H"); break;
        case 0xDF : opbytes = print_cmd("RST","18H"); break;
        case 0xE7 : opbytes = print_cmd("RST","20H"); break;
        case 0xEF : opbytes = print_cmd("RST","28H"); break;
        case 0xF7 : opbytes = print_cmd("RST","30H"); break;
        case 0xFF : opbytes = print_cmd("RST","38H"); break;

        //returns
        case 0xC9 : opbytes = print_cmd("RET"); break;

        case 0xC0 : opbytes = print_cmd("RET","NZ"); break; 
        case 0xC8 : opbytes = print_cmd("RET","Z"); break;  
        case 0xD0 : opbytes = print_cmd("RET","NC"); break;  
        case 0xD8 : opbytes = print_cmd("RET","C"); break;

        case 0xD9 : opbytes = print_cmd("RETI"); break;

        default:
            std::cout<<"Instruction not disassembled yet"<<std::endl;
            throw "instruction not disassembled";
    }
    if (opbytes<1){
        throw "Instruction should not have less than 1 opbyte";
    }
    return opbytes;
}

int Disassembler::disassemble_all(std::vector<char> char_vect) const{

    std::vector<char>::iterator it = char_vect.begin();

    while (it!=char_vect.end()){
        try{
            //std::cout<<"0x"<<std::hex<<std::setfill('0') << std::setw(2)<<(int)*it<<" ";
            std::cout<<"0x"<<std::hex<<std::setfill('0') << std::setw(2)<<it - char_vect.begin()<<" ";
            it+=disassemble_next_op(it);

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

