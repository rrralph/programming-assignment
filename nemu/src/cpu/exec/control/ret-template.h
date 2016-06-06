#include "cpu/exec/template-start.h"
#define instr ret

static void do_execute(){
	cpu.eip=swaddr_read(cpu.esp,4);
	cpu.eip-=(DATA_BYTE+1);
	cpu.esp+=4;
	cpu.esp+=op_src->val;
	//Log("eip: 0x%x",cpu.eip);
	print_asm(str(instr) "i 0x%x",op_src->val);
}
make_instr_helper(i);
make_helper(ret){
	cpu.eip=swaddr_read(cpu.esp,4);
	cpu.esp+=4;
	cpu.eip-=1;
	//Log("eip: 0x%x",cpu.eip);
	print_asm(str(instr) " 0x%x",cpu.eip);
	return 1;
}

#include "cpu/exec/template-end.h"
