#include "nemu.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>
#include <stdlib.h>

enum {
	NOTYPE = 256, EQ,
        NUM = 10
	/* TODO: Add more token types */

};

static struct rule {
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */

	{" +",	NOTYPE},				// spaces
	{"\\+", '+'},					// plus
	{"-", '-'},
	{"\\*", '*'},
	{"\\/", '/'},
	{"\\(", '('},
	{"\\)", ')'},
	{"==", EQ},						// equal
	{"(0x)?[0-9]+",NUM}
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
	int i;
	char error_msg[128];
	int ret;

	for(i = 0; i < NR_REGEX; i ++) {
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if(ret != 0) {
			regerror(ret, &re[i], error_msg, 128);
			Assert(ret != 0, "regex compilation failed: %s\n%s", error_msg, rules[i].regex);
		}
	}
}

typedef struct token {
	int type;
	char str[32];
} Token;

Token tokens[32];
int nr_token;
//nr_token is the char signified except whiteblank

static bool make_token(char *e) {
	int position = 0;
	int i;
	regmatch_t pmatch;
	
	nr_token = 0;

	while(e[position] != '\0') {
		/* Try all rules one by one. */
		for(i = 0; i < NR_REGEX; i ++) {
			if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
				char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;

				Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s", i, rules[i].regex, position, substr_len, substr_len, substr_start);
				position += substr_len;

				/* TODO: Now a new token is recognized with rules[i]. Add codes
				 * to record the token in the array ``tokens''. For certain 
				 * types of tokens, some extra actions should be performed.
				 */

				switch(rules[i].token_type) {
					case NOTYPE:
					    break;
					case EQ:
					case '+':
					case '-':
					case '*':
					case '/':
					case '(':
					case ')':
					    tokens[nr_token].type=rules[i].token_type;  
				            nr_token++;
					    break;	
					case NUM:
					    tokens[nr_token].type=rules[i].token_type;  
					    sprintf(tokens[nr_token].str,"%.*s",substr_len,substr_start);

				            nr_token++;
					    break;
					default: panic("please implement me");
				}

				break;
			}
		}

		if(i == NR_REGEX) {
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}

	return true; 
}
bool check_validity(Token *p,Token *q){
//	if((q-p) <2) return false;
	int rightnum=0;
        while (p<=q){ 
//	   printf("p:%d\n",(*p).type);
	   if((*p).type=='('){
		   rightnum++;
	   }
	   else if((*p).type==')'){
		   rightnum--;
		   if(rightnum<0) return false;
	   }
	   p++;
        }	   
	if(rightnum) return false;
        if(p!=(q+1)) assert(0);
	return true;
}
bool check_parentheses(Token *p,Token *q){
	if((q-p) <2) return false;
	if( p[0].type !='('|| q[0].type !=')')
		   return false;
        p++;
	int rightnum=0;
        while (p<q){ 
	   if((*p).type=='('){
		   rightnum++;
	   }
	   else if((*p).type==')'){
		   rightnum--;
		   if(rightnum<0) return false;
	   }
	   p++;
        }	   
	if (rightnum) return false;
        if(p!=q) assert(0);
	return true;
}
Token* get_dominant_operator(Token *p,Token *q){
	Token *t=q;
	int position=-1;
        while(q>=p){
	        if((*q).type=='+'||(*q).type=='-'||(*q).type=='*'||(*q).type=='/'){
		    Token *t2=q+1;
                    while(t2<=t&&(*t2).type!='('&&(*t2).type!=')'){
	                t2++;
		    } 
		    if(t2==(t+1)||(*t2).type!=')'){
		        if((*q).type=='+'||(*q).type=='-'){
			    while(q>p&&(q-1)[0].type=='-'){
				q--;
			    }
			    if(q==p||(q-1)[0].type==')'||(q-1)[0].type==NUM){
                                position=q-p;
			    }else position=q-p-1;
			    break;
			}else if(position==-1) position=q-p;
		    }
		}
            q--;
	}	
        if(position==-1) assert(0);
	printf("dom:%d\n",p[position].type);
	return p+position;
}
uint32_t eval(Token *p,Token *q){
	if(p>q){
		assert(0);
	}
	else if(p==q){
		assert((*p).type==NUM);
		return (strtol((*p).str,NULL,0));
	}
	else if(check_parentheses(p,q)==true){
//		printf("parenthese true\n");
		return eval(p+1,q-1);
	}
	else{
		bool valid=check_validity(p,q);
		assert(valid);
//		printf("valid:%d\n",valid);
		Token *op=get_dominant_operator(p,q);
		if(p<op){
		    int val1=eval(p,op-1);
		    int val2=eval(op+1,q);
		    switch(op[0].type){
	                case '+': return val1+val2;
                        case '-': return val1-val2;
	                case '*': return val1*val2;
	                case '/': 
			    assert(val2);
	                    return val1/val2;
                        default: assert(0);
		    }
		}else {
		    return -1*(eval(p+1,q));
		}

	}
}
uint32_t expr(char *e, bool *success) {
	if(!make_token(e)) {
		*success = false;
		return 0;
	}
	/* TODO: Insert codes to evaluate the expression. */
	int v=eval(tokens,tokens+nr_token-1);
	printf("ans:%d\n",v);
	return v;
	//panic("please implement me");
//	return 0;
}

