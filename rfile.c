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
			else c = numNode->data;//you have to categorize decimal part and integer part of numNode in case of '.'.
		}while(c != EOF);
		fclose(fp);
	}
}
