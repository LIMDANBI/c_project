# include "cal.h"

operStkNode* newOperStkNode(char c){
  operStkNode* tmp = (operStkNode*)malloc(sizeof(operStkNode));
  tmp->oper = c;
  tmp->prev = NULL;
  return tmp;
}

operStk* newOperStk(){
  operStk* tmp = (operStk*)malloc(sizeof(operStk));
  tmp->top = NULL;
  return tmp;
}
void push2Ostk(operStk* stk, char c){
  operStkNode* tmp = newOperStkNode(c);
  tmp->prev = stk->top;
  stk->top = tmp;
}

char pop4Ostk(operStk* stk){
  operStkNode* tmp = stk->top;
  char poped = tmp->oper;
  stk->top = tmp->prev;
  free(tmp);
  return poped;
}

int emptyOstk(operStk* stk){
  if(stk->top == NULL) return 1;
  else return 0;
}

numStkNode* newNumStkNode(NUM *n){
  numStkNode* tmp = (numStkNode* )malloc(sizeof(numStkNode));
  tmp->num = n;
  tmp->prev = NULL;
  return tmp;
}

numStk* newNumStk(){
  numStk* tmp = (numStk* )malloc(sizeof(numStkNode));
  tmp->top = NULL;
  return tmp;
}

void push2Nstk(numStk *stk, NUM *n){
  numStkNode* tmp = newNumNode(n);
  tmp->prev = stk->top;
  stk->top = tmp;
}

NUM* pop4Nstk(numStk *stk){
  numStkNode* tmp = stk->top;
  NUM* poped = tmp->num;
  stk->top = tmp->prev;
  free(tmp);
  return poped;
}

int emptyNstk(numStk *stk){
  if(stk->top == NULL) return 1;
  else return 0;
}

