#include "cpu/exec/template-start.h"

#define instr sub

static void do_execute() {
	DATA_TYPE result = op_dest->val - op_src->val;
	OPERAND_W(op_dest, result);

	if(op_dest->val<op_src->val)
		cpu.eflags.CF=1;
	if(result==0)
		cpu.eflags.ZF=1;
	cpu.eflags.SF=MSB(result);
		
	if(MSB(op_dest->val)^MSB(op_src->val) &&
	   MSB(op_dest->val)^MSB(result))
		cpu.eflags.OF=1;
	uint8_t cnum=(uint8_t)11111111&result;
	cnum=(cnum&0x55)+((cnum>>1)&0x55);
	cnum=(cnum&0x33)+((cnum>>2)&0x33);
	cnum=(cnum&0x0f)+((cnum>>4)&0x0f);	
	if(cnum % 2!=0)
		cpu.eflags.PF=1;


	print_asm_template2();
}
#if DATA_BYTE == 2 || DATA_BYTE==4

make_instr_helper(si2rm)

#endif

make_instr_helper(i2rm);
make_instr_helper(rm2r);


#include "cpu/exec/template-end.h"
