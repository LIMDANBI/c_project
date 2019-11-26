#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int data;
  struct numNode *prev;
  struct numNode *next;
} numNode; //숫자 노드 하나, 노드 : [prev - 숫자 - next]

typedef struct {
  numNode *head;
} numList; // 이중 연결 리스트로 연결된 수의 시작을 가리키는 포인터 (ex)12345.6789) // 1을 가르킴.

typedef struct {
  int sign; // + : 0, - : 1
  numList *integer;
  numList *decimal;
} NUM; //숫자의 정수와 소수부에 나눠서 접근할 수 있게 함.

typedef struct {
  char oper;
  NUM *num;
  struct expression next;
} expression;  //인픽스를 저장할 수 있는 자료형, 후위표기식으로 바꿀 때도 사용할 수 있는 구조
              // ex) ["123.34" - "+" - "456.34" - null ]

typedef struct {
  expression *head;
} expressionList;

//stack(스택)
typedef struct {
  NUM *num;
  struct numStkNode *prev;
} numStkNode; //숫자를 담는 스택의 노드 하나

typedef struct {
  numStkNode *top;
} numStk;//숫자 스택의 탑

typedef struct {
  char oper;
  struct operStkNode *prev;
} operStkNode; //연산자를 담는 스택의 노드 하나

typedef struct { //연산자 스택의 탑
  operStkNode *top;
} operStk;

