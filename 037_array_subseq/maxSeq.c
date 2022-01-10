#include<stdio.h>
#include<stdlib.h>

int max(int a,int b){
  if (a>b)
    return a;
  else
    return b;
}

size_t  maxSeq(int * array, size_t n){
  int cnt=0;
  int max_cnt=0;
  int index;
  if(n==0)
    return 0;
  else
    {
      cnt=1;
      max_cnt=1;
      index=array[0];
    }

  for (size_t i=1;i<n;i++)
    {
      if (array[i]>index){
	cnt++;
	max_cnt=max(max_cnt,cnt);
      }
      else{
	max_cnt=max(max_cnt,cnt);
	cnt=1;
      }
      index=array[i];
    }
  return max_cnt;
}
