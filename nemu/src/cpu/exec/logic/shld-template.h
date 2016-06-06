#include "cpu/exec/template-start.h"

#define instr shld


#if DATA_BYTE ==2 || DATA_BYTE==4
static void do_execute(){
	DATA_TYPE in=op_dest->val;
	DATA_TYPE out=op_src2->val;
	uint8_t c=op_src->val;
	c&=0x1f;
	while(c!=0){
		out<<=1;
		out|=(in>>((DATA_BYTE<<3)-1))&1;
		in <<=1;
		c--;
	}
	OPERAND_W(op_src2,out);
	print_asm(str(instr) str(SUFFIX) " %s,%s,%s",op_src->str,op_dest->str,op_src2->str);
}
make_helper(concat3(shldi,_,SUFFIX)){
	int len = concat(decode_si_rm2r_,SUFFIX)(eip+1);
	op_dest->val=REG(op_dest->reg);
	do_execute();
	return len+1;
}
#endif



#include "cpu/exec/template-end.h"
