#include<cstdio>
#include<cstdlib>
#include<string>
#include<iostream>
using namespace std;
int main(){
  int a;
  cin>>a;
  cin.clear();
  string str;
  getline(&cin,&str,5);
  cout<<str;
}
