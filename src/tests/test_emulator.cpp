#include "Test.hpp"
#include "../Cpu.hpp"

void test_jump(){

	Test t("jump_function",__FILE__,__FUNCTION__);

	// Cpu cpu();
	// cpu.print_pc();
	// cpu.print_sp();
	// cpu.print_stack();
	
	// cpu.load_debug_cartridge("ff");
	// cpu.print_mem(0x00);
	// t.assert(cpu.get_pc()==0x100,__LINE__);

	// cpu.jump(0xff);
	// t.assert(cpu.get_pc()==0xff,__LINE__);

	// cpu.call(0xff);
	// cpu.print_stack(0);
	// cpu.print_stack(1);
	// t.assert(cpu.get_pc()==0xff,__LINE__);
	// t.assert(cpu.get_sp()==SP0-2,__LINE__);
	// t.assert(cpu.get_stack(1)==0x1,__LINE__);
	// t.assert(cpu.get_stack(0)==0x00,__LINE__);

	t.result();
}

int main(){
	test_jump();
	return 0;
}