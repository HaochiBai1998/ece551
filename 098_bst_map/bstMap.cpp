#include "bstmap.h"
#include<string>
int main(){
  BstMap<std::string,int> bstM;
  bstM.add("a1",10);
  bstM.add("a1",100);
  bstM.add("a7",9);
  bstM.add("a6",8);
  bstM.add("a4",7);
  bstM.add("a3",6);
  bstM.add("a9",5);
  bstM.add("a5",4);
  bstM.add("a0",3);
  bstM.add("a10",2);

  cout<<endl;
  bstM.print(bstM.getRoot());
  cout<<endl;
  bstM.remove("a1");
  bstM.print(bstM.getRoot());
  cout<<endl;
  bstM.remove("a6");
  bstM.print(bstM.getRoot());
  cout<<endl;
  bstM.remove("a9");
  bstM.print(bstM.getRoot());
  cout<<endl;
  bstM.remove("a7");
  bstM.print(bstM.getRoot());
  cout<<endl;

  try{
    cout<<endl;
  }
  catch (const invalid_argument & e){
    cerr<<"invalid_argument:"<<endl;
    exit(EXIT_FAILURE);
  }
  return 0;
}
