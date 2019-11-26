# include "cal.h"

numStkNode* newNumStk(NUM *n){  //새로운 숫자 스택 생성  
  numStkNode *stk = (numStkNode* )malloc(sizeof(numStkNode));
  stk->num = n;
  stk->prev = NULL;
  return stk;
}

void push2Nstk(numStk *stk, NUM *n){ //숫자 스택에 푸쉬  
  numStkNode *tmp = (numStkNode* )malloc(sizeof(numStkNode));
  tmp->num = n;
  tmp->prev = stk->top;
  stk->top = tmp;
}

NUM* pop4Nstk(numStk *stk){  //숫자 스택에서 팝  
  NUM *poped = stk->top->num;
  numStkNode *tmp = stk->top->prev;
  free(stk->top);
  stk->top = tmp;
  return poped;
}

int emptyNstk(numStk *stk){ // 스택이 비었으면 1 , 스택이 비어있지 않으면 0 
  if(stk->top == NULL){
    return 1;
  }
  else{
    return 0;
  }
}

operStackNode* newOperStk(char c){ //새로운 연산자 스택 생성  
   operStkNode *stk = (operStkNode* )malloc(sizeof(operStkNode));
   stk->oper = c;
   stk->prev = NULL;
   return stk;
 }

void push2Ostk(operStk *stk, char c){  //연산자 스택에 푸쉬   
   operStkNode *tmp = (operStkNode* )malloc(sizeof(operStkNode));
   tmp->oper = c;
   tmp->prev = stk->top;
   stk->top = tmp;
 }

char pop4Ostk(operStk *stk){  // 연산자 스택에서 팝   
  char poped;
  poped = stk->top->oper;
  operStkNode *tmp = stk->top->prev;
  free(stk->top);
  stk->top = tmp; 
  return poped;
}

int emptyOstk(operStk *stk){ // 스택이 비었으면 1 , 스택이 비어있지 않으면 0 
  if(stk->top == NULL){
    return 1;
  }
  else{
    return 0;
  }
} 
