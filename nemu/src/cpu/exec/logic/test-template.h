#include "cpu/exec/template-start.h"

#define instr test

static void do_execute(){
	DATA_TYPE result=(op_src->val & op_dest->val);
	cpu.eflags.OF=0;
	cpu.eflags.CF=0;
	update_PZS_eflags();
	
	print_asm(str(instr) " %s,%s",op_src->str,op_dest->str);

}



make_instr_helper(r2rm);




#include "cpu/exec/template-end.h"
