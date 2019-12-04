# include "cal.h"

numNode* newNumNode(int data){
  numNode* tmp = (numNode*)malloc(sizeof(numNode));
  tmp->data = data;
  tmp->next = NULL;
  tmp->prev = NULL;
  return tmp;
}

numList* newNumList(){
  numList* tmp = (numList*)malloc(sizeof(numList));
  tmp->head = NULL;
  return tmp;
}

NUM* newNUM(){
  NUM* tmp = (NUM*)malloc(sizeof(NUM));
  tmp->sign = 0;
  tmp->decimal = NULL;
  tmp->integer = NULL;
  return tmp;
}

numNode* getNumTail(numList* list){
  numNode* tmp = list->head;
  while(tmp->next != NULL){
    tmp = tmp->next;
  }
  return tmp;
}

void appendNum(numList* list, int data){
  numNode* tmp = newNumNode(data);
  if(list->head == NULL){
    list->head = tmp;
  }
  else{
    numNode* tail = getNumTail(list);
    tail->next = tmp;
    tmp->prev = tail;
  }
}

void printNum(NUM *n){
  numNode *tmp = n->integer->head;
  if(n->sign) printf("-");
  while(tmp!=NULL){
    printf("%d",tmp->data);
    tmp = tmp->next;
  }
  if(n->decimal->head != NULL) {
  printf(".");
  tmp = n->decimal->head;
  while(tmp!=NULL) {
      printf("%d",tmp->data);
      tmp = tmp->next;
    }
  }
}

