#include<string>
#include<cstdio>
#include<cstdlib>
#include<sstream>

class Expression{
public:
  virtual std::string toString() const=0;
  virtual ~Expression(){};
};

class NumExpression: public Expression{
protected:
  long l;
public:
  NumExpression(long l1):l(l1){};
  virtual ~NumExpression(){
  };
  virtual std::string toString() const{
    std::stringstream str;
    str<<l;
    return str.str();
  }
};
  
class PlusExpression: public Expression{
protected:
  Expression * e1;
  Expression * e2;
public:
  virtual ~PlusExpression(){
    delete e1;
    delete e2;
  }
  PlusExpression(Expression * lhs, Expression * rhs):e1(lhs),e2(rhs){}
  virtual std::string toString() const{
    return"("+e1->toString()+" + "+e2->toString()+")"; 
  }
};
