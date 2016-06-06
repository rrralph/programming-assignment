#include "FLOAT.h"

FLOAT F_mul_F(FLOAT a, FLOAT b) {
	long long ans=(long long)a *(long long)b;
	return ans>>16;
}

FLOAT F_div_F(FLOAT a, FLOAT b) {
	long long A=Fabs(a);
	long long B=Fabs(b);
	A<<=16;
	B<<=16;
	FLOAT ans=0;
	int c=16;
	while(A!=0){
		if(A>=B){
			A=A-B;
			ans|=(1<<c);
		}
		if(c==0)
			break;
		B>>=1;
		c--;
	}
	if((a<0&&b>0)||(a>0&&b<0))
		ans=-ans;
	return ans;
}

FLOAT f2F(float a) {
	int binary_a,i,e,m, ans;
	binary_a=*(int *)&a;
	m=binary_a&((1<<23)-1);
	e=((binary_a>>23)&((1<<8)-1))-127;
	ans=1;
	for(i=0;i<e+16;i++){
		ans=(ans<<1)+((m&(1<<22))>>22);
		if(ans<0){//overflow
			return 0x80000000u;
		}
		m<<=1;
	}
	if(binary_a>>31)
		ans=(~ans)+1;
	return (FLOAT)ans;
}

FLOAT Fabs(FLOAT a) {
	FLOAT ans=a<0?-a:a;
	return ans;
}

FLOAT sqrt(FLOAT x) {
	FLOAT dt, t = int2F(2);

	do {
		dt = F_div_int((F_div_F(x, t) - t), 2);
		t += dt;
	} while(Fabs(dt) > f2F(1e-4));

	return t;
}

FLOAT pow(FLOAT x, FLOAT y) {
	/* we only compute x^0.333 */
	FLOAT t2, dt, t = int2F(2);

	do {
		t2 = F_mul_F(t, t);
		dt = (F_div_F(x, t2) - t) / 3;
		t += dt;
	} while(Fabs(dt) > f2F(1e-4));

	return t;
}

