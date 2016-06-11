#include "monitor/bt.h"
#include "monitor/expr.h"

/*
PartOfStackFrame getStackFrame(swaddr_t eipAddr){
	PartOfStackFrame temp;
	temp.prev_ebp=swaddr_read(eipAddr,4);
	temp.ret_addr=swaddr_read(eipAddr+4,4);
	temp.args[0]=swaddr_read(eipAddr+8+0,1);
	temp.args[1]=swaddr_read(eipAddr+8+1,1);
	temp.args[2]=swaddr_read(eipAddr+8+2,1);
	temp.args[3]=swaddr_read(eipAddr+8+3,1);
	return temp;
}*/
