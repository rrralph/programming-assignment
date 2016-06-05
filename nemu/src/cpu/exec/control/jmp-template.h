#include "cpu/exec/template-start.h"

#define instr jmp

#if DATA_BYTE ==1 
#define CODE_LEN 2
#endif

#if DATA_BYTE ==2
#undef CODE_LEN
#define CODE_LEN 3
#endif

#if DATA_BYTE==4
#undef CODE_LEN
#define CODE_LEN 5
#endif

static void do_execute(){

	if(op_src->type==OP_TYPE_IMM){
		cpu.eip+=(DATA_TYPE_S)op_src->val;
#if DATA_BYTE == 2
		cpu.eip&=0x0000ffff;
#endif
	}else{
		if(DATA_BYTE == 2){
			cpu.eip=(op_src->val&0x0000ffff)-2;
		}else
			cpu.eip=op_src->val-2;
	}
	print_asm(str(instr) " 0x%x",cpu.eip+CODE_LEN);
}
make_instr_helper(i);
#if DATA_BYTE==2||DATA_BYTE==4
make_instr_helper(rm);
#endif







#include "cpu/exec/template-end.h"
