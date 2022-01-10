
#include "function.h"
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <cmath>
#include <iostream>
using namespace std;

extern int binarySearchForZero(Function<int, int> * f, int low, int high);

class CountedIntFn : public Function<int,int>{
protected:
  unsigned remaining;
  Function<int,int> * f;
  const char * mesg;
public:
  CountedIntFn(unsigned n, Function<int,int> * fn, const char * m): remaining(n),
                                                                    f(fn),
                                                                    mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr,"Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;

    //  cout<<mesg<<remaining<<endl;
    return f->invoke(arg);
  }
};

void check(Function<int,int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg){
  int rem;
  if(high>low)
    rem=log2(high-low)+1;
  else
    rem=1;
  CountedIntFn c1(rem,f,mesg);
  //if(high==low){
    //   cerr<<"function: "<<mesg<<" has same low & high"<<endl;
    //exit(EXIT_SUCCESS);
  //}
  int index=binarySearchForZero(&c1,low,high);
  if (index!=expected_ans){
    cerr<<"function: "<<mesg<<" expected index= "<<expected_ans<<" but get "<<index<<endl; 
    exit(EXIT_FAILURE);
  }
}
/*
template<typename R, typename A>
class Function {
public:
  virtual R invoke(A arg) = 0;
  virtual ~Function() {}
};
*/

class SinFunction : public Function<int, int> {
public:
  virtual int invoke(int arg) {
    return 10000000 * (sin(arg/100000.0) - 0.5);
  }
};

class LinearFunction: public Function<int, int>{
public:
  virtual int invoke(int arg){
    return arg;
  }
};
  
int main(){
  SinFunction sin;
  LinearFunction linear;
  check(&sin,0,150000,52359,"Sinfunction");
  check(&linear,1,2,1,"LinearFunction");
  check(&linear,-2,0,-1,"LinearFunction");  
  check(&linear,-2,-1,-2,"LinearFunction");
  check(&linear,1,2,1,"LinearFunction");
  check(&linear,0,2,0,"LinearFunction");
  check(&linear,-1,3,0,"LinearFunction");
  check(&linear,1,1,1,"LinearFunction");
  return EXIT_SUCCESS;
}
