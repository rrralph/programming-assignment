#include "cpu/exec/template-start.h"

#define instr cmps

make_helper(concat3(instr,_,SUFFIX)){
	DATA_TYPE_S result=MEM_R(cpu.esi)-MEM_R(cpu.edi);
	update_PZS_eflags();
	if(MSB(result)^MSB(MEM_R(cpu.esi))&&(MSB(MEM_R(cpu.esi))^MSB(MEM_R(cpu.edi))))
		cpu.eflags.OF=1;
	else
		cpu.eflags.OF=0;
	if((DATA_TYPE_S)MEM_R(cpu.esi)<(DATA_TYPE_S)MEM_R(cpu.edi))
		cpu.eflags.CF=1;
	else	
		cpu.eflags.CF=0;
	if(((MEM_R(cpu.esi)&0x7)+(MEM_R(cpu.edi)&0x7))>>3)
		cpu.eflags.AF=1;
	else
		cpu.eflags.AF=0;
	if(cpu.eflags.DF==0){
		cpu.esi+=DATA_BYTE;
		cpu.edi+=DATA_BYTE;
	}else{
		cpu.esi-=DATA_BYTE;
		cpu.edi-=DATA_BYTE;
	}
	return 1;
}















#include "cpu/exec/template-end.h"
