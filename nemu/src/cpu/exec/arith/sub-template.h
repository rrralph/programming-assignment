#include "cpu/exec/template-start.h"

#define instr sub

static void do_execute() {
	DATA_TYPE result = op_dest->val - op_src->val;
	OPERAND_W(op_dest, result);

	if(op_dest->val<op_src->val)
		cpu.eflags.CF=1;

	print_asm_template2();
}

make_instr_helper(i2rm);
make_instr_helper(rm2r);


#include "cpu/exec/template-end.h"
