numNode* newNumNode(int data){      // 새로운 넘노드를 만들어 줌
    numNode* tmp = (numNode* )malloc(sizeof(numNode));
    tmp->data = data;
    tmp->prev = NULL;
    tmp->next = NULL;
    return tmp;
}

NUM* newNUM(){  // 새로운 넘을 만들어 줌
    NUM* tmp = (NUM* )malloc(sizeof(NUM));
    tmp->sign = 0;
    tmp->integer = NULL;
    tmp->decimal = NULL;
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

