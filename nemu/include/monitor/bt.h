#ifndef __BT_H__
#define __BT_H__

#include "common.h"

typedef struct{
	swaddr_t prev_ebp;
	swaddr_t ret_addr;
	uint32_t args[4];
}PartOfStackFrame;












#endif
