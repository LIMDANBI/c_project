# include "cal.h"

//----------------------- "+" --------------------------------------

NUM* plus(NUM *n1, NUM *n2){

  int carry = 0;
  NUM *ans = newNUM();
  numList *intpart = newNumList(); ans->integer = intpart;
  numList *decimpart = newNumList();ans->decimal = decimpart;

  numNode *d1 = n1->decimal->head;
  numNode *d2 = n2->decimal->head;

  while(1){   //두수의 소수부분 자리수를 맞춰준다
    if(d1==NULL && d2==NULL) break;
    else if(d1==NULL){
      while(d2!=NULL){
        appendNum(n1->decimal, 0); d2 = d2->next;
      }
      break;
    }
    else if(d2==NULL){  //d2== NULL
      while(d1!=NULL){
        appendNum(n2->decimal, 0); d1 = d1->next;
      }
      break;
    }
    else{ //둘다 null X
      d1 = d1->next; d2 = d2->next;
    }
  }

  numNode *dtail1 = getNumTail(n1->decimal);
  numNode *dtail2 = getNumTail(n2->decimal);

  while (dtail1 != NULL) {  //소수 부분 계산 시작
    int tmp = carry + dtail1->data + dtail2->data;
    if(tmp>9){
      carry = tmp/10; tmp = tmp%10;
      rappendNum(decimpart, tmp);
    }
    else{
      rappendNum(decimpart, tmp);  carry = 0;
    }
    dtail1 = dtail1->prev; dtail2 = dtail2->prev;
  }

  numNode *itail1 = getNumTail(n1->integer);
  numNode *itail2 = getNumTail(n2->integer);

  while(1){  // 정수부분 계산 시작
    if(itail1==NULL && itail2==NULL){
      break;
    }
    else if(itail1 == NULL){
        int tmp = carry + itail2->data;
        if(tmp>9){
          carry = tmp/10; tmp = tmp%10;
          rappendNum(intpart, tmp);
        }
        else {
          rappendNum(intpart, tmp); carry = 0;
        }
        itail2 = itail2->prev;
      }
      else if(itail2==NULL){ //itail2 == NULL
        int tmp = carry + itail1->data;
        if(tmp>9){
          carry = tmp/10; tmp = tmp%10;
          rappendNum(intpart, tmp);
        }
        else {
          rappendNum(intpart, tmp); carry = 0;
        }
        itail1 = itail1->prev;
      }
    else{ //둘다 널이 아닐 때
      int tmp = carry + itail1->data + itail2->data;
      if(tmp>9){
        carry = tmp/10; tmp = tmp%10;
        rappendNum(intpart, tmp);
      }
      else {
        rappendNum(intpart, tmp); carry = 0;
      }
      itail1 = itail1->prev; itail2= itail2->prev;
    }
  }
  if(carry != 0){
    rappendNum(intpart, carry);
  }
  return ans;
}

//----------------------- "-" --------------------------------------

