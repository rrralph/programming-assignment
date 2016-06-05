#ifndef __CWTL_H__
#define __CWTL_H__

#include "../../../../include/cpu/exec/helper.h"

int cwtl(){
    if(ops_decoded.is_data_size_16){
        (cpu.eax&0x00008000)?(cpu.edx= 0x0000ffff): (cpu.edx=0);
    	print_asm("cwtl");    
    }else{
        cpu.eax&0x80000000? (cpu.edx=0xffffffff): (cpu.edx=0);
	print_asm("cltd");
    }
    
    return 1;
}





#endif
