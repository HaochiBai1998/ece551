#include "IntArray.h"
#include <assert.h>
#include <ostream>
/*
class IntArray {
private:
  int * data;
  int numElements;*/
IntArray::IntArray():data(NULL),numElements(0) {
  
}
IntArray::IntArray(int n):data(new int[n]),numElements(n) {
  
}

IntArray::IntArray(const IntArray & rhs):data(new int[rhs.numElements]),numElements(rhs.numElements)  {
  for(int i=0;i<numElements;i++){
    data[i]=rhs.data[i];
  }
}
IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if(this!=&rhs){
    int * temp=new int[rhs.numElements];
    for(int i=0;i<rhs.numElements;i++){
      temp[i]=rhs.data[i];
    }
    delete[] data;
    numElements=rhs.numElements;
    data=temp;
  }
  return * this;
}
const int & IntArray::operator[](int index) const {
  assert(index>=0&&index<this->numElements);
  return this->data[index];
}
int & IntArray::operator[](int index) {
  assert(index>=0&&index<this->numElements);
  return this->data[index];
}

int IntArray::size() const {
  return this->numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if(this->numElements!=rhs.numElements){
    return false;
  }
  for (int i=0;i<this->numElements;i++){
    if(this->data[i]!=rhs.data[i])
      return false;
  }
  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  return !(*this==rhs);
  
}
IntArray IntArray::operator+(const IntArray & rhs) const {
  assert(numElements==rhs.numElements);
  IntArray temp(numElements);
  for (int i=0;i<numElements;i++){
    temp.data[i]=data[i]+rhs.data[i];
  }
  return temp;
}
/*IntArray & IntArray::operator+=(const IntArray & rhs) const {
  assert(numElements==rhs.numElements);
  for (int i=0;i<this->numElements;i++){
    data[i]+=rhs.data[i];
  }
  return *this;
  }*/

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  s<<"{";
  if(rhs.numElements!=0)
    s<<rhs.data[0];
  for (int i=1;i<rhs.numElements;i++){
    s<<", "<<rhs.data[i];
  }
  s<<"}";
  return s;
}
