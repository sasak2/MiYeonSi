#define rt return
#define prt(X) printf(X)

#define MAX(a,b) a>b?a:b
#define MIN(a,b) a<b?a:b

#define SIZE 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
선생님 아니 stl 못쓰는건 너무하지 않습니까 진짜
아니 저 이거 동적배열 vector 구현해야 한다니까요?
선생님?
네?
네?

버그가 있는데 못찾겠다
걍 엎자
*/

struct func{
	char name_[20];
	float poly_func[SIZE];
	int func_size;
};

int func_arr_size=0;
struct func functions[SIZE];

struct func *get_new_func() {
	func_arr_size++;
	return &functions[func_arr_size-1];
}

struct func *search_func_by_name(char cmp[20]) {
	for(int i=0; i<func_arr_size; i++) {
		if(strcmp(cmp,functions[i].name_)==0) {
			return &functions[i];
		}
	}
	//엥 없다
	prt("WTF?");
	return NULL;
}

void Q0() {
	char func_name_[20];
	float func_input_buffer[SIZE];
	int func_input_size=0;

	prt("\nfunc name : ");
	scanf("%s",func_name_);

	prt("\nfunc size : ");
	scanf("%d",&func_input_size);

	printf("\n%s(x)= ",func_name_);
	for(int i=0; i<=func_input_size; i++) {
		scanf("%f",&func_input_buffer[i]);
	}

	//조왔어 입력 다받음

	struct func *new_func=get_new_func();

	strcpy(new_func->name_,func_name_);
	new_func->func_size=func_input_size;
	for(int i=0; i<=func_input_size; i++) 
		new_func->poly_func[i]=func_input_buffer[i];
	for(int i=func_input_size+1; i<SIZE; i++) 
		new_func->poly_func[i]=0.0f;

	printf("\n\n%s(x)= %f",func_name_,new_func->poly_func[0]);
	for(int i=1; i<=func_input_size; i++) 
		printf(" + %fx^%d",new_func->poly_func[i], i);

	//printf("%s",search_func_by_name(func_name_)->name_);
	return;
}

void Q1() {
	char func_name_[20];
	char func_name_1[20];
	char func_name_2[20];
	int operator_;

	prt("\nfunc name : ");
	scanf("%s",func_name_);

	prt("\noperator(0:+ 1:- 2:*) : ");
	scanf("%d",&operator_);

	char operator_ch;
	if(operator_==0) operator_ch='+';
	if(operator_==1) operator_ch='-';
	if(operator_==2) operator_ch='*';

	
	printf("\n%s(x) = func1(x) %c func2(x)",func_name_,operator_ch);
	prt("\nfunc1 : ");
	scanf("%s",func_name_1);
	prt("\nfunc2 : ");
	scanf("%s",func_name_2);
	printf("\n%s(x) = %s(x) %c %s(x)",
		func_name_,func_name_1,operator_ch,func_name_2);

  float calcing_func[SIZE];
	struct func *f1 = search_func_by_name(func_name_1);
	struct func *f2 = search_func_by_name(func_name_2);

	int max=MAX(f1->func_size,f2->func_size);
	if(max>=SIZE) max=SIZE-1;

	for(int i=0; i<SIZE; i++)
		calcing_func[i]=0.0f;

	
	if(operator_ch=='+') {
		for(int i=0; i<=max; i++) {
			calcing_func[i]=f1->poly_func[i]+f2->poly_func[i];
		}
	}

	if(operator_ch=='-') {
		for(int i=0; i<=max; i++) {
			calcing_func[i]=f1->poly_func[i]-f2->poly_func[i];
		}
	}

	if(operator_ch=='*') {
		//fft를 쓰고싶지만 그러면 내 대가리가 깨질것이기에
		//그냥 n^2 쓸게요 허허

		max=MIN(f1->func_size+f2->func_size,SIZE-1);
		
		for(int f1_p=0; f1_p<=f1->func_size; f1_p++) {
			for(int f2_p=0; f2_p<=f2->func_size; f2_p++) {
				//Out Of Bound 막아라!!!
				if(f1_p+f2_p>=SIZE) continue;
				calcing_func[f1_p+f2_p] +=
					(f1->poly_func[f1_p])*(f2->poly_func[f2_p]);
			}
		}
	}
	//이제 복사 
	struct func *new_func=get_new_func();
	
	strcpy(new_func->name_,func_name_);
	for(int i=0; i<SIZE; i++) 
		new_func->poly_func[i]=calcing_func[i];
	
	printf("\n\n%s(x)= %f",func_name_,new_func->poly_func[0]);
	for(int i=1; i<=max; i++) 
		printf(" + %fx^%d",new_func->poly_func[i], i);

	//printf("%s",search_func_by_name(func_name_)->name_);
	return;	
}

