#include "cpu/exec/template-start.h"
#define instr ret

static void do_execute(){
	cpu.eip=MEM_R(cpu.esp);
	cpu.esp+=DATA_BYTE;
	if(DATA_BYTE==2){
		cpu.eip&=0x0000ffff;
	}
	cpu.esp+=(DATA_TYPE_S)op_src->val;
	print_asm(str(instr) " 0x%x",cpu.eip);
}
make_instr_helper(i);
make_helper(ret){
	cpu.eip=MEM_R(cpu.esp);
	cpu.esp+=DATA_BYTE;
	print_asm(str(instr) " 0x%x",MEM_R(cpu.esp-DATA_BYTE));
	return 1;
}

#include "cpu/exec/template-end.h"
