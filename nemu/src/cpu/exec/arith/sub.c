#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "sub-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "sub-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "sub-template.h"
#undef DATA_BYTE


/* for instruction encoding overloading */

make_helper_v(sub_si2rm);
make_helper_v(sub_i2rm);
make_helper_v(sub_rm2r);
make_helper_v(sub_r2rm);

make_helper(sub_i2rm_b);
make_helper(sub_rm2r_b);
make_helper(sub_r2rm_b);
