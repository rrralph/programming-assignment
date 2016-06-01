#ifndef __LEAVE_H__
#define __LEAVE_H__

#define DATA_BYTE 4
#include "cpu/exec/helper.h"
#include "cpu/exec/template-start.h"
#define instr leave

make_helper(leave){
	cpu.esp=cpu.ebp;
	cpu.ebp=MEM_R(cpu.esp);
	cpu.esp+=4;
	print_asm(str(instr));
	return 1;
}

#include "cpu/exec/template-end.h"



#endif
