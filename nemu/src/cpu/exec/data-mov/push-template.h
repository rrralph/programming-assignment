#include "cpu/exec/template-start.h"

#define instr push

static void do_execute(){
	cpu.esp-=DATA_BYTE;
	MEM_W(cpu.esp, op_src->val);	
	//print_asm_template2();
	print_asm(str(instr) " %s",op_src->str);

}

#if DATA_BYTE==2 || DATA_BYTE==4
make_instr_helper(r);
make_instr_helper(rm);
#endif

make_instr_helper(i);






#include "cpu/exec/template-end.h"
