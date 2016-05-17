#include "cpu/exec/template-start.h"

#define instr je
static void do_execute(){
	if(cpu.eflags.ZF==1){
		cpu.eip=cpu.eip+op_src->val;
		print_asm(str(instr) " 0x%x", cpu.eip+2);
	}
}

make_instr_helper(i);











#include "cpu/exec/template-end.h"
