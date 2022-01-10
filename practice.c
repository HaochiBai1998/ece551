/*
zy146 & qz127 & hb174 "Read double from stdin" Assignment
Ziling Yuan & Qinyun Zhang & Haochi Bai

Our code only accepts valid input:
1. if input starts with several " ", can just follow by only one sign('+','-')
2. After several " " and a sign, our input only accept one '.' character and digit numbers

*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"
#include "ctype.h"
#include "math.h"
#define MAX_INPUT 256 

double getDoubleInput(){
  char str[MAX_INPUT]; 
  printf("input a number:");  
  fgets(str,MAX_INPUT,stdin);
  //if input is NULL ,exit with error
  assert(str);
  char * pch=strchr(str,'.');
  //if input contains more than 2 '.' characters, exit with error
  if (pch!=NULL)
    pch=strchr(pch+1,'.');
  if (pch!=NULL){
    fprintf(stderr,"Non-standard input: More than one '.'\n");
    exit(EXIT_FAILURE);
  }
  char * ptr =str;
  //set a pointer which points to the str address after several ' ' and a sign
  while (*ptr==' '){
    ptr++;
  }
  if(*ptr=='+'||*ptr=='-')
    ptr++;
  //if the following characters contain characters other than digit number or '.',exit with error.
  while(*ptr!='\n'){
    if(!isdigit(*ptr)&&*ptr!='.'){
	fprintf(stderr,"Non-standard input:Invalid character\n");
	exit(EXIT_FAILURE);
    }
    ptr++;
  }
  return atof(str);
}
int main(){
  //test
  double ans=getDoubleInput();
  printf("%lf\n",ans);
  return EXIT_SUCCESS;
}
