# include "cal.h"

int getOperPri(char oper){   //연산자의 우선순위를 리턴하는 함수  (in2post에서 사용)
  if(oper == '*'){
    return 3;
  }
  else if(oper == '+' || oper == '-'){
    return 2;
  }
  else if(oper == '(' || oper == ')'){
    return 1;
  }
}

void in2post(expressionList* infix, expressionList* postfix){
  expressionNode* before = infix->head;
  operStk* stk = newOperStk();
  expressionNode *freed;

  while(before != NULL){
    if(!operCheck(before->oper)){ //숫자인 경우
      appendExpression(postfix, newExpressionNode(before->num, 0));
    }
    else{ //연산자인 경우
      if(before->oper == '(') push2Ostk(stk, before->oper);  // '('인 경우

      else if(before->oper == ')'){  // ')'인 경우
        while(!emptyOstk(stk) && stk->top->oper != '('){
          if(stk->top->prev == NULL){
            printf(" !! The parentheses pair does not match. !! \n "); exit(1);
          }
          appendExpression(postfix, newExpressionNode(NULL, pop4Ostk(stk)));
        }
        pop4Ostk(stk);
      }

      else{  // +, -, *  인 경우
          while(!emptyOstk(stk) && getOperPri(stk->top->oper) >= getOperPri(before->oper)){
            appendExpression(postfix, newExpressionNode(NULL, pop4Ostk(stk)));
          }
          push2Ostk(stk, before->oper);
      }
    }
    freed = before; before = before->next;
    free(freed);
  }
  while(!emptyOstk(stk)){
    if (stk->top->oper == '(') {
      printf(" !! The parentheses pair does not match. !! \n "); exit(1);
    }
    appendExpression(postfix, newExpressionNode(NULL, pop4Ostk(stk)));

  }

  // expressionNode *path = postfix->head;
  // while(path != NULL){
  //   if(path->oper == '(' || path->oper ==')'){
  //     printf(" !! The parentheses pair does not match. !! \n "); exit(1);
  //   }
  //   path = path->next;
  // }
}

