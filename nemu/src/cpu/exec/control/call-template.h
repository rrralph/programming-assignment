#include "cpu/exec/template-start.h" 
#define instr call

static void do_execute(){
	cpu.esp-=DATA_BYTE;
	MEM_W(cpu.esp,cpu.eip+DATA_BYTE);
	if(op_src->type==OP_TYPE_IMM){

	cpu.eip+=(DATA_TYPE_S)op_src->val;
#if DATA_BYTE==2
	cpu.eip&=0x0000FFFF;
#endif
	}else{
		if(DATA_BYTE==2){
			cpu.eip=op_src->val&0x0000ffff;
		}else
			cpu.eip=op_src->val;
	}

	print_asm(str(instr) " 0x%x",cpu.eip+DATA_BYTE+1);
}
make_instr_helper(i);
make_instr_helper(rm);





#include "cpu/exec/template-end.h"
