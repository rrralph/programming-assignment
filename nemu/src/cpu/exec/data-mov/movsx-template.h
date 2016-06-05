#include "cpu/exec/template-start.h"

#define instr movsx
static void do_execute(){
	int result;
	result=op_src->val<<(32-(DATA_BYTE<<3));
	result>>=(32-(DATA_BYTE<<3));
	write_operand_l(op_dest,result);
	print_asm_template2();
}

make_instr_helper(rm2r);









#include "cpu/exec/template-end.h"
