# include "cal.h"

int getOperPri(char oper){   //연산자의 우선순위를 리턴하는 함수  (in2post에서 사용)
  if(oper == '*' || oper == '/'){
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

  while(before != NULL){ //숫자인 경우
    if(!operCheck(before->oper)){
      appendExpression(postfix, newExpressionNode(before->num, 0));
    }
    else{ //연산자인 경우
      if(before->oper == '(') push2Ostk(stk, before->oper);  // '('인 경우

      else if(before->oper == ')'){  // ')'인 경우
        while(!emptyOstk(stk) && stk->top->oper != '('){
          appendExpression(postfix, newExpressionNode(NULL, pop4Ostk(stk)));
        }
        pop4Ostk(stk);
      }

      else{  // +, -, *, /  인 경우
          while(!emptyOstk(stk) && getOperPri(stk->top->oper) >= getOperPri(before->oper)){
            appendExpression(postfix, newExpressionNode(NULL, pop4Ostk(stk)));
          }
          push2Ostk(stk, before->oper);
      }
    }
    before = before->next;
  }
  while(!emptyOstk(stk)){
    appendExpression(postfix, newExpressionNode(NULL, pop4Ostk(stk)));
  }
}
