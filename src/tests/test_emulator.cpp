#include "Test.hpp"
#include "Cpu.hpp"

#include "Disassembler.hpp"
#include "utils.hpp"
#include <vector>
#include <string>


void test_jump(){

	Test t("jump_function",__FILE__,__FUNCTION__);

	//Init
	Cpu cpu;
	cpu.print_pc();
	cpu.print_sp();
	cpu.print_stack(3);	
	cpu.load_debug_cartridge("5f 01 02 03 04 05 06 07 08 09 10");
	cpu.print_mem(0x00,10);
	t.test_assert(cpu.get_pc()==00 ,__LINE__);
	t.test_assert(cpu.get_sp()==SP0,__LINE__);
	t.test_assert(cpu.get_stack(1)==0x00,__LINE__);
	t.test_assert(cpu.get_stack(0)==0x00,__LINE__);

	//Jump
	cpu.load_debug_cartridge("c3 02 01");
	cpu.print_mem(0x00,5);
	cpu.emulate();
	t.test_assert(cpu.get_pc(), 0x102 ,__LINE__);

	cpu.load_debug_cartridge("18 0a");
	cpu.print_mem(0x00,5);
	cpu.emulate();
	t.test_assert(cpu.get_pc(), 0x0a ,__LINE__);

	//call
	cpu.load_debug_cartridge("cd 10");
	cpu.print_mem(0x00,5);
	cpu.emulate();
	t.test_assert(cpu.get_pc(), 0x10 ,__LINE__);
	t.test_assert(cpu.get_sp(), SP0-2 ,__LINE__);
	t.test_assert(cpu.get_stack(0), 0x0 ,__LINE__);
	t.test_assert(cpu.get_stack(1), 0x3 ,__LINE__);

	t.result();
}

int main(){
	test_jump();
	return 0;
}