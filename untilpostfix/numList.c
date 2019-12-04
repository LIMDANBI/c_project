# include "cal.h"

numNode* newNumNode(int data){  // [prev - data - next] 형의 노드
  numNode* tmp = (numNode*)malloc(sizeof(numNode));
  tmp->data = data;
  tmp->next = NULL;
  tmp->prev = NULL;
  return tmp;
}

numList* newNumList(){  // 정수, 소수 부분을 리스트로 연결
  numList* tmp = (numList*)malloc(sizeof(numList));
  tmp->head = NULL;
  return tmp;
}

NUM* newNUM(){  // 부호+정수부분+소수부분 (즉, 하나의 숫자)
  NUM* tmp = (NUM*)malloc(sizeof(NUM));
  tmp->sign = 0;
  tmp->decimal = NULL;
  tmp->integer = NULL;
  return tmp;
}

numNode* getNumTail(numList* list){  //원하는 리스트의 꼬리노드를 알 수 있음
  numNode* tmp = list->head;
  while(tmp->next != NULL){
    tmp = tmp->next;
  }
  return tmp;
}

void appendNum(numList* list, int data){  //원하는 리스트에 data를 추가할 수 있음
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

void rappendNum(numList *list, int data){  //appendNum과 반대로 거꾸로 데이터 추가
  numNode *tmp = newNumNode(data);
  if(list->head == NULL){
    list->head = tmp;
  }
  else{
    numNode *tail = getNumTail(list);
    tail->prev = tmp;
    tmp->next = tail;
  }
}

void printNum(NUM *n){  //NUM을 프린트 해주는 함수
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

