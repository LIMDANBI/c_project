# include <stdio.h>
# include <stdlib.h>
// -------------------- 구조체 --------------------------
typedef struct numNode{  // 넘 노드 구조체 [prev - 숫자 - next]
    int data;
    struct numNode *prev;
    struct numNode *next;
}numNode;

typedef struct numList{ //넘리스트의 헤드를 가리킴
    numNode *head;
}numList;

typedef struct NUM{ //넘 구조체, 부호-정수-소수
    int sign;  // + : 0 , - : 1
    numList *integer;
    numList *decimal;
}NUM;

typedef struct expressionNode{ //익스프레션 노드
  char oper;
  NUM *num;
  struct expressionNode *next;
}expressionNode;

typedef struct expressionList{  // 익스프레션 리스트, 중위표기식을 받아 후위표기식으로 변환할 때 사용  (후위표기식도 expressionList 타입임)
  expressionNode *head;
}expressionList;

// stack 구조체
typedef struct numStkNode{
  NUM *num;
  struct numStkNode *prev;
}numStkNode;  //숫자를 담는 스택의 노드 하나

typedef struct numStk{
  numStkNode *top;
}numStk;  //숫자 스택  (계산할 때 사용할 거임)

typedef struct operStkNode{
  char oper;
  struct operStkNode *prev;
} operStkNode; //연산자를 담는 스택의 노드 하나

typedef struct operStk{
  operStkNode *top;
}operStk; //연산자 스택 (in2post에서 사용할거임)


//------------------------함수-------------------------

//numList.c
numNode* newNumNode(int data);
NUM* newNUM(void);
numList* newNumList(void);
numNode* getNumTail(numList *list);
void appendNum(numList *list, int data);
void rappendNum(numList *list, int data);
void printNum(NUM *n);

//expressionList.c
int operCheck(char oper); //연산자이면 1, 아니면 0 리턴
expressionNode* newExpressionNode(NUM* num, char oper);
expressionList* newExpressionList(void);
expressionNode* getExpressionTail(expressionList *list);
void appendExpression(expressionList *list, expressionNode *exnode);

//stack.c
numStkNode* newNumStkNode(NUM *n);
numStk* newNumStk(void);
void push2Nstk(numStk *stk, NUM *n);
NUM* pop4Nstk(numStk *stk);
int emptyNstk(numStk *stk);
operStkNode* newOperStkNode(char c);
operStk* newOperStk();
void push2Ostk(operStk* stk, char c);
char pop4Ostk(operStk* stk);
int emptyOstk(operStk* stk);

//postfix.c
int getOperPri(char oper);
void in2post(expressionList *infix, expressionList *postfix);

//calculator.c
NUM* plus(NUM *n1, NUM *n2);
NUM* minus(NUM *n1, NUM *n2);
NUM* multi(NUM *n1, NUM *n2);
NUM* divi(NUM *n1, NUM *n2);

