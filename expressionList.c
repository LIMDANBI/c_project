# include "cal.h"

int operCheck(char c){
  if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c ==')') return 1;
  else return 0;
}


expressionNode* newExpressionNode(NUM* num, char c){
  expressionNode* tmp = (expressionNode*)malloc(sizeof(expressionNode));
  tmp->num = num;
  tmp->oper = c;
  tmp->next = NULL;
  return tmp;
}

expressionList* newExpressionList(){
  expressionList* tmp = (expressionList*)malloc(sizeof(expressionList));
  tmp->head = NULL;
  return tmp;
}

expressionNode* getExpressionTail(expressionList* list){
  expressionNode* tmp = list->head;
  while(tmp->next != NULL){
    tmp = tmp->next;
  }
  return tmp;
}

void appendExpression(expressionList* list, expressionNode* node){
  if(list->head == NULL){ //첫 입력이 연산자일 경우 오류 처리 해주기 ??
    list->head = node;
  }
  else{
    expressionNode* tail = getExpressionTail(list);
    tail->next = node;
  }
}

