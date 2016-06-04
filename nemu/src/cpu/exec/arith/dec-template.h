#include "cpu/exec/template-start.h"

#define instr dec

static void do_execute () {
	DATA_TYPE result = op_src->val - 1;
	OPERAND_W(op_src, result);

	/* TODO: Update EFLAGS. */
	update_PZS_eflags();
	if((op_src->val&0x7)>0)
		cpu.eflags.AF=1;
	else
		cpu.eflags.AF=0;
	if(MSB(op_src->val)&&(!MSB(result)))
		cpu.eflags.OF=1;
	else
		cpu.eflags.OF=0;
	print_asm_template1();
}

make_instr_helper(rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(r)
#endif

#include "cpu/exec/template-end.h"
