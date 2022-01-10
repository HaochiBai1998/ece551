#include<cstdio>
#include<cstdlib>
class A{
  int y;
public:
  A():y(0){
    printf("A()\n");
  }
  A(int x):y(x){
    printf("A(%d)\n",x);
  }
};

class B{
  A a1;
  A a2;
  A a3;
public:
  B(int x):a3(x+1),a1(x-3){
    printf("B(%d)\n",x);
  }
};

int main(){
  B(42);
  return 0;
}
