# include <iostream>
# include <stack>
# include <string>
using namespace std;

int getOperPri(char c){   //연산자의 우선순위를 리턴하는 함수  (in2post에서 사용)
  if(c == '*' || c=='/'){
    return 3;
  }
  else if(c == '+' || c == '-'){
    return 2;
  }
  else if(c == '(' || c == ')'){
    return 1;
  } 
}

int operCheck(char oper){ //연산자이면 1, 아니면 0 리턴
  if(oper == '+' || oper == '-' ||oper == '*' || oper == '(' || oper == ')'){
    return 1;
  }
  else{
    return 0;
  }
}

int main(){

    stack<char> oper;

    string s; cin>>s;

    for(int i=0; i<s.size(); i++){

      if(operCheck(s[i])){  //연산자인 경우
        if(s[i] == '('){
          oper.push(s[i]);
        }

        else if(s[i] == ')'){
          while(!oper.empty() && oper.top() != '('){ //비었는지도 같이!!  
            char a = oper.top();
            cout << a;
            oper.pop();
          }
          oper.pop();
        }

        else if(s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/'){
          while(!oper.empty() && getOperPri(oper.top()) >= getOperPri(s[i])){  //같은 경우도 팝!! 
              char a = oper.top();
              cout << a;
              oper.pop();
          }
          oper.push(s[i]);
        }
      }

      else{  // 숫자인 경우
        cout << s[i];
      }
    }
    while(!oper.empty()){
      char a = oper.top();
      cout << a;
      oper.pop();
    }
    return 0;
  }

