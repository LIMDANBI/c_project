# include "cal.h"

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
  } //prefect(debugging)

//마이너스 수가 인자로 들어올 수 있음
  if(n1->sign == 1 && n2->sign == 1) ans->sign = 1;
  else if(n1->sign == 1){
    n1->sign = 0; ans = minus(n2, n1);
    return ans;
  }
  else if(n2->sign == 1){
    n2->sign = 0; ans = minus(n1, n2);
    return ans;
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

// --------------------- "+" ---------------------------------------

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
        itail1->prev->data--; itail1->data+=10;
        rappendNum(intpart, itail1->data-itail2->data - pull); pull = 0;
      }
      itail1 = itail1->prev; itail2 = itail2->prev;
    }
  }

  return ans;
}

//----------------------- "-" --------------------------------------

NUM* multi(NUM *n1, NUM *n2){
  NUM *ans = newNUM();
  numList *intpart = newNumList(); ans->integer = intpart;
  numList *decimpart = newNumList(); ans->decimal = decimpart;
  if(n1->sign != n2->sign) ans->sign = 0;  // 둘중 하나가 음수면 답은 음수, 아니면 양수
  else ans->sign = 1;

  while (1) {

  }


}

//----------------------- "*"----------------------------------------

// NUM* divi(NUM *n1, NUM *n2){
//
// }

// -------------- the end (until divi) -------------------------------

