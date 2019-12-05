# include "cal.h"

numNode* newNumNode(int data){      // 새로운 넘노드를 만들어 줌
    numNode* tmp = (numNode* )malloc(sizeof(numNode));
    tmp->data = data;
    tmp->prev = NULL;
    tmp->next = NULL;
    return tmp;
}

NUM* newNUM(void){  // 새로운 넘을 만들어 줌
    NUM *tmp = (NUM* )malloc(sizeof(NUM));
    tmp->sign = 0;
    tmp->integer = NULL;
    tmp->decimal = NULL;
    return tmp;
}

numList* newNumList(void){  // 새로운 넘 리스트를 만들어 줌
    numList *tmp = (numList* )malloc(sizeof(numList));
    tmp->head = NULL;
    return tmp;
}


numNode* getNumTail(numList *list){  // 넘노드의 꼬리를 리턴해줌
    numNode *tmp = list->head;
    while(tmp->next != NULL){
        tmp = tmp->next;
    }
    return tmp;
}


void appendNum(numList *list, int nextN){   // 넘리스트와 숫자 하나를 받아서 넘 리스트를 확장
    numNode *tmp = newNumNode(nextN);
    if(list->head == NULL){
        list->head = tmp;
    }
    else{
        numNode *tail = getNumTail(list);
        tmp->prev = tail;
        tail->next = tmp;
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
    list->head = tmp;
  }
}

void printNum(NUM *n){ //넘을 프린트해주는 함수
  numNode *tmp = n->integer->head;
  if(n->sign) printf("-"); // + : 0, - : 1
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

