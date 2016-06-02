#include "cpu/exec/template-start.h"

#define instr adc

static void do_execute(){
	DATA_TYPE_S result=op_src->val+op_dest->val+cpu.eflags.CF;    
        update_PZS_eflags();
        if(((op_src->val&0x7)+(op_dest->val&0x7))>>3)
 		cpu.eflags.AF=1;
	else
		cpu.eflags.AF=0;
        if(MSB(result)!=MSB(op_src->val)&&MSB(result)!=MSB(op_dest->val))
        	cpu.eflags.OF=1;
        else
                cpu.eflags.OF=0;
        long long result2=(long long )op_src->val +(long long)op_dest->val;
        if(result2>>DATA_BYTE*8)
  		cpu.eflags.CF=1;
        else 
		cpu.eflags.CF=0;
        OPERAND_W(op_dest,result);
  	print_asm_template2();
}


make_instr_helper(i2rm);
make_instr_helper(r2rm);
make_instr_helper(rm2r);


#if DATA_BYTE == 2|| DATA_BYTE ==4
make_instr_helper(si2rm);
#endif



#include "cpu/exec/template-end.h"
