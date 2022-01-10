#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE

template<typename T>
class LinkedList{
  class Node{
  public:
    T data;
    Node * next;
    Node * prev;
    Node():data(0),next(NULL),prev(NULL){};
    Node(T d):data(d),next(NULL),prev(NULL){};
    Node(T d, Node * n, Node * p):data(d),next(n),prev(p){};
  };
  Node * head;
  Node * tail;
  int size;
public:
  void addFront(const T &item){
    head=new Node(item,head,NULL);
    if(tail==NULL)
      tail=head;
    else
      head->next->prev=head;
    size++;
  }
  void addBack(const T &item){
    tail=new Node(item,NULL,tail);
    if(head==NULL)
      head=tail;
    else
      tail->prev->next=tail;
    size++;
  }
  LinkedList & operator=(const LinkedList<T> & rhs){
    LinkedList<T> temp(rhs);
    Node * tmp;
    tmp=head;
    head=temp.head;
    temp.head=tmp;
    tmp=tail;
    tail=temp.tail;
    temp.tail=tmp;
    int sz=size;
    size=temp.size;
    temp.size=sz;
    return *this;
  }
  bool remove(const T &item){
    Node * current=head;
    if(current==NULL)
      return false;
    if(current->next==NULL&&current->data==item){
      delete current;
      head=NULL;
      tail=NULL;
      size--;
      return true;
    }    
    if(current->next!=NULL&&current->data==item){
      head=current->next;
      head->prev=NULL;
      delete current;
      size--;
      return true;
    }
    while(current->next!=NULL){
      Node * temp=current->next;
      if(item==temp->data){
	current->next=temp->next;
	if(temp->next!=NULL)
	  temp->next->prev=current;
	else
	  tail=current;
	delete temp;
	size--;
	return true;
      }
      current=current->next;
    }
    return false;
  }
  
  T& operator[](int index){
    Node * current=head;
    if(index<0||head==NULL)
      throw std::exception();
    for(int i=0;i<index;i++){
      if(current==NULL)
	throw std::exception();
      current=current->next;
    }
    return current->data;
  }

  const T& operator[](int index) const {
    Node * current=head;
    if(index<0||head==NULL)
      throw std::exception();
    for(int i=0;i<index;i++){
      if(current==NULL)
	throw std::exception();
      current=current->next;
    }
    return current->data;
  }

  int find(const T &item) const{
    Node * current=head;
    for(size_t i=0;current!=NULL;i++){
      if(item==current->data)
	return i;
      current=current->next;
    }
    return -1;
  }
  LinkedList():head(NULL),tail(NULL),size(0){ };
  LinkedList(const LinkedList<T> & rhs):head(NULL),tail(NULL),size(0){
    for(int i=0;i<rhs.size;i++){
      this->addBack(rhs[i]);
    }
  }
  ~LinkedList(){
    while(head!=NULL&&head->next!=NULL){
      Node * temp=head;
      head=head->next;
      head->prev=NULL;
      delete temp;
    }
    if(head!=NULL){
      delete head;
      head=NULL;
      tail=NULL;
    }
  }
  int getSize() const{
    return size;
  }
  friend void testList();
};
#endif
