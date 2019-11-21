#include <stdio.h>

#define LEN 100
#define TRUE = 1
#define FALSE = 0

typedef int Data;

typedef struct stack{
	Data Arr[LEN];
	int top;

}stack;

typedef stack Stack;


void stack_init(Stack *pstack){
	pstack->top = -1;
}


int stack_empty(Stack *pstack){
	if(top == -1) return TRUE;
	else return FALSE;
}


void push(Stack *pstack, Data Data){
	
	pstack->top += 1;
	pstack->Arr[pstack->top] = Data;

}

void pop(Stack *pstack, Data Data){

	if(stack_empty == 1) {
		printf("error!");
		exit(-1);
	}
	pstack->top -= 1;
}

Data peek(Stack *pstack){

	if(stack_empty == 1){
		printf("error!");
		exit(-1);
	}
	return pstack->Arr[pstack->top];
}

void show(Stack *pstack){
	if(stack_empty == 1){
		printf("error!");
		exit(-1);
	}

	for(int i = 0; i < (pstack->top) + 1; i++){
		printf("%d\n",pstack->Arr[i]);
	}
}

int main(){
	Stack stack;
	stack_empty(&stack);

	Push(&stack, /*sth num*/);

	print(&stack);
}