float *func_power(float *calcing, struct func *origin, int power, int *calcing_size) {
// 끼얏호 복붙띠
	//float calcing[SIZE];
	//struct func *origin=search_func_by_name(func_name_1);
	//int calcing_size=origin->func_size;

	for(int i=0; i<SIZE; i++) {
		calcing[i]=origin->poly_func[i];
	}
	float calcing_new[SIZE]={0,};

	for(int chasu=1; chasu<power; chasu++) {
		for(int ca_p=0; ca_p<=*calcing_size; ca_p++) {
			for(int or_p=0; or_p<=origin->func_size; or_p++) {
				//Out Of Bound 막아라!!!
				if(ca_p+or_p>=SIZE) continue;
				calcing_new[ca_p+or_p] +=
					(calcing[ca_p])*(origin->poly_func[or_p]);
			}
		}		
		*calcing_size=MIN(*calcing_size+origin->func_size,SIZE-1);
		for(int i=0; i<=*calcing_size; i++) {
			calcing[i]=calcing_new[i];
			calcing_new[i]=0.0f;
		}
	}
	//곱하기를 마니마니한다

	return calcing;
}

void Q2() {
	char func_name_[20];
	char func_name_1[20];
	int power;
	
	prt("\nfunc name : ");
	scanf("%s",func_name_);

	printf("\n%s(x) = func1(x)^n",func_name_);
	prt("\nfunc1 : ");
	scanf("%s",func_name_1);
	prt("\n n : ");
	scanf("%d",&power);

	/*
	 그냥 포문을 돌린다
 	이게맞다
 	*/
	float calcing[SIZE];
	struct func *origin=search_func_by_name(func_name_1);
	int calcing_size=origin->func_size;

	func_power(calcing,origin,power,&calcing_size);
	
	struct func *new_func=get_new_func();
	strcpy(new_func->name_,func_name_);
	new_func->poly_func[0]=calcing[0];
	new_func->func_size=calcing_size;
	printf("\n%s(x) = (%s(x))^%d = \n%f",
		func_name_,func_name_1,power,calcing[0]);
	for(int i=1; i<=calcing_size; i++) {
		new_func->poly_func[i]=calcing[i];
		printf(" + %fx^%d",new_func->poly_func[i],i);
	}
	return;
}

void Q3() {
	char func_name_[20];
	char func_name_1[20];
	char func_name_2[20];


	prt("\nfunc name : ");
	scanf("%s",func_name_);

	printf("\n%s(x) = func1(func2(x))",func_name_);
	prt("\nfunc1 : ");
	scanf("%s",func_name_1);
	prt("\nfunc2 : ");
	scanf("%s",func_name_2);
	printf("\n%s(x) = %s(%s(x))",
		func_name_,func_name_1,func_name_2);


	struct func *origin1=search_func_by_name(func_name_1);
	struct func *origin2=search_func_by_name(func_name_2);

	float calcing_of_all[SIZE]={origin1->poly_func[0],0.0f,};
	int size_of_all=(origin1->func_size)*(origin2->func_size);

	
	
	for(int i=1; i<=origin1->func_size; i++) {
		//----------------------

		float calcing[SIZE];
		struct func *origin=origin2;
		int calcing_size=origin->func_size;
		func_power(calcing,origin,i,&calcing_size);
		for(int k=0; k<=calcing_size; k++) {
			calcing_of_all[k]+=(origin1->poly_func[i])*calcing[k];
		}
		//----------------------
	}

	struct func *new_func = get_new_func();
	strcpy(new_func->name_,func_name_);
	new_func->func_size=size_of_all;
	new_func->poly_func[0]=calcing_of_all[0];

	printf(" = %f",calcing_of_all[0]);
	for(int i=1; i<=size_of_all; i++) {
		new_func->poly_func[i]=calcing_of_all[i];
		printf(" + %fx^%d",calcing_of_all[i],i);
	}
	
	return;
}

void Q4() {
	char func_name_[20];
	char func_name_1[20];


	prt("\nfunc name : ");
	scanf("%s",func_name_);

	printf("\n%s(x) = func1'(x)",func_name_);
	prt("\nfunc1 : ");
	scanf("%s",func_name_1);

	printf("%s(x) = %s'(x) = ",func_name_,func_name_1);
	
	struct func *origin=search_func_by_name(func_name_1);

	float calcing[SIZE]={0.0f,};
	for(int i=1; i<=origin->func_size; i++) {
		calcing[i-1]=origin->poly_func[i]*(i);
	}

	struct func *new_func = get_new_func();
	strcpy(new_func->name_,func_name_);
	new_func->func_size=origin->func_size-1;

	new_func->poly_func[0]=calcing[0];
	printf("%f",new_func->poly_func[0]);
	for(int i=1; i<=new_func->func_size; i++) {
		new_func->poly_func[i]=calcing[i];
		printf(" + %fx^%d",new_func->poly_func[i],i);
	}
	
}

