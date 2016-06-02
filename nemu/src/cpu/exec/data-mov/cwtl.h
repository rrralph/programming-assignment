#ifndef __CWTL_H__
#define __CWTL_H__

#include "../../../../include/cpu/exec/helper.h"

int cwtl(){
    if(ops_decoded.is_data_size_16){
        (cpu.eax<<16)<0?(cpu.edx= 0x0000ffff): (cpu.edx=0);
    }else{
        (cpu.eax<0)? (cpu.edx=0xffffffff): (cpu.edx=0);
    }
    print_asm_template1();    
    return 1;
}





#endif
