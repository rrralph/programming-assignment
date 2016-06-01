#include "cpu/exec/template-start.h"

#define instr pop

static void do_execute(){
	OPERAND_W(op_dest,MEM_R(cpu.esp));
	cpu.esp+=DATA_BYTE;
	print_asm(str(instr) " %s",op_dest->str);

}

make_instr_helper(rm);
make_instr_helper(r);










#include "cpu/exec/template-end.h"