void Q5() {
	char func_name_[20];
	char func_name_1[20];


	prt("\nfunc name : ");
	scanf("%s",func_name_);

	printf("\n%s(x) = ∫func1(x)dx",func_name_);
	prt("\nfunc1 : ");
	scanf("%s",func_name_1);

	printf("%s(x) = ∫%s(x)dx = ",func_name_,func_name_1);

	struct func *origin=search_func_by_name(func_name_1);

	float calcing[SIZE]={0.0f,};
	for(int i=0; i<=origin->func_size; i++) {
		calcing[i+1]=origin->poly_func[i]/(i+1);
	}

	struct func *new_func = get_new_func();
	strcpy(new_func->name_,func_name_);
	new_func->func_size=origin->func_size+1;

	new_func->poly_func[0]=calcing[0];
	printf("%f",new_func->poly_func[0]);
	for(int i=1; i<=new_func->func_size; i++) {
		new_func->poly_func[i]=calcing[i];
		printf(" + %fx^%d",new_func->poly_func[i],i);
	}

}

float Fx(struct func *origin1, struct func *origin2) {

//	struct func *origin1=new_func;
//	struct func *origin2=a_;

	float calcing_of_all[SIZE]={origin1->poly_func[0],0.0f,};
	int size_of_all=(origin1->func_size)*(origin2->func_size);

	for(int i=1; i<=origin1->func_size; i++) {
		//----------------------
		float calcing[SIZE];
		struct func *origin=origin2;
		int calcing_size=origin->func_size;
		func_power(calcing,origin,i,&calcing_size);
		for(int k=0; k<=calcing_size; k++) {
			calcing_of_all[k]+=(origin1->poly_func[i])*calcing[k];
		}
		//----------------------
	}
	return  calcing_of_all[0];

}

void Q6() {
	char func_name_1[20];
	float a,b;
	printf("\n∫ a to b func1(x) dx");
	prt("\na : ");
	scanf("%f",&a);

	prt("\nb : ");
	scanf("%f",&b);

	prt("\nfunc1 : ");
	scanf("%s",func_name_1);

	printf("\n∫ %f to %f %s(x) dx = ",a,b,func_name_1);

	struct func *origin=search_func_by_name(func_name_1);

	float calcing[SIZE]={0.0f,};
	for(int i=0; i<=origin->func_size; i++) {
		calcing[i+1]=origin->poly_func[i]/(i+1);
	}

	struct func *new_func = 
	(struct func*)malloc(sizeof(struct func));
	new_func->func_size=origin->func_size+1;
	new_func->poly_func[0]=calcing[0];
	for(int i=1; i<=new_func->func_size; i++) {
		new_func->poly_func[i]=calcing[i];
		//printf("%f ",new_func->poly_func[i-1]);
	}

	struct func *a_ = 
	(struct func*)malloc(sizeof(struct func));
	a_->func_size=0;
	a_->poly_func[0]=a;

	struct func *b_ = 
	(struct func*)malloc(sizeof(struct func));
	b_->func_size=0;
	b_->poly_func[0]=b;


	printf("%f",Fx(new_func,a_)-Fx(new_func,b_));

}

void help() {
	char msg[50][1000]= {
		"미적분 연산 시뮬레이터",
	"query : -1~6"
	"-1 : exit"
	"0 : 다항함수 입력"
	};
	//아몰랑귀찮앙
	return;
}

int main(void) {
  freopen("input.txt", "rt", stdin);

	int Q;
  while(1) {
		printf("\nQuery : ");
		scanf("%d",&Q);
		//printf("Q : %d \n",Q);
		switch(Q) {
			case 2147483647 :
				help();
				break;
			case -1:
				return 0;
				//끗
				break;
			case 0:
				//새로운 다항함수 선언
				Q0();
				break;
			case 1:
				//함수 +-* 함수 로 새로운 다항함수 선언
				Q1();
				break;
			case 2:
				//함수^n으로 새로운 다항함수 선언
				Q2();
				break;
			case 3:
				//f(g(x)) 로 새로운 다항함수 선언
				Q3();
				break;
			case 4:
				//다항함수 미분!!!
				Q4();
				break;
			case 5:
				//다항함수 적분!(적분상수 0)
				Q5();
				break;
			case 6:
				//다항함수 정적분
				Q6();
				break;
			defualt:
				break;
		}
		//입력 쿼리에 따라...
	}
/*
나는 도대체 뭔짓을 했길레 500줄에 육박하는 코드가 탄생한 것인가?
공백포함 10000자 돌파 후덜덜
*/
	return 0;
}
