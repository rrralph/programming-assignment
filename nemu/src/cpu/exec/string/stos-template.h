#include "cpu/exec/template-start.h"

#define instr stos

make_helper(concat3(instr,_,SUFFIX)){
	DATA_TYPE_S src=cpu.eax;
	if(DATA_BYTE==1){
		src&=0x000000ff;
	}
	else if(DATA_BYTE==2){
		src&=0x0000ffff;
	}
	MEM_W(MEM_R(cpu.edi),src);
	if(cpu.eflags.DF==0){
		cpu.edi+=DATA_BYTE;
	}else
		cpu.edi-=DATA_BYTE;
	print_asm(str(instr) str(SUFFIX));
	return 1;
}




#include "cpu/exec/template-end.h"
