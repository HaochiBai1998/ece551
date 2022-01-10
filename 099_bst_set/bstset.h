

#include"set.h"
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<exception>
#include<utility>
using namespace std;
/*
template<typename T>
class Set {
public:
  virtual void add(const T & key) = 0;
  virtual bool contains(const T& key) const = 0;
  virtual void remove(const T& key) = 0;
  virtual ~Set<T>() {}
};
*/
template<typename T>

class BstSet: public Set<T> {
  class Node{
  public:
    T data;
    Node * left;
    Node * right;
    Node():data(0),left(NULL),right(NULL){};
    Node(T t):data(t),left(NULL),right(NULL){};
  };
  Node * root;
 public:
  virtual void add(const T & key){
    Node ** current=&root;
    while(*current!=NULL){
      if((*current)->data==key){
	return;
      }
      else if((*current)->data>key){
        current=&((*current)->left);
      }
      else
        current=&((*current)->right);
    }
    *current=new Node(key);
    return;
  }
  
  Node ** find(const T & key) const {
    Node ** current=const_cast<Node **>(&root);
    while(*current!=NULL){
      if((*current)->data==key){
        return current;
      }
      else if((*current)->data>key){
        current=&(*current)->left;
      }
      else{
        current=&(*current)->right;
      }
    }
    return NULL;
  }
  
  virtual bool contains(const T& key) const{
    Node ** N=this->find(key);
    if (N==NULL)
      return false;
    return true;
  }
  
  void freeBst(Node * r){
    if(r==NULL){
      return;
    }
    freeBst(r->left);
    freeBst(r->right);
    //   cout<<"delete node:"<<r->data.first<<endl;
    delete r;
  }
  
  virtual void remove(const T& key){
    Node ** N = find(key);
    Node * N2 = *N;
    
    if (N2 == NULL) {
      return;
    }
    if (N2->left == NULL) {
      *N = N2->right;
    }
    else {
      Node **vic = &N2->left;
      while ((*vic)->right != NULL) {
        vic = &(*vic)->right;
      }
      *N = *vic;
      *vic = (*vic)->left;
      (*N)->left = N2->left;
      (*N)->right = N2->right;
    } 
    delete N2;
  }
  Node * copyTree(Node * r){
    if(r==NULL)
      return NULL;
    Node * rnt=new Node(r->data);
    rnt->left=copyTree(r->left);
    rnt->right=copyTree(r->right);
    return rnt;
  }
  BstSet():root(NULL){};
  
  BstSet(BstSet & rhs){
    root=copyTree(rhs.root);
  }

  Node * getRoot(){
    return root;
  }

  BstSet & operator=( BstSet & rhs){
    if(this!=&rhs){
      BstSet<T> temp=rhs;
      Node * ro=root;
      root=temp.root;
      temp.root=ro;
    }
    return * this;
  }

  
  virtual ~BstSet() {
    freeBst(root);
    root=NULL;
  }
};
