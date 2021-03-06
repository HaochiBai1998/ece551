#include "point.hpp"
class Circle{
  Point center;
  const double radius;
public:
  Circle(Point init_c,double init_r);
  void move(double dx,double dy);
  double intersectionArea(const Circle & otherCircle);
};
