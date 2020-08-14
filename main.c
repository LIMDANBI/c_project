#include "cal.h"

int main(){

    printf(" ======= Welcome to infinite calculator! ======= \n");
    printf("Enter the expression in infix notation.\n");

    char c, store = 'f';  //first
    int checkPoint = 0;

    expressionList *infix = newExpressionList();
    NUM *nNum = newNUM();
    numList *intpart = newNumList(); numList *decimpart = newNumList();

    nNum->integer = intpart;
    nNum->decimal = decimpart;

    while((c = getchar()) != '\n'){

      if('0' <= c && c <= '9'){ //숫자인 경우
        if(checkPoint == 0) appendNum(intpart, c-'0');
        else appendNum(decimpart, c-'0');
      }

      else if(operCheck(c)){  // 연산자인 경우
        if(store == 'f' && store == '('){
          if(c == '*' || c == ')') {
            printf(" !! Wrong expression. !! \n"); exit(1);
          }
          else if(c == '+');
          else if(c == '-') nNum->sign = 1;
          else if(c == '(') appendExpression(infix, newExpressionNode(NULL, c));
        }
        else if(store == '+'){
          if(c == '+');
          else if(c == '-') nNum->sign = 1;
          else if(c == '*') {
            printf(" !! Wrong expression. !! \n"); exit(1);
          }
          else if(c == '('){
            appendExpression(infix, newExpressionNode(NULL, c));
          }
          else if(c == ')'){
            printf(" !! Wrong expression. !! \n"); exit(1);
          }
        }
        else if(store == '-'){
          if(c == '+');
          else if(c == '-') nNum->sign = 1;
          else if(c == '*') {
            printf(" !! Wrong expression. !! \n"); exit(1);
          }
          else if(c == '('){
            appendExpression(infix, newExpressionNode(NULL, c));
          }
          else if(c == ')'){
            printf(" !! Wrong expression. !! \n"); exit(1);
          }
        }
        else if(store == '*'){
          if(c == '+'){
            appendExpression(infix, newExpressionNode(NULL, c));
          }
          else if(c == '-') {
            appendExpression(infix, newExpressionNode(NULL, c));
          } 
          else if(c == '*') {
            printf(" !! Wrong expression. !! \n"); exit(1);
          }
          else if(c == '('){
            appendExpression(infix, newExpressionNode(NULL, c));
          }
          else if(c == ')'){
            printf(" !! Wrong expression. !! \n"); exit(1);
          }
        }
        else if(store == ')'){
          if(c == '+' || c == '-' || c == '*' || c == ')'){
            appendExpression(infix, newExpressionNode(NULL, c));
          }
          else if(c == '('){
            printf(" !! Wrong expression. !! \n"); exit(1);
          }
        }
        else{   // store = 숫자
          appendExpression(infix, newExpressionNode(nNum, 0));
          checkPoint = 0; nNum = newNUM();
          intpart = newNumList(); decimpart = newNumList();
          nNum->integer = intpart; nNum->decimal = decimpart;
          appendExpression(infix, newExpressionNode(NULL, c));
        }
      }

      else if(c == '.'){  //정수 부분과 소수 부분의 경계를 분리
        if(checkPoint==1){
          printf(" !! There were more than two dots in one number. !! \n"); exit(1);
        }
        checkPoint = 1;
      }

      else if(c == ' ') ;  // 공백은 무시한다

      else{  // 이외 나머지는 오류 처리
        printf(" !! You have entered an invalid character. !!\n"); exit(1);
      }
      if(c != ' ' && c!= '.') store = c;
    }
    appendExpression(infix, newExpressionNode(nNum, 0));

    expressionNode *in = infix->head;
    while (in != NULL) {
      if(operCheck(in->oper)) {
        printf("%c", in->oper);
      }
      else{
        printNum(in->num);
      }
      in = in->next;
    }
    printf("\n");

    expressionList* postfix = newExpressionList();
    in2post(infix, postfix);

    expressionNode *path1 = postfix->head;
    while (path1!=NULL) {
      if(operCheck(path1->oper)) {
        printf(" %c ", path1->oper);
      }
      else{
        printf(" "); printNum(path1->num); printf(" ");
      }
      path1 = path1->next;
    }
    printf("\n");

    expressionNode *path = postfix->head;
    numStk *nStk = newNumStk();  //계산시 숫자를 보관하고 빼서 쓸 스택 선언

    while(path!=NULL){   //postfix식을 돌면서 계산을 함

      if(operCheck(path->oper)){ //연산자인 경우

        if(path->oper == '+'){  //스택에서 두 수를 빼서 계산하고 결과 값을 다시 스택에 넣는다.
          NUM *process2 = pop4Nstk(nStk); NUM *process1 = pop4Nstk(nStk);
          NUM *result; int who = whoMore(process1, process2);
          if(process1->sign == process2->sign ){  // 두 수의 부호가 같을 때
            result = plus(process1, process2);
            if(process1->sign == 1) result->sign = 1;
          }

          else{  // process1->sign != process2->sign
            if(process1->sign == 1){  //process2->sign = 0;
              if(who == 1) {  // -9+6
                result = minus(process1, process2); result->sign = 1;
              }
              else if(who == 0 || who == 2){
                result = minus(process2, process1);
              }
            }
            else{  // process1->sign = 0; process2->sign = 1;
              if(who == 0 || who == 1) result = minus(process1, process2);
              else if(who == 2){  //8+-9
                process2->sign = 0;
                result = minus(process2, process1); result->sign = 1;
              }
            }
          }
          push2Nstk(nStk, result);
        }

        else if(path->oper == '-'){
          NUM *process2 = pop4Nstk(nStk); NUM *process1 = pop4Nstk(nStk);
          NUM *result; int who = whoMore(process1, process2);
          if(process1->sign == process2->sign ){  // 두 수의 부호가 같을 때
            if(process1->sign == 0){  //둘다 양수
              if(who == 0 || who == 1){
                result = minus(process1, process2);
              }
              else if(who == 2){
                result = minus(process1, process2); result->sign = 1;
              }
            }
            else{ // 둘다 음수
              if(who == 1){
                result = minus(process1, process2); result->sign = 1;
              }
              else if(who == 0 || who == 2){
                result = minus(process2, process1); result->sign = 0;
              }
            }
          }

          else{  // process1->sign != process2->sign
            if(process1->sign == 1){  //process2->sign = 0;
              result = plus(process1, process2); result->sign = 1;
            }
            else{  // process1->sign = 0; process2->sign = 1;
              result = plus(process1, process2);
            }
          }
          push2Nstk(nStk, result);
        }

        else if(path->oper == '*'){
          NUM *process2 = pop4Nstk(nStk); NUM *process1 = pop4Nstk(nStk);
          NUM *result = multi(process1, process2);;
          if(process1->sign != process2->sign) result->sign = 1;
          push2Nstk(nStk, result);
        }

      }
      else{ // 넘인 경우
        push2Nstk(nStk, path->num);
      }
      path = path->next;
    }

    NUM *final_ans = pop4Nstk(nStk); deletzero(final_ans);
    printNum(final_ans); printf("\n");

  }

