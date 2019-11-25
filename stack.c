#include "cal.h"

operStackNode* newOperStackNode(char c)
{
    operStackNode *temp = (operStackNode *)malloc(sizeof(operStackNode));
    temp->oper = c;
    temp->prev = NULL;
    return temp;
}

operStack* newOperStack(void)
{
    operStack *temp = (operStack *)malloc(sizeof(operStack));
    temp->top = NULL;
    return temp;
}

void pushToOperStack(operStack *stk, operStackNode *newnode)
{
    newnode->prev = stk->top;
    stk->top = newnode;
}

char popFromOperStack(operStack *stk)
{
    char poped = stack->top->oper;
    operStackNode *temp = stack->top->prev;
    free(stack->top);
    stack->top = temp;
    return poped;
}

numStackNode* newNumStackNode(NUM *n)
{
    numStackNode *temp = (numStackNode *)malloc(sizeof(numStackNode));
    temp ->num = n;
    temp->prev = NULL;
    return temp;
}

numStack *newNumStack(void)
{
    numStack *temp = (numStack *)malloc(sizeof(numStack));
    temp->top = NULL;
    return temp;
}

void pushToNumStack(numStack *stk, numStackNode *newnode)
{
    newnode->prev = stk->top;
    stk->top = newnode;
}

NUM *popFromNumStack(numStack *stk)
{
    NUM *poped = stk->top->num;
    numStackNode *temp = stk->top->prev;
    free(stk->top);
    stk->top = temp;
    return poped;
}

