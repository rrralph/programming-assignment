#include "cpu/exec/template-start.h"

#define instr movs

make_helper(concat3(instr,_,SUFFIX)){
	MEM_W(cpu.edi,MEM_R(cpu.esi));
	if(cpu.eflags.DF==0){
		cpu.esi+=DATA_BYTE;	
		cpu.edi+=DATA_BYTE;
	}else{
		cpu.esi-=DATA_BYTE;	
		cpu.edi-=DATA_BYTE;
	}
	print_asm(str(instr) str(SUFFIX));
	return 1;
}










#include "cpu/exec/template-end.h"
