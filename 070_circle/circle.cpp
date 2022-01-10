/*
class Circle{
  Point center;
  const double radius;
public:
  Circle(Point init_c,double init_r);
  void move(double dx,double dy);
  double intersectionArea(const Circle & otherCircle);
}
*/
#include "circle.hpp"
#include "cmath"
#define pi acos(-1)
Circle::Circle(Point init_c,double init_r):center(init_c),radius(init_r){}
void Circle::move(double dx,double dy){
  center.Point::move(dx,dy);
}
double Circle::intersectionArea(const Circle & otherCircle){
  const double d= center.distanceFrom(otherCircle.center);
  double r1=radius;
  double r2=otherCircle.radius;
  if((r1+r2)<=d)
    return 0;
  if(r1>r2){
    double tmp=r1;
    r1=r2;
    r2=tmp;
  }
  if(r2-r1>=d)
    return pi*r1*r1;
  double ang1=acos((r1*r1+d*d-r2*r2)/(2*r1*d));
  double ang2=acos((-r1*r1+d*d+r2*r2)/(2*r2*d));
  return ang1*r1*r1+ang2*r2*r2-d*r1*sin(ang1);
}
