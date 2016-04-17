#include "monitor/monitor.h"
#include "monitor/expr.h"
#include "monitor/watchpoint.h"
#include "nemu.h"


#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void cpu_exec(uint32_t);

/* We use the ``readline'' library to provide more flexibility to read from stdin. */
char* rl_gets() {
	static char *line_read = NULL;

	if (line_read) {
		free(line_read);
		line_read = NULL;
	}

	line_read = readline("(nemu) ");

	if (line_read && *line_read) {
		add_history(line_read);
	}

	return line_read;
}

static int cmd_c(char *args) {
	cpu_exec(-1);
	return 0;
}

static int cmd_q(char *args) {
	return -1;
}

static int cmd_help(char *args);
static int cmd_si(char *args) {
	args=strtok(args," ");
	//when more than 1 args are give, ensure to only use the first one
	if(args==NULL){
		cpu_exec(1);
	}else{
		int i=0,slen=strlen(args);
		for(;i<slen;i++){
			if(args[i]-'0'<0||args[i]-'9'>0){
				printf("Invalid args!\n");
			}
		}
		int tnum=0;
		//numeric value of the char type args
		for(i=0;i<slen;i++){
			tnum=(args[i]-'0')+tnum*10; 
		}
		cpu_exec(tnum);

	}
	return 0;	
}
static int cmd_info(char *args) {
	if(args==NULL){
		printf("lacking args!\n");
		return 0;
	}
	char *des=strtok(args," ");
	if(*des=='r'){
		printf("eax: 0x%x    %d\n",cpu.eax,cpu.eax);
		printf("ecx: 0x%x    %d\n",cpu.ecx,cpu.ecx);
		printf("edx: 0x%x    %d\n",cpu.edx,cpu.edx);
		printf("ebx: 0x%x    %d\n",cpu.ebx,cpu.ebx);
		printf("esp: 0x%x    %d\n",cpu.esp,cpu.esp);
		printf("ebp: 0x%x    %d\n",cpu.ebp,cpu.ebp);
		printf("esi: 0x%x    %d\n",cpu.esi,cpu.esi);
		printf("edi: 0x%x    %d\n",cpu.edi,cpu.edi);
		printf("eip: 0x%x    %d\n",cpu.eip,cpu.eip);
	}else if(*des=='w'){
		print_watchpoints();
	}else printf("Invalid args!\n");
	return 0;
}
static void print_4byte(swaddr_t addr)
{
	int i=4;
	for(;i>=1;i--)
		printf("%02x",swaddr_read(addr+i-1,1));
}
static int cmd_x(char *args){
	char *argsNum=strtok(args," ");
	char *desIndex=strtok(NULL," ");
	if(argsNum==NULL||desIndex==NULL)
	{
		printf("Lack arguments!");
		return 0;
	}
	uint32_t bnum=(uint32_t)strtoul(argsNum,NULL,0);
	uint32_t hwdes=(uint32_t)strtoul(desIndex,NULL,0);
	int j,i=0;
	int cnt=bnum/4;
	for(;i<cnt;i++)
	{
	    	printf("%x:  ",hwdes+i*16);
		for(j=1;j<=4;j++)
		{
			printf("0x");
			print_4byte(hwdes+i*16+(j-1)*4);
			printf("\t");

		}
		printf("\n");
	}
	int frac=bnum-cnt*4;
	printf("%x:  ",hwdes+cnt*16);
	for(i=1;i<=frac;i++)
	{
		printf("0x");
		print_4byte(hwdes+cnt*16+(i-1)*4);
		if(i<frac) printf("\t");
		else printf("\n");
	}
	return 0;
}
static int cmd_p(char *args){
	//printf("%s\n",args);
	bool s=true;
	expr(args,&s);

	return 0;
}
static int cmd_w(char *args){
	if(args==NULL){
		printf("lacking args!\n");
		return 0;
	}
	bool s=true;
	int v=expr(args,&s);
	if(s){
		WP* p=new_wp();
		strcpy(p->str,args);	
		printf("Watchpoint %d: %s\n",p->NO,p->str);
		p->value=v;
	}else{
		printf("unvalid expr!\n");
	}
	//printf("%s\n",p->str);
	return 0;

}
static int cmd_d(char *args){
	int no=strtol(args,NULL,0);		
	WP* p=get_wp_fromno(no);
	free_wp(p);
	return 0;
}
static struct {
	char *name;
	char *description;
	int (*handler) (char *);
} cmd_table [] = {
	{ "help", "Display informations about all supported commands", cmd_help },
	{ "c", "Continue the execution of the program", cmd_c },
	{ "q", "Exit NEMU", cmd_q },
        { "si", "Step one instruction exactly", cmd_si },
	{ "info", "Info r lists all the registers and their contents, Info w lists all the watchpoints", cmd_info },
	{ "x", "Examine memory N 4 bytes", cmd_x },
	{ "p", "Evaluate EXPR",cmd_p },
	{ "w", "Set watchpoint",cmd_w},
	{ "d", "Delete watchpoint N",cmd_d}
	/* TODO: Add more commands */

};

#define NR_CMD (sizeof(cmd_table) / sizeof(cmd_table[0]))

static int cmd_help(char *args) {
	/* extract the first argument */
	char *arg = strtok(NULL, " ");
	int i;

	if(arg == NULL) {
		/* no argument given */
		for(i = 0; i < NR_CMD; i ++) {
			printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
		}
	}
	else {
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(arg, cmd_table[i].name) == 0) {
				printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
				return 0;
			}
		}
		printf("Unknown command '%s'\n", arg);
	}
	return 0;
}

void ui_mainloop() {
	while(1) {
		char *str = rl_gets();
		char *str_end = str + strlen(str);

		/* extract the first token as the command */
		char *cmd = strtok(str, " ");
		if(cmd == NULL) { continue; }

		/* treat the remaining string as the arguments,
		 * which may need further parsing
		 */
		char *args = cmd + strlen(cmd) + 1;
		if(args >= str_end) {
			args = NULL;
		}

#ifdef HAS_DEVICE
		extern void sdl_clear_event_queue(void);
		sdl_clear_event_queue();
#endif

		int i;
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(cmd, cmd_table[i].name) == 0) {
				if(cmd_table[i].handler(args) < 0) { return; }
				break;
			}
		}

		if(i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
	}
}
