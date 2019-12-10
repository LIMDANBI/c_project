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
  if(tmp == NULL){
    return tmp;
  }
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
    numNode *recent = list->head;
    recent->prev = tmp;
    tmp->next = recent;
    list->head = tmp;
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

int whoMore(NUM *n1, NUM *n2){  // 두 넘을 받아서 누가 더 큰지 리턴해주는 함수
                                // 0 :같다 , 1: n1이 더 크다 , 2: n2가 더 크다.

  if(n1->sign > n2->sign) return 2;
  else if(n1->sign < n2->sign) return 1;
  
  numNode *intpart1 = n1->integer->head;
  numNode *intpart2 = n2->integer->head;
  while (1) {  // 정수 부분 부터 체크
    if(intpart1==NULL && intpart2==NULL){  // 길이가 같을 때
      intpart1 = n1->integer->head; intpart2 = n2->integer->head;
      while (intpart1!=NULL) {
        if(intpart1->data > intpart2->data) return 1;
        else if(intpart2->data > intpart1->data) return 2;
        intpart1 = intpart1->next; intpart2 = intpart2->next;
      }
      break;
    }
    else if(intpart1==NULL) return 2;  // 만약 1.11000 과 1.11이라면,,
    else if(intpart2==NULL) return 1;
    intpart1 = intpart1->next; intpart2 = intpart2->next;
  }

  numNode *decimpart1 = n1->decimal->head;
  numNode *decimpart2 = n2->decimal->head;
  while (decimpart1!=NULL && decimpart2!=NULL) { // 소수 부분 체크
    if(decimpart1->data>decimpart2->data) return 1;
    else if(decimpart2->data>decimpart1->data) return 2;
    decimpart1 = decimpart1->next; decimpart2 = decimpart2->next;
  }
  if(decimpart1 != NULL) return 1;  // 다음 수가 0으로 끝난다면??
  else if(decimpart2 != NULL) return 2;
  return 0;
}

void deletzero(NUM *n){    // 불필요한 앞뒤 0 을 제거해주는 함수
  numNode *intpart = n->integer->head;
  numNode *decimpart = getNumTail(n->decimal);
  while(intpart->data == 0){
    numNode *freed = intpart;
    intpart = intpart->next;
    n->integer->head = intpart;
    // free(freed);
  }
  while(decimpart->data == 0){
    numNode *freed = decimpart;
    decimpart = decimpart->prev;
    // free(freed);
  }
}

