#include "cpu/exec/template-start.h"

#define instr add
static void do_execute(){
    DATA_TYPE result=op_src->val+op_dest->val;
    update_PZS_eflags();
    if(MSB(result)!=MSB(op_src->val)&&MSB(op_src->val)!=MSB(op_dest->val))
        cpu.eflags.OF=1;
    else
        cpu.eflags.OF=0;
    if(((op_src->val&0x7)+(op_dest->val&0x7))>>3)
        cpu.eflags.AF=1;
    else 
        cpu.eflags.AF=0;
    if(result<op_src->val)
        cpu.eflags.CF=1;
    else 
        cpu.eflags.CF=0;
    OPERAND_W(op_dest,result);
    print_asm_template2();
}
make_instr_helper(i2rm);
make_instr_helper(r2rm);
make_instr_helper(rm2r);
make_instr_helper(i2a);

#if DATA_BYTE==2 || DATA_BYTE ==4
make_instr_helper(si2rm);
#endif

#include "cpu/exec/template-end.h"
