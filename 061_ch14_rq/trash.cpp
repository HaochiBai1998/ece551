#include<cstdio>
#include<cstdlib>
void swap(const int & x, int & y){
  int temp=x;
  // x=y;
  y=temp;
}
int main(void){
  int a=3;
  int b=4;
  int &c=b;
  swap(3,b);
  printf("a=%d,b=%d\n",a,c);
  return 0;
}
