#include "cpu/exec/template-start.h"

#if DATA_BYTE ==1 
#define EIP_OFF 2
#endif

#if DATA_BYTE ==2 
#undef EIP_OFF
#define EIP_OFF 4
#endif

#if DATA_BYTE ==4 
#undef EIP_OFF
#define EIP_OFF 6
#endif

#define update_eip() \
	cpu.eip=cpu.eip+op_src->val;\
	if (DATA_BYTE==2)\
		cpu.eip=cpu.eip &0x0000ffff;\
	print_asm(str(instr) " 0x%x", cpu.eip+EIP_OFF);

#define instr ja
static void do_execute(){
	if(cpu.eflags.CF==0 && cpu.eflags.ZF==0){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------
#define instr jae
static void do_execute(){
	if(cpu.eflags.CF==0){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------
#define instr jb
static void do_execute(){
	if(cpu.eflags.CF==1){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------
#define instr jbe
static void do_execute(){
	if(cpu.eflags.ZF==1 || cpu.eflags.CF==1){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------
#define instr jc
static void do_execute(){
	if(cpu.eflags.CF==1){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------
#define instr jcxz
static void do_execute(){
	if((cpu.ecx&0xffff)==0){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------
#if DATA_BYTE ==1
#define instr jecxz
static void do_execute(){
	if(cpu.ecx==0){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
#endif
//------------------------------------------------------
#define instr je
static void do_execute(){
	if(cpu.eflags.ZF==1){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------
#define instr jz
static void do_execute(){
	if(cpu.eflags.ZF==1){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------
#define instr jg
static void do_execute(){
	if(cpu.eflags.ZF==0 && cpu.eflags.SF==cpu.eflags.OF){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------
#define instr jge
static void do_execute(){
	if(cpu.eflags.SF==cpu.eflags.OF){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------
#define instr jl
static void do_execute(){
	if(cpu.eflags.SF!=cpu.eflags.OF){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------
#define instr jle
static void do_execute(){
	if(cpu.eflags.ZF==1 && cpu.eflags.SF!=cpu.eflags.OF){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------
#define instr jna
static void do_execute(){
	if(cpu.eflags.ZF==1 && cpu.eflags.CF==1){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------
#define instr jnae
static void do_execute(){
	if(cpu.eflags.CF==1){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------
#define instr jnb
static void do_execute(){
	if(cpu.eflags.CF==0){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------
#define instr jnbe
static void do_execute(){
	if(cpu.eflags.ZF==0 && cpu.eflags.CF==0){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------
#define instr jnc
static void do_execute(){
	if(cpu.eflags.CF==0){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------
#define instr jne
static void do_execute(){
	if(cpu.eflags.ZF==0){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------
#define instr jng
static void do_execute(){
	if(cpu.eflags.ZF==1 && cpu.eflags.SF!=cpu.eflags.OF){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------
#define instr jnge
static void do_execute(){
	if(cpu.eflags.SF!=cpu.eflags.OF){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------
#define instr jnl
static void do_execute(){
	if(cpu.eflags.SF==cpu.eflags.OF){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------
#define instr jnle
static void do_execute(){
	if(cpu.eflags.ZF==0 && cpu.eflags.SF==cpu.eflags.OF){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------
#define instr jno
static void do_execute(){
	if(cpu.eflags.OF==0){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------
#define instr jnp
static void do_execute(){
	if(cpu.eflags.PF==0){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------
#define instr jns
static void do_execute(){
	if(cpu.eflags.SF==0){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------
#define instr jnz
static void do_execute(){
	if(cpu.eflags.ZF==0){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------
#define instr jo
static void do_execute(){
	if(cpu.eflags.OF==1){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------
#define instr jp
static void do_execute(){
	if(cpu.eflags.PF==1){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------
#define instr jpe
static void do_execute(){
	if(cpu.eflags.PF==1){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------
#define instr jpo
static void do_execute(){
	if(cpu.eflags.PF==0){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------
#define instr js
static void do_execute(){
	if(cpu.eflags.SF==1){
		update_eip();
	}
}
make_instr_helper(i);
#undef instr
//------------------------------------------------------






#include "cpu/exec/template-end.h"