#ifndef __WATCHPOINT_H__
#define __WATCHPOINT_H__

#include "common.h"

typedef struct watchpoint {
	int NO;
	struct watchpoint *next;

	/* TODO: Add more members if necessary */
	char str[32];
	int value;


} WP;

void init_wp_list();
WP* new_wp();
void free_wp(WP* wp);
WP* get_wp_fromno(int no);
void print_watchpoints();
bool check_watchpoints();
#endif