NUM* minus(NUM *n1, NUM *n2){

  NUM *ans = newNUM();
  numList *intpart = newNumList(); ans->integer = intpart;
  numList *decimpart = newNumList(); ans->decimal = decimpart;
  int pull = 0;  //정수 부분에서 끌어올 때 사용

  int who = whoMore(n1,n2);  // 누가 더 큰 수 인지 알려 준다
  //
  if(who == 2){ // (빼는 수가 더 큰 경우)작은수에서 큰수를 빼면 결과는 마이너스
    NUM *tmp = n1; n1 = n2; n2 = tmp;  // 두 값을 반대로 뺀다
  }
  if(who == 0){ // 두수가 완전히 같다면 그 결과값은 0이 될것임.
    appendNum(ans->integer, 0);
    return ans;
  }

  // who == 1 인 경우 위에서 아무처리도 하지 않고 계산 시작 !!
  numNode *d1 = n1->decimal->head;
  numNode *d2 = n2->decimal->head;

  while(1){   //두수의 소수부분 자리수를 맞춰준다. 짧은 수에 빈자리에 0을 채워 줌
    if(d1==NULL && d2==NULL) break;
    else if(d1==NULL){
      while(d2!=NULL){
        appendNum(n1->decimal, 0); d2 = d2->next;
      }
      break;
    }
    else if(d2==NULL){  //d2== NULL
      while(d1!=NULL){
        appendNum(n2->decimal, 0); d1 = d1->next;
      }
      break;
    }
    else{ //둘다 null X
      d1 = d1->next; d2 = d2->next;
    }
  }

  numNode *dtail1 = getNumTail(n1->decimal);
  numNode *dtail2 = getNumTail(n2->decimal);

  while (dtail1 != NULL) { // 소수 부분(같은 자리수를 가지고 있음) 알의 자리 부터 계산 시작
    if(dtail2->data > dtail1->data){ //앞에서 숫자를 끌어와야 할 때
      if(dtail1->prev != NULL){
        dtail1->prev->data--; dtail1->data+=10; //앞에서 수를 끌어옴
        rappendNum(decimpart, dtail1->data - dtail2->data);
      }
      else{
        pull = 1; dtail1->data+=10; //정수 부분에서 수를 끌어옴
        rappendNum(decimpart, dtail1->data - dtail2->data);
      }
    }
    else rappendNum(decimpart, dtail1->data - dtail2->data);
    dtail1 = dtail1->prev; dtail2 = dtail2->prev;
  }

  numNode *itail1 = getNumTail(n1->integer);
  numNode *itail2 = getNumTail(n2->integer);

  while (1) {  // 정수 부분 일의 자리 부터 계산 시작
    if(itail1==NULL && itail2==NULL) break;
    else if(itail2 == NULL){
      while(itail1 != NULL){
        rappendNum(intpart, itail1->data - pull); pull = 0;
        itail1 = itail1->prev;
      }
      break;
    }
    else{  //둘다 널이 아닐 때
      if(itail1->data-pull>=itail2->data){
        rappendNum(intpart, itail1->data-itail2->data - pull); pull = 0;
      }
      else{  // 빼는 값이 같거나 더 큰 경우
        if(itail1->prev->data!=0 || itail1->data>itail2->data){
          itail1->prev->data--; itail1->data+=10;
          rappendNum(intpart, itail1->data-itail2->data - pull); pull = 0;
        }
        else{
          ans->sign = 1;
          rappendNum(intpart, itail2->data-itail1->data-pull); pull = 0;
        }
      }
      itail1 = itail1->prev; itail2 = itail2->prev;
    }
  }

  return ans;
}

//----------------------- "*" --------------------------------------

NUM* multi(NUM *n1, NUM *n2){

  printNum(n1);
  printf("\n");
  printNum(n2);
  printf("\n");

  int carry = 0;
  NUM *ans = newNUM();
  numList *intpart = newNumList(); ans->integer = intpart;
  numList *decimpart = newNumList(); ans->decimal = decimpart;

  numNode *itail1 = getNumTail(n1->integer); numNode *dtail1 = getNumTail(n1->decimal);
  numNode *itail2 = getNumTail(n2->integer); numNode *dtail2 = getNumTail(n2->decimal);

  numList *tmp1 = newNumList();  // 임식적으로 값을 저장할 것
  numList *tmp2 = newNumList();
  numNode *seat = NULL;

// 정수로 만들어 주기
  while(dtail1 != NULL){
    rappendNum(tmp1, dtail1->data);
    dtail1 = dtail1->prev;
  }
  while(itail1 != NULL){
    rappendNum(tmp1, itail1->data);
    itail1 = itail1->prev;
  }

  while(dtail2 != NULL){
    rappendNum(tmp2, dtail2->data);
    dtail2 = dtail2->prev;
  }
  while(itail2 != NULL){
    rappendNum(tmp2, itail2->data);
    itail2 = itail2->prev;
  }


// 제대로 바뀌는지 츌력해보는 부분    처음것만 바뀜,,
  numNode *path1 = tmp1->head;
  while (path1 != NULL) {
    printf("%d", path1->data);
    path1 = path1->next;
  }

  printf("\n");

  numNode *path2 = tmp2->head;
  while (path2 != NULL) {
    printf("%d", path2->data);
    path2 = path2->next;
  }


// 계산 시작
 // while(tmp2 != NULL){
 //   while (tmp1 != NULL) {
 //
 //   }
 // }


// 다시 소수로 돌려놓음
  // while (dtail1 == NULL && dtail2 == NULL) {
  //
  // }



}
