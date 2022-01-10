#include<stdio.h>
#include<stdlib.h>
unsigned power(unsigned x, unsigned y);
void run_check(unsigned x, unsigned y, unsigned expected_ans){
  unsigned ans=power(x,y);
  if (ans!=expected_ans)
    {
      printf("test fail\n");
      exit(EXIT_FAILURE);
    }
}
int main (){
  run_check(0,0,1);
  run_check(0,1,0);
  run_check(1,0,1);
  run_check(1,1,1);
  run_check(1,2,1);
  run_check(2,0,1);
  run_check(2,1,2);
  run_check(2,2,4);
  run_check(2,3,8);
  run_check(2,4,16);
  run_check(3,0,1);
  run_check(3,1,3);
  run_check(3,2,9);
  run_check(3,3,27);
  run_check(4,0,1);
  run_check(4,1,4);
  run_check(4,2,16);
  run_check(4,3,64);
  run_check(4,4,256);
  run_check(4,5,1024);
  run_check(5,0,1);
  run_check(5,1,5);
  run_check(5,2,25);
  run_check(5,3,125);
  run_check(4294967295,1,4294967295);
  return EXIT_SUCCESS;
}
