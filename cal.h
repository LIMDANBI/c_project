#include <stdio.h>
#include <stdlib.h>

typedef struct numNode {
    int num;
    struct numNode *prev;
    struct numNode *next;
} numNode;

typedef struct {
    numNode *head;
} numList;

typedef struct {
    int sign;               // 1 : +, 0 : -.
    numList *integer;
    numList *decimal;
} NUM;

typedef struct {
  NUM *num;
  char oper;
  struct expressionNode *next;
} expressionNode;

typedef struct {
  expressionNode *head;
} expressionList;

typedef struct {
  NUM *num;
  numStackNode *prev;
} numStackNode;

typedef struct {
  numStackNode *top;
} numStack;

typedef struct {
  caar oper;
  struct operStackNode *prev;
} operStackNode;

typedef struct {
  operStackNode *top;
} operStack;


