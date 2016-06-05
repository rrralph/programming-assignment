#include "cpu/exec/template-start.h"
#define instr ret

static void do_execute(){
	cpu.eip=MEM_R(cpu.esp);
	cpu.esp+=4;
	cpu.esp+=op_src->val;
	print_asm(str(instr) " 0x%x",cpu.eip);
}
make_instr_helper(i);
make_helper(ret){
#if DATA_BYTE==2
#undef DATA_BYTE
#define DATA_BYTE 4
	cpu.eip=MEM_R(cpu.esp);
	cpu.esp+=DATA_BYTE;
	print_asm(str(instr) " 0x%x",MEM_R(cpu.esp-4));
#undef DATA_BYTE
#define DATA_BYTE 2
#endif
	return 1;
}

#include "cpu/exec/template-end.h"
