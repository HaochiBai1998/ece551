#include<stdio.h>
#include<stdlib.h>

struct _retire_info{
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;
double Count(int age,double initial, retire_info info){
  double out=initial;
  for (int i=0; i<info.months; i++)
    {
      printf("Age %3d month %2d you have $%.2f\n",age/12,age%12,out);
      out=out*(1+info.rate_of_return)+info.contribution;
      age++;
    }
      return out;
}
void retirement(int startAge, double initial, retire_info working, retire_info retired){
  double save=initial;
  int age=startAge;
  save=Count(age,save,working);
  age=age+working.months;
  save=Count(age,save,retired);
  age+=retired.months;
}
int main(){
  retire_info working;
  working.months=489;
  working.contribution=1000;
  working.rate_of_return=0.045/12;
  retire_info retired;
  retired.months=384;
  retired.contribution=-4000;
  retired.rate_of_return=0.01/12;
  int startAge=327;
  int initial=21345;
  retirement(startAge,initial,working,retired);
  return EXIT_SUCCESS;
}
