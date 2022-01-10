#include<string>
#include<cstdio>
#include<iostream>
#include<vector>

using namespace std;
template<typename T>
class Set{
  vector<T> sets;
public:
  void add(const T & element){
    for(typename vector<T>::const_iterator it=sets.begin();it!=sets.end();++it){
      if(*it==element)
	return;
    }
    sets.push_back(element);
  }
  bool contains(const T & element) const{
    for(typename vector<T>::const_iterator it=sets.begin();it!=sets.end();++it){
      if(*it==element)
        return true;
    }
    return false;
  }
  size_t cardinality() const{
    return sets.size();
  }
  void remove(const T & element ){
    for(typename vector<T>::const_iterator it=sets.begin();it!=sets.end();++it){
      if(*it==element){
        sets.erase(it);
	return;
      }
    }
    return;
  }
  Set<T> intersect(const Set<T> & rhs) const{
    Set<T> InterS;
    for(typename vector<T>::const_iterator it=sets.begin();it!=sets.end();++it){
      if(rhs.contains(*it)){
	InterS.add(*it);
      }
    }
    return InterS;
  }
  
  Set<T> myUnion(const Set<T> & rhs) const{
    Set<T> UnionS;
    for(typename vector<T>::const_iterator it_rhs=rhs.sets.begin();it_rhs!=rhs.sets.end();++it_rhs){
      UnionS.add(*it_rhs);
    }
    for(typename vector<T>::const_iterator it_lhs=sets.begin();it_lhs!=sets.end();++it_lhs){
      UnionS.add(*it_lhs);
    }
    return UnionS;
  } 
  Set<T> diff(const Set<T> & rhs) const{
    Set<T> DiffS;
    Set<T> UnionS=this->myUnion(rhs);
    Set<T> InterS=this->intersect(rhs);
    for(typename vector<T>::const_iterator it_U=UnionS.sets.begin();it_U!=UnionS.sets.end();++it_U){
      if(!InterS.contains(*it_U)){
	DiffS.add(*it_U);
      }
    }
    return DiffS;
  }
  void printSets() const{
    for(typename vector<T>::const_iterator it=sets.begin();it!=sets.end();++it){
      cout<<*it<<endl;
    }
  }
};


int main(){
  Set<int> s1;
  for(int i=0;i<10;i++){
    s1.add(i);
  }
  Set<int> s2;
  for(int i=3;i<13;i++){
    s2.add(i);
  }

  cout<<"Test int:\n";

  cout<<"S1:\n";
  s1.printSets();
  cout<<endl;


  
  cout<<"S2:\n";
  s2.printSets();
  cout<<endl;

  Set<int> s3=s1.intersect(s2);

  cout<<"Intersect:\n";
  s3.printSets();
  cout<<endl;
  
  Set<int> s4=s1.myUnion(s2);

  cout<<"Union:\n";
  s4.printSets();
  cout<<endl;

  Set<int> s5=s1.diff(s2);

  cout<<"Diff:\n";
  s5.printSets();
  cout<<endl;
  
  return EXIT_SUCCESS;
}
