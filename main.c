#include "cal.h"

int main(){

    printf(" ======= Welcome to infinite calculator! ======= \n");
    printf("Enter the expression in infix notation.\n");

    char c, store = 'f';  //first
    int checkPoint = 0, oLap = 0;

    expressionList *infix = newExpressionList();
    NUM *nNum = newNUM();
    numList *intpart = newNumList(); numList *decimpart = newNumList();

    nNum->integer = intpart;
    nNum->decimal = decimpart;

    while((c = getchar()) != '\n'){

      if('0' <= c && c <= '9'){ //숫자인 경우
        if(checkPoint == 0) appendNum(intpart, c-'0');
        else appendNum(decimpart, c-'0');
        oLap =  0;
      }

      else if(operCheck(c)){  // 연산자인 경우
        if(c == '+'){
          if(store == '+' || store == '-' || store == '*' || store == 'f' || store == '(') oLap = 1;
          else{
            appendExpression(infix, newExpressionNode(nNum, 0));
            checkPoint = 0; nNum = newNUM(); oLap = 0;
            intpart = newNumList(); decimpart = newNumList();
            nNum->integer = intpart; nNum->decimal = decimpart;
            appendExpression(infix, newExpressionNode(NULL, c));
          }
        }
        else if (c == '-'){
          if(store == '+' || store == '-' || store == '*' || store == 'f' || store == '('){
            oLap = 1; nNum->sign = 1;
          }
          else {
            appendExpression(infix, newExpressionNode(nNum, 0));
            checkPoint = 0; nNum = newNUM(); oLap = 0;
            intpart = newNumList(); decimpart = newNumList();
            nNum->integer = intpart; nNum->decimal = decimpart;
            appendExpression(infix, newExpressionNode(NULL, c));
          }
        }
        else if(c == '*'){
          if(store == '+' || store == '-' || store == '*' || store == 'f' || store == '(' ){
            printf(" !! Wrong expression. !! \n"); exit(1);
          }
          else{
            appendExpression(infix, newExpressionNode(nNum, 0));
            checkPoint = 0; nNum = newNUM(); oLap = 0;
            intpart = newNumList(); decimpart = newNumList();
            nNum->integer = intpart; nNum->decimal = decimpart;
            appendExpression(infix, newExpressionNode(NULL, c));
          }
        }
        else if(c == '('){  // 괄호 쌍이 맞는지 파악하기 해줘야함
          if(store == '-' || store == '+'){
            if(nNum->sign) appendExpression(infix, newExpressionNode(NULL, '-'));
            else if(nNum->sign == 0) appendExpression(infix, newExpressionNode(NULL, '+'));
            nNum->sign = 0; appendExpression(infix, newExpressionNode(NULL, c));
          }
          else if(store == ')'){
            printf(" !! Wrong expression. !! \n"); exit(1);
          }
          else appendExpression(infix, newExpressionNode(NULL, c));
        }
        else if(c== ')'){
          if(store == '+' || store == '-' || store == '*' ||store == '('){
            printf(" !! Wrong expression. !! \n"); exit(1);
          }
          else{
            if(nNum->integer != NULL){
              appendExpression(infix, newExpressionNode(nNum, 0));
              checkPoint = 0; nNum = newNUM(); oLap = 0;
              intpart = newNumList(); decimpart = newNumList();
              nNum->integer = intpart; nNum->decimal = decimpart;   
            }
            appendExpression(infix, newExpressionNode(NULL, c));
          }
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
      if(store != ' ') store = c;
    }


    appendExpression(infix, newExpressionNode(nNum, 0));
    expressionList* postfix = newExpressionList();
    in2post(infix, postfix);

    expressionNode *in = infix->head; expressionNode *path = postfix->head;

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

    while (path!=NULL) {
      if(operCheck(path->oper)) {
        printf(" %c ", path->oper);
      }
      else{
        printf(" "); printNum(path->num); printf(" ");
      }
      path = path->next;
    }
  }

