#ifndef __FUNCTION_H__
#define __FUNCTION_H__
template<typename R, typename A> 
class Function {
public:
  virtual R invoke(A arg) = 0;
  virtual ~Function() {}
};
#endif

int BSZ(Function<int, int> *f,int low,int high,int L,int H){
  int mid=(high+low)/2;
  if(mid==low||mid==high){
    //int d=f->invoke(mid);
    if((mid==high&&high!=H)||(mid==low))
      return mid;
    if(high==H)
      return H-1;
    else
      return L;
  }
  
  int data=f->invoke(mid);
  if(data<0){
    return BSZ(f,mid,high,L,H);
  }
  else if(data>0){
    return BSZ(f,low,mid,L,H);
  }
  else
    return mid;
}

int binarySearchForZero(Function<int, int> * f, int low, int high){
  return BSZ(f,low,high,low,high);
}
