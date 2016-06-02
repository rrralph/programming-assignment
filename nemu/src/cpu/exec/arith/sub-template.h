#include "cpu/exec/template-start.h"

#define instr sub

static void do_execute() {
	DATA_TYPE_S result = op_dest->val - op_src->val;

	update_PZS_eflags();
	if((op_dest->val&0x7)<(op_src->val&0x7))
		cpu.eflags.CF=1;
	else
		cpu.eflags.CF=0;

	if(MSB(op_dest->val)^MSB(op_src->val) &&
	   MSB(op_dest->val)^MSB(result))
		cpu.eflags.OF=1;
 	else
		cpu.eflags.OF=0;

	if(op_dest->val<op_src->val)
		cpu.eflags.CF=1;
	else
		cpu.eflags.CF=0;
		
	OPERAND_W(op_dest, result);
	print_asm_template2();
}
#if DATA_BYTE == 2 || DATA_BYTE==4

make_instr_helper(si2rm)

#endif

make_instr_helper(i2rm);
make_instr_helper(rm2r);
make_instr_helper(r2rm);


#include "cpu/exec/template-end.h"
