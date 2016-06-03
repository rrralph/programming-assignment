#include "cpu/exec/template-start.h"

#define instr jmp

static void do_execute(){

	if(op_src->type==OP_TYPE_IMM){
		cpu.eip+=(DATA_TYPE_S)op_src->val;
#if DATA_BYTE == 2
		cpu.eip&=0x0000ffff;
#endif
	}else{
		if(DATA_BYTE == 2){
			cpu.eip=op_src->val&0x0000ffff;
		}else
			cpu.eip=op_src->val;
	}
	print_asm(str(instr) " %s",op_src->str);
}
make_instr_helper(i);
#if DATA_BYTE==2||DATA_BYTE==4
make_instr_helper(rm);
#endif







#include "cpu/exec/template-end.h"
