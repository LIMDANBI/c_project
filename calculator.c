# include "cal.h"

//----------------------- "+" "+" --------------------------------------

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

  if(n1->sign == 1 && n2->sign == 1) ans->sign = 1;
  else if(n1->sign == 1){
    n1->sign = 0; ans = minus(n2, n1);
    return ans;
  }
  else if(n2->sign == 1){
    n2->sign = 0; ans = minus(n1, n2);
    return ans;
  }

  int who = whoMore(n1,n2);  // 누가 더 큰 수 인지 알려 준다

  if(who == 2){ // (빼는 수가 더 큰 경우)작은수에서 큰수를 빼면 결과는 마이너스
    NUM *tmp = n1; n1 = n2; n2 = tmp;  // 두 값을 반대로 뺀다
    ans->sign = 1;  // 부호는 마이너스가 될 것
  }
  else if(who == 0){ // 두수가 완전히 같다면 그 결과값은 0이 될것임.
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
          if(itail1->prev == NULL) ans->sign = 1;
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

  int carry = 0;
  NUM *ans = newNUM();
  numList *intpart = newNumList(); ans->integer = intpart;
  numList *decimpart = newNumList(); ans->decimal = decimpart;

  numNode *itail1 = getNumTail(n1->integer); numNode *dtail1 = getNumTail(n1->decimal);
  numNode *itail2 = getNumTail(n2->integer); numNode *dtail2 = getNumTail(n2->decimal);

  numList *tmp1 = newNumList(); numList *tmp2 = newNumList();  // 임식적으로 값을 저장할 것
  numList *resultTmp = newNumList();
  numNode *seat = getNumTail(resultTmp); numNode *oaseat =  getNumTail(resultTmp);

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

  numNode *tmpPath1 = getNumTail(tmp1);
  numNode *tmpPath2 = getNumTail(tmp2);

//계산 시작
 while(tmpPath2 != NULL){
   while (tmpPath1 != NULL) {
     int temp;
     if (seat == NULL){
       temp = carry + tmpPath1->data * tmpPath2->data;
       if(temp>9){
         carry = temp/10; temp = temp%10;
         rappendNum(resultTmp, temp);
       }
       else{
         rappendNum(resultTmp, temp); carry = 0;
       }
     }
     else{
       temp = carry + seat->data + tmpPath1->data * tmpPath2->data;
       if(temp>9){
         if(seat!=NULL){
           carry = temp/10; temp = temp%10;
           seat->data = temp;
         }
         else{
           carry = temp/10; temp = temp%10;
           rappendNum(resultTmp, temp); carry = 0;
         }
       }
       else{
         if(seat!=NULL){
           seat->data = temp; carry = 0;
         }
         else{
           rappendNum(resultTmp, temp); carry = 0;
         }
       }
       seat = seat->prev;
     }
     tmpPath1 = tmpPath1->prev;
   }
   if(carry != 0) {
    rappendNum(resultTmp, carry); carry = 0;
   }
   if(seat==NULL) seat = getNumTail(resultTmp);
   seat = seat->prev;
   tmpPath2 = tmpPath2->prev; tmpPath1 = getNumTail(tmp1);
   if(oaseat == NULL) oaseat = seat;
   else {
    oaseat = oaseat -> prev; seat = oaseat;
   }
 }

// 다시 소수로 돌려놓음
  numNode *resultTmpPath = getNumTail(resultTmp);  // 정수 계산결과 값의 꼬리노드를 리턴 받는다
  dtail1 = getNumTail(n1->decimal); dtail2 = getNumTail(n2->decimal);  // 들어온 두 인자의 소수 부분의 꼬리 노드를 리턴 받는다

  if(dtail1 == NULL && dtail2 == NULL) {  // 정수 부분만 있음 (둘다 소수점이 없음)
    ans->integer = resultTmp;
  }

  else if(dtail1 != NULL && dtail2 != NULL){  // 둘다 소수 부분이 있음
    while (dtail1 != NULL) {   // 먼저 n1 소수 부분만큼 돌면서 정답의 소수 부분에 역으로 넣어줌
      rappendNum(decimpart, resultTmpPath->data);
      resultTmpPath = resultTmpPath->prev; dtail1 = dtail1->prev;
    }
    while (dtail2 != NULL) { // n2소수 부분만큼 돌면서 정답의 소수 부분에 역으로 넣어줌
      rappendNum(decimpart, resultTmpPath->data);
      resultTmpPath = resultTmpPath->prev; dtail2 = dtail2->prev;
    }
    while(resultTmpPath != NULL){  // 소수 부분에 넣고 남은 부분은 정수 부분에 넣어 줌
      rappendNum(intpart, resultTmpPath->data);
      resultTmpPath = resultTmpPath->prev;
    }
    if(ans->integer == NULL) appendNum(intpart, 0);
  }

  else if(dtail2 == NULL) { //n1의 소수 부분만 있음
    while (dtail1 != NULL) {  // n1 소수 부분만큼 돌면서 정답의 소수 부분에 역으로 넣어줌
      rappendNum(decimpart, resultTmpPath->data);
      resultTmpPath = resultTmpPath->prev; dtail1 = dtail1->prev;
    }
    while (resultTmpPath != NULL) { // 소수 부분에 넣고 남은 부분은 정수 부분에 넣어 줌
      rappendNum(intpart, resultTmpPath->data);
      resultTmpPath = resultTmpPath->prev;
    }
    if(ans->integer == NULL) appendNum(intpart, 0);
  }

  else if(dtail1 == NULL){ // n2 의 소수부분만 있음
    while (dtail2 != NULL) {  // n2 소수 부분만큼 돌면서 정답의 소수 부분에 역으로 넣어줌
      rappendNum(decimpart, resultTmpPath->data);
      resultTmpPath = resultTmpPath->prev; dtail2 = dtail2->prev;
    }
    while(resultTmpPath != NULL){  // 소수 부분에 넣고 남은 부분은 정수 부분에 넣어 줌
      rappendNum(intpart, resultTmpPath->data);
      resultTmpPath = resultTmpPath->prev;
    }
  }
  return ans;
}

