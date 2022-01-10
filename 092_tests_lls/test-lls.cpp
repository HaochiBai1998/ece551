#include "il.hpp"
#include<list>
#include<iostream>
#include<assert.h>

/*

void testList(void);
class IntList {
 private:
  class Node {
   public:
    int data;
    Node * next;
    Node * prev;
    Node() : data(0), next(NULL), prev(NULL){};
    Node(int d) : data(d), next(NULL), prev(NULL){};
  };
  Node * head;
  Node * tail;
  int size;

 public:
  IntList();
  IntList(const IntList & rhs);
  IntList & operator=(const IntList & rhs);
  ~IntList();
  void addFront(const int & item);
  void addBack(const int & item);
  bool remove(const int & item);
  int & operator[](int index);
  const int & operator[](int index) const;
  int find(const int & item);
  int getSize() const;
  friend void testList(void);
};

*/
void testList(){
  
  //[]
  IntList I1;
  assert(I1.size == 0 && I1.getSize()==0 && I1.head==NULL && I1.tail==NULL);
  IntList I2=I1;
  assert(I2.size == 0 && I2.getSize()==0 && I2.head==NULL && I2.tail==NULL);
  IntList I4(I1);
  assert(I2.size == 0 && I2.getSize()==0 && I2.head==NULL && I2.tail==NULL);

  //[1]
  I1.addFront(1);
  assert(I1.head==I1.tail && I1.head->data==1 && I1.head->prev==NULL && I1.head->next==NULL && I1.size==1 && I1.getSize()==1
	 && I1.find(1)==0 && I1[0]==1);
  I2=I1;
  assert(I2.head==I2.tail && I2.head->data==1 && I2.head->prev==NULL && I2.head->next==NULL && I2.size==1 && I2.getSize()==1
	 && I2.find(1)==0 && I2[0]==1);
  IntList I3(I1);
  assert(I3.head==I3.tail && I3.head->data==1 && I3.head->prev==NULL && I3.head->next==NULL && I3.size==1 && I3.getSize()==1
	 && I3.find(1)==0 && I3[0]==1);
  
  assert(!I1.remove(0));  
  assert(I1.head==I1.tail && I1.head->data==1 && I1.head->prev==NULL && I1.head->next==NULL && I1.size==1 && I1.getSize()==1
	 && I1.find(1)==0 && I1[0]==1);
  assert(I1.remove(1));
  //[]
  assert(I1.size == 0 && I1.getSize()==0 && I1.head==NULL && I1.tail==NULL);

  //[1]
  I1.addFront(1);
  assert(I1.head==I1.tail && I1.head->data==1 && I1.head->prev==NULL && I1.head->next==NULL && I1.size==1 && I1.getSize()==1
	 && I1.find(1)==0 && I1[0]==1);
  //[]
  I1.remove(1);
  //[1]
  I1.addBack(1);
  assert(I1.head==I1.tail && I1.head->data==1 && I1.head->prev==NULL && I1.head->next==NULL && I1.size==1 && I1.getSize()==1
	 && I1.find(1)==0 && I1[0]==1);
  //[]
  I1.remove(1);
  //[1]
  I1.addBack(1);
  assert(I1.head==I1.tail && I1.head->data==1 && I1.head->prev==NULL && I1.head->next==NULL && I1.size==1 && I1.getSize()==1
	 && I1.find(1)==0 && I1[0]==1);
  
  //[1 2]
  I1.addBack(2);
  assert(I1.head->next==I1.tail && I1.head->data==1 && I1.head->prev==NULL && I1.head->next==I1.tail && I1.tail->data==2
	 && I1.tail->prev==I1.head && I1.tail->next==NULL && I1.size==2 && I1.getSize()==2
	 && I1.find(1)==0 && I1[0]==1 && I1[1]==2 && I1.find(2)==1);
  I2=I1;
  assert(I2.head->next==I2.tail && I2.head->data==1 && I2.head->prev==NULL && I2.head->next==I2.tail && I2.tail->data==2
	 && I2.tail->prev==I2.head && I2.tail->next==NULL && I2.size==2 && I2.getSize()==2
	 && I2.find(1)==0 && I2[0]==1 && I2[1]==2 && I2.find(2)==1);
  IntList I5(I1);
  assert(I5.head->next==I5.tail && I5.head->data==1 && I5.head->prev==NULL && I5.head->next==I5.tail && I5.tail->data==2
	 && I5.tail->prev==I5.head && I5.tail->next==NULL && I5.size==2 && I5.getSize()==2
	 && I5.find(1)==0 && I5[0]==1 && I5[1]==2 && I5.find(2)==1);

  //[2 1]
  assert(I1.remove(2));
  I1.addFront(2);
  assert(I1.head->next==I1.tail && I1.head->data==2 && I1.head->prev==NULL && I1.head->next==I1.tail && I1.tail->data==1
	 && I1.tail->prev==I1.head && I1.tail->next==NULL && I1.size==2 && I1.getSize()==2
	 && I1.find(1)==1 && I1[0]==2 && I1[1]==1 && I1.find(2)==0);

  I1.remove(2);
  I1.addBack(2);
  //[1 2 3]
  I1.addBack(3);
  I2=I1;
  IntList I6(I1);
  assert(I2.head->next->next==I2.tail && I2.head->data==1 && I2.head->prev==NULL && I2.tail->data==3
	 && I2.head->next==I2.tail->prev && I2.head->next->prev==I2.head && I2.head->next->data==2
	 && I2.tail->prev->prev==I2.head && I2.tail->next==NULL && I2.size==3 && I2.getSize()==3
	 && I2.find(1)==0 && I2.find(2)==1 && I2.find(3)==2 && I2[0]==1 && I2[1]==2 && I2[2]==3);
  
  assert(I6.head->next->next==I6.tail && I6.head->data==1 && I6.head->prev==NULL && I6.tail->data==3
	 && I6.head->next==I6.tail->prev && I6.head->next->prev==I6.head && I6.head->next->data==2
	 && I6.tail->prev->prev==I6.head && I6.tail->next==NULL && I6.size==3 && I6.getSize()==3
	 && I6.find(1)==0 && I6.find(2)==1 && I6.find(3)==2 && I6[0]==1 && I6[1]==2 && I6[2]==3);
  assert(I1.head->next->next==I1.tail && I1.head->data==1 && I1.head->prev==NULL && I1.tail->data==3
	 && I1.head->next==I1.tail->prev && I1.head->next->prev==I1.head && I1.head->next->data==2
	 && I1.tail->prev->prev==I1.head && I1.tail->next==NULL && I1.size==3 && I1.getSize()==3
	 && I1.find(1)==0 && I1.find(2)==1 && I1.find(3)==2 && I1[0]==1 && I1[1]==2 && I1[2]==3);

  //[1 3]
  I1.remove(2);
  assert(I1.head->next==I1.tail && I1.head->data==1 && I1.head->prev==NULL && I1.head->next==I1.tail && I1.tail->data==3
	 && I1.tail->prev==I1.head && I1.tail->next==NULL && I1.size==2 && I1.getSize()==2
	 && I1.find(1)==0 && I1[0]==1 && I1[1]==3 && I1.find(3)==1);
  
}
int main(){  
  testList();
  return EXIT_SUCCESS;
}
