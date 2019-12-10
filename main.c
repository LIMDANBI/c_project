#include "cal.h"

int main(){

    printf(" ======= Welcome to infinite calculator! ======= \n");
    printf("Enter the expression in infix notation.\n");

    char c;
    int checkPoint = 0;

    expressionList *infix = newExpressionList();
    NUM *nNum = newNUM();
    numList *intpart = newNumList();
    numList *decimpart = newNumList();

    nNum->integer = intpart;
    nNum->decimal = decimpart;

    while((c = getchar()) != '\n'){
      if('0' <= c && c <= '9'){
        if(checkPoint == 0) appendNum(intpart, c-'0');
        else appendNum(decimpart, c-'0');
      }
      else if(operCheck(c)){
        appendExpression(infix, newExpressionNode(nNum, 0));
        checkPoint = 0;
        nNum = newNUM();
        intpart = newNumList();
        decimpart = newNumList();
        nNum->integer = intpart;
        nNum->decimal = decimpart;
        appendExpression(infix, newExpressionNode(NULL, c));
      }
      else if(c == '.'){
        if(checkPoint==1){
          printf("error.\n");
          exit(1);
        }
        checkPoint = 1;
      }
      else{
        printf("error.\n");
        exit(1);
      }
    }

    appendExpression(infix, newExpressionNode(nNum, 0));

    expressionList* postfix = newExpressionList();
    in2post(infix, postfix);

    expressionNode *path = postfix->head;
    numStk *nStk = newNumStk();  //계산시 숫자를 보관하고 빼서 쓸 스택 선언

    while(path!=NULL){   //postfix식을 돌면서 계산을 함
      if(operCheck(path->oper)){ //연산자인 경우
        if(path->oper == '+'){  //스택에서 두 수를 빼서 계산하고 결과 값을 다시 스택에 넣는다.
          NUM *process1 = pop4Nstk(nStk); NUM *process2 = pop4Nstk(nStk);
          NUM *result = plus(process2, process1);
          push2Nstk(nStk, result);
        }
        else if(path->oper == '-'){
          NUM *process1 = pop4Nstk(nStk); NUM *process2 = pop4Nstk(nStk);
          printNum(process2); printf(" "); printNum(process1); printf("\n");
          NUM *result = minus(process2, process1);
          push2Nstk(nStk, result);
        }
        // else if(path->oper == '*'){
        //   NUM *process1 = pop4Nstk(nStk); NUM *process2 = pop4Nstk(nStk);
        //   NUM *result = multi(process2, process1);
        //   push2Nstk(nStk, result);
        // }
        // else{
        //   NUM *process1 = pop4Nstk(nStk); NUM *process2 = pop4Nstk(nStk);
        //   NUM *result = divi(process2, process1);
        //   push2Nstk(nStk, result);
        // }
      }
      else{ // 넘인 경우
        push2Nstk(nStk, path->num);
      }
      path = path->next;
    }

    NUM *final_ans = pop4Nstk(nStk); // deletzero(final_ans);
    printNum(final_ans);
  }
