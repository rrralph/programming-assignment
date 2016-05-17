#include "cpu/exec/template-start.h" 
#define instr call

static void do_execute(){
	cpu.esp-=DATA_BYTE;
	cpu.esp=cpu.eip;

	cpu.eip+=op_src->val;
#if DATA_BYTE==2
	cpu.eip&=0x0000FFFF;
#endif
	print_asm(str(instr) " 0x%x",cpu.eip+DATA_BYTE+1);
}
make_instr_helper(i);






#include "cpu/exec/template-end.h"
