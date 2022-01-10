#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
  int numRows=5;
  char*s="appleappleappleapple";
  char answer[1000]; 
  char ** ans=malloc(numRows*sizeof(*ans));
  char ** ptr=malloc(numRows*sizeof(*ptr));
  for(int i=0;i<numRows;i++){
    ans[i]=malloc(sizeof(**ans));
    ptr[i]=ans[i];
  }
  int count=0;
  int * mallocline= malloc(numRows*sizeof(*mallocline));
  for (int i=0;i<numRows;i++)
    mallocline[i]=1;
  int index=1;
  for(;*s!='\0';s++){
    **(ans+count)=*s;
    mallocline[count]++;
    ptr[count]=realloc(ptr[count],mallocline[count]*sizeof(char));
    ans[count]=ans[count]+1;
    count+=index;
    if(count==numRows-1){
      index=-1;   
    }
    if(count==0){
      index=1;
    }
  } 
  for(int i=0;i<numRows;i++)
    **(ans+i)='\0';
  for (int i=0;i<numRows;i++){
    strcat(answer,ptr[i]);
    free(ptr[i]);
  }
  free(ans);
  free(ptr);
  free(mallocline);
  printf("%s",answer);
  return 0;
}

