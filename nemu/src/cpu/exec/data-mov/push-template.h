#include "cpu/exec/template-start.h"

#define instr push

static void do_execute(){
	cpu.esp=cpu.esp-DATA_BYTE;
	cpu.esp=op_src->val;	
	print_asm(str(instr) " %s",op_src->str);

}

#if DATA_BYTE==2 || DATA_BYTE==4
make_instr_helper(r);
#endif








#include "cpu/exec/template-end.h"
