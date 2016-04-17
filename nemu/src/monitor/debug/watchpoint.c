#include "monitor/watchpoint.h"
#include "monitor/expr.h"

#define NR_WP 5

static WP wp_list[NR_WP];
static WP *head, *free_;

void init_wp_list() {
	int i;
	for(i = 0; i < NR_WP; i ++) {
		wp_list[i].NO = i;
		wp_list[i].next = &wp_list[i + 1];
	}
	wp_list[NR_WP - 1].next = NULL;

	head = NULL;
	free_ = wp_list;
}
/* TODO: Implement the functionality of watchpoint */
WP* new_wp(){
	if(head==NULL){
		head=free_;
		free_=free_->next;
		head->next=NULL;
		return head;
	}else{
		assert(free_);
		WP* p=head;
		while(p->next!=NULL) p=p->next;
		p->next=free_;
		free_=free_->next;
		p->next->next=NULL;	
		return p->next;
	}
}
WP* get_wp_fromno(int no){ 
	WP* p=head;
	assert(head);

	while(p){
		if(p->NO!=no) p=p->next;
		else break;
	}
	assert(p);
	return p;
}

void free_wp(WP* wp){
	WP* p=head;
	WP* q=free_;
	assert(head);
	if(head!=wp){
	while(p->next!=wp)
		p=p->next;
	WP *t=p->next;
	p->next=t->next;
	t->next=NULL;
	if(free_==NULL) {free_=t;}
	else{
		while(q->next!=NULL){
			q=q->next;
		}
		q->next=t;
	}
	}else{
		head=head->next;
		p->next=NULL;	
		while(q){
			if(q->next==NULL) break;
			else q=q->next;
		}	
		if(free_==NULL) {free_=p;}
		else{
			q->next=p;
		}
	}
//	printf("free watchpoint:%d\n",wp->NO);
}

void print_watchpoints(){
	WP* p=head;
	if(head==NULL) {printf("No watchpoints!\n");return;}
	while(p){
		printf("watchpoint %d: %s %d\n",p->NO,p->str,p->value);
		p=p->next;
	}	
}
bool check_watchpoints(){
	if(head==NULL) return false;
	WP* p=head;
	bool s=false;
	while(p){
		int v=expr(p->str,&s);		
		if(v!=p->value){
			printf("Watchpoint %d: %s\n",p->NO,p->str);
			printf("Old value= %d\n",p->value);
			p->value=v;
			printf("New value= %d\n",p->value);
			s=true;
		}
		p=p->next;
	}
	return s;
}


