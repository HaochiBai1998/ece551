#include<string>
#include<cstdio>
#include<cstdlib>
#include<sstream>

class Expression{
public:
  virtual std::string toString() const=0;
  virtual long evaluate() const=0;
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
  virtual long evaluate() const {
    return l;
  }
};

class allFormExpression: public Expression{
protected:
  Expression * e1;
  Expression * e2;
  std::string op;
public:
  allFormExpression(Expression * lhs,Expression * rhs,std::string str):e1(lhs),e2(rhs),op(str){};
  virtual ~allFormExpression(){
    delete e1;
    delete e2;
  }
  virtual std::string toString() const {
    return "("+e1->toString()+" "+op+" "+e2->toString()+")"; 
  }
  virtual long evaluate() const {
    if(op=="+")
      return e1->evaluate()+e2->evaluate();
    else if(op=="-")
      return e1->evaluate()-e2->evaluate();
    else if(op=="*")
      return e1->evaluate()*e2->evaluate();
    else 
      return e1->evaluate()/e2->evaluate();
  }  
};

class PlusExpression: public allFormExpression{
public:
  virtual ~PlusExpression(){}
  PlusExpression(Expression * lhs, Expression * rhs):allFormExpression(lhs,rhs,"+"){};
  virtual std::string toString() const{
    return "("+e1->toString()+" "+op+" "+e2->toString()+")";   
  }
};
class MinusExpression: public allFormExpression{
public:
  virtual ~MinusExpression(){}
  MinusExpression(Expression * lhs, Expression * rhs):allFormExpression(lhs,rhs,"-"){};
  virtual std::string toString() const{
    return "("+e1->toString()+" "+op+" "+e2->toString()+")";   
  }
  
};
class TimesExpression: public allFormExpression{
public:
  virtual ~TimesExpression(){}
  TimesExpression(Expression * lhs, Expression * rhs):allFormExpression(lhs,rhs,"*"){};
  virtual std::string toString() const{
    return "("+e1->toString()+" "+op+" "+e2->toString()+")";   
  }
  
};
class DivExpression: public allFormExpression{
public:
  virtual ~DivExpression(){}
  DivExpression(Expression * lhs, Expression * rhs):allFormExpression(lhs,rhs,"/"){};
  virtual std::string toString() const{
    return "("+e1->toString()+" "+op+" "+e2->toString()+")";   
  }
};
