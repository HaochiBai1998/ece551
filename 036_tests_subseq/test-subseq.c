//size_t  maxSeq(int * array, size_t n);
#include<stdio.h>
#include<stdlib.h>
size_t maxSeq(int *array, size_t n);
int *p;
void test(int array[],size_t n, size_t ans){
  size_t reg=maxSeq(array,n);
  p=array;
  if (reg!=ans){
    //    printf("expected %ld get %ld\n",ans,reg);
    exit(EXIT_FAILURE);
  }
}
int main(){
  test(p,0,0);
  test((int[]){1},1,1);
  test((int[]){1,1},2,1);
  test((int[]){-2147483648,2147483647},2,2);
  test((int[]){1,2,3,2,4},5,3);
  test((int[]){1,2,1,3,2,4,6,1,3,5,7},11,4);
  test((int[]){1,2,3,4,5,6,7,8},8,8);
  return 0;
}
