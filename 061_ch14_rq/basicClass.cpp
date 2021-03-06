#include<stdio.h>
#include<stdlib.h>


class BankAccount{
private:
  static unsigned long  nextAccountNumber;
  unsigned long accountNumber;
  double balance;
public:
  unsigned long getAccountNumber(){
    return accountNumber;
  }
  void deposit(double amount){
    balance+=amount;
  }
  double withdraw(double amount){
    if (amount<=balance){
      balance-=balance;
      return amount;
    }
    else{
      double actualAmount=balance;
      balance=0;
      return actualAmount;
    }
  }
  void initAccount(){
    accountNumber=nextAccountNumber;
    nextAccountNumber++;
    balance=0;
  }
};
unsigned long BankAccount::nextAccountNumber=5;
  

int main(void){
  BankAccount b1;
  BankAccount b2;
  b1.initAccount();
  b2.initAccount();
  b1.deposit(42.50);
  b2.deposit(199.87);
  return 0;

}
