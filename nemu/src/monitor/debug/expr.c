#include "nemu.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

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
	{"[0-9]",NUM}
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
					case EQ:
					case '+':
					case '-':
					case '*':
					case '/':
					case '(':
					case ')':
					    tokens[nr_token].type=rules[i].token_type;  
					    break;	
					case NUM:
					    tokens[nr_token].type=rules[i].token_type;  
					    sprintf(tokens[nr_token].str,"%.*s",substr_len,substr_start);
					    //printf("%s\n",tokens[nr_token].str);
					    break;
					default: panic("please implement me");
				}
				nr_token++;

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
bool check_parentheses(char *p,char *q){
	if( p[0] !='('|| q[0] !=')'){
		   return false;
}
        p++;
	int leftflag=false;
        while (p<q){ 
	   if(*p=='('){
		   if(leftflag){
	               return false;
		   }else leftflag=true;
	   }
	   else if(*p==')'){
		   if(!leftflag){
	               return false;
		   }else leftflag=false;
	   }
	   p++;
        }	   
        if(p!=q) assert(0);
	return true;
}
char* get_dominant_operator(char *p,char *q){
	printf("len:%.*s\n",q-p,p);
	char *t=q;
	char *dopt=t;
        while(q>=p){
	        if(*q=='+'||*q=='-'||*q=='*'||*q=='/'){
		    char *t2=q+1;
                    while(t2<=t&&*t2!='('&&*t2!=')'){
	                t2++;
		    } 
		    if(*t2!=')'){
		        if(*q=='+'||*q=='-'){
		            dopt=q;
			    break;
			}else if(dopt==t) dopt=q;
		    }
		}
            q--;
	}	
        if(dopt==t)
	{//	printf("dopt is :%c\n",dopt[0]);
		assert(0);
	}

	printf("dopt is :%c\n",dopt[0]);
	return dopt;
}
uint32_t eval(char* p,char* q){
	if(p>q){
		assert(0);
	}
	else if(p==q){
		printf("p=q\n");
		return *p-'0';
	}
	else if(check_parentheses(p,q)==true){
		return eval(p+1,q-1);
	}
	else{
	        printf("get_dominantstring:%.*s\n",q-p,p);
		char *op=get_dominant_operator(p,q);
		int val1=eval(p,op-1);
		int val2=eval(op+1,q);
		switch(op[0]){
	            case '+': return val1+val2;
                    case '-': return val1-val2;
	            case '*': return val1*val2;
	            case '/': 
			assert(val2);
	                return val1/val2;
                    default: assert(0);
		}

	}
}
char *concatenation(char *dest,const char *source){
	char *temp = (char*)malloc(sizeof(char)*(strlen(dest)+strlen(source)));
	int i=0;
	while(dest[i]!='\0'){
            temp[i]=dest[i];
	    i++;
	}
	int j=0;
	while(source[j]!='\0'){
	    temp[i++]=source[j++];
	}
	temp[i]='\0';
	return temp;
}
uint32_t expr(char *e, bool *success) {
	if(!make_token(e)) {
		*success = false;
		return 0;
	}
	char *e2=strtok(e," ");
        char *e3=NULL;	
	while(e2!=NULL){
            e3=concatenation(e3,e2);
	    e2=strtok(NULL," ");
	}
	printf("e3is:%s\n",e3);
        //printf("parentheses:%d\n",check_parentheses(e3,e3+strlen(e3)-1));
	//char *op=get_dominant_operator(e3,e3+strlen(e3)-1);
	//printf("dominant operator:%d %c\n",op-e3,op[0]);

	/* TODO: Insert codes to evaluate the expression. */
	int v=eval(e3,e3+strlen(e3));
	printf("ans:%d\n",v);
	return v;
	//panic("please implement me");
	//return 0;
}

