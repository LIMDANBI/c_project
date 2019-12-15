#include "cal.h"

int main(){

    printf(" ======= Welcome to infinite calculator! ======= \n");
    printf("Enter the expression in infix notation.\n");

    char c;
    int checkPoint = 0;
    int oPlug = 0;

    expressionList *infix = newExpressionList();
    NUM *nNum = newNUM();
    numList *intpart = newNumList();
    numList *decimpart = newNumList();

    nNum->integer = intpart;
    nNum->decimal = decimpart;

    while((c = getchar()) != '\n'){

      if('0' <= c && c <= '9'){ //숫자인 경우
        if(checkPoint == 0) appendNum(intpart, c-'0');
        else appendNum(decimpart, c-'0');
        oPlug = 1;
      }
      else if(operCheck(c)){  // 연산자인 경우  ,   나중에 *8+8과 과 같은 경우 예외 처리해줘야함
        if(c == '(' || c == ')') oPlug = 1;
        if(oPlug == 1){
          if(nNum != NULL){
            appendExpression(infix, newExpressionNode(nNum, 0));
            checkPoint = 0; nNum = newNUM();
            intpart = newNumList(); decimpart = newNumList();
            nNum->integer = intpart; nNum->decimal = decimpart;
          }
          appendExpression(infix, newExpressionNode(NULL, c));
          oPlug = 0;
        }
        else if(oPlug == 0){
          if(c == '+') {
            oPlug = 1;
          }
          else if(c == '-'){
            nNum->sign = 1; oPlug = 1;
          }
          else{
            if(nNum->integer != NULL){
              appendExpression(infix, newExpressionNode(nNum, 0));
              checkPoint = 0; nNum = newNUM();
              intpart = newNumList(); decimpart = newNumList();
              nNum->integer = intpart; nNum->decimal = decimpart;
              appendExpression(infix, newExpressionNode(NULL, c));
            }
            else{
              printf("error.\n"); exit(1);
            }
          }
        }
      }
      else if(c == '.'){  //정수 부분과 소수 부분의 경계를 분리
        if(checkPoint==1){
          printf("error.\n"); exit(1);
        }
        checkPoint = 1;
      }
      else if(c == ' ') ;  // 공백은 무시한다
      else{  // 이외 나머지는 오류 처리
        printf("error.\n"); exit(1);
      }
    }
    appendExpression(infix, newExpressionNode(nNum, 0));
    expressionList* postfix = newExpressionList();
    in2post(infix, postfix);

    expressionNode *path = postfix->head;
    expressionNode *in = infix->head;
    while (in != NULL) {
      if(operCheck(in->oper)) {
        printf("%c", in->oper); printf(" ");
      }
      else{
        printNum(in->num); printf(" ");
      } 
      in = in->next;
    }

    while (path!=NULL) {
      if(operCheck(path->oper)) {
        printf("%c", path->oper); printf(" ");
      }
      else{
        printNum(path->num); printf(" ");
      } 
      path = path->next;
    }
  }

