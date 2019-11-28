#include <stdio.h>

int main(){
	FILE *fp;
	int c;
	fp = fopen("input","r");
	if(fp == NULL)
		perror("Error opening file");
	else{
		do{
			c = getc(fp);
			if(c == '+') c = operStkNode->oper;
			else if(c == '-') c = operStkNode->oper;
			else if(c == '*') c = operStkNode->oper;
			else if(c == '.') pass;
			else{
				while(c != '.'){
					c = numList->integer;
				}
				if(c == '.') pass;
				else if(c != '.') c = numList->decimal;
			}//you have to add codes about ERROR when '.' appear twice.
		}while(c != EOF);
		fclose(fp);
	}
}
