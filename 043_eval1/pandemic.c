#include "stdio.h"
#include "stdlib.h"
#include "pandemic.h"
#include "string.h"
#include "assert.h"
#include "ctype.h"
#include "math.h"

/*
Function split() can find out whether input string line is valid input
(The definition of a valid string is shown in pandemic.c:line 26). If it is valid,
this funtion will find out first ','character and store the country name string 
into dest->name. Finally return the pointer points to the address latter than ','
character.
*/ 
char * split(char *line,country_t *dest);
/*
Function ValidNumberString() will define whether non-digit characters exists in 
input string str. If any character other than digit number exists. Function will 
print error message and exit. line pointer is used to print error message 
*/
void isValidNumberString(char * str,char *line);

/*
Function parseLine will first judge whether the line string input is valid input. 
(A valid input need to meet following requests:
1. Input char pointer cannot be NULL pointer.
2. Input string contains at least one ',' character.
3. The string length before first ',' character need to be smaller than MAX_NAME_LEN-1.
4. the characters latter than first ',' can only contain digit number (0~9).)

If input line string is valid , this function will split the line string input into two
separate string by ',' character, then stores country name and converted population into
a country_t destination varible and return it.
*/
country_t parseLine(char * line) {
  //create a destination country_t varible to store result
  country_t dest;
  //create a country_t type pointer to change value of dest
  country_t * dest_p=&dest;
  //use assert function find whether line is a NULL pointer, if so, exit with error.
  assert(line);
  //define a new char pointer to store the splitted result.  
  char * newline=split(line,dest_p);
  //define whether newline is a string only contains digit characters.
  isValidNumberString(newline,line);
  //convert string to uint64_t varible by using atol function.
  //Then store converted varible to dest.population
  dest.population=(uint64_t) atol(newline);
  return dest;
}

/*
calcRunningAvg function will calculation the seven-day running average of case data.
It takes an array of daily case data, the number of days over which the data is measured,
and an array of doubles "avg", which is whether I will write the result of the calculation,
and return void.
*/
void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //if n_days<7 return
  if (n_days<7)
    return;
  //calculate 7 days Arithmetic average number then stores in avg array 
  for (size_t i=0;i<n_days-6;i++){
    avg[i]=(double)(data[i]+data[i+1]+data[i+2]+data[i+3]+data[i+4]+data[i+5]+data[i+6])/7;
  }
  return;
}

/*
function calcCumulative will calculates the cumulative numberof cases that day per 100,000 people,
, the sum of all the cases in that country so far per 100,000 people.It takes an array of daily case data, 
the number of days over which the data is measured,the population for that country,
 and an array of doubles "cum", which is where you will write the result of the calculation,
 and returns void. Array "cum" has length n_days.
*/
void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  double sum=0;
  //calculate cumulative cases per 100,000 people
  for (size_t i=0; i<n_days; i++){
    cum[i]=sum+(double)data[i]/pop*100000;
    sum=cum[i];
  }
  return;
}

/*
function printCountryWithMax will find the maximum number of daily cases of all countries represented in the data,
over the entire time period. It takes an array of country_t's with length n_countries, a 2-D array of data,
with each country's data representing a row (so data[0] is the zeroth country's time series data) of n_days and returns void.
*/
void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  unsigned max=0;
  // find the maximum of daily cases
  for (size_t i=0; i<n_countries;i++){
    for (size_t j=0; j<n_days;j++){
      if (data[i][j]>max)
	max=data[i][j];
    }
  }
  //print out one of the maximum daily cases and its country name 
  for (size_t i=0; i<n_countries;i++){
    for (size_t j=0; j<n_days;j++){
      if (data[i][j]==max){
	printf("%s has the most daily cases with %u\n",countries[i].name,max);
	return;
      }
    }
  }
}


char * split(char *line,country_t *dest){
  char * newline=line;
  char * pch=strchr(newline,',');
  if (pch==NULL){  
    fprintf(stderr,"Non-standard input: No comma in line\n");
    fprintf(stderr,"%s\n",line);
    exit(EXIT_FAILURE);
  }
  //find whether input line exceed maximum name length, if so, exit with error.
  size_t namelen=pch-newline;
  if (namelen>MAX_NAME_LEN-1){
    fprintf(stderr,"Non-standard input: Exceed maximum name length in line\n");
    fprintf(stderr,"%s\n",line);
    exit(EXIT_FAILURE);
  }
  //find whether input line starts with a ',' character, if so, exit with error.
  if (namelen==0){
    fprintf(stderr,"Non-standard input: No country name in line\n");
    fprintf(stderr,"%s\n",line);
    exit(EXIT_FAILURE);
  }
  //copy country name to dest.name
  strncpy(dest->name,newline,namelen);
  //add a '\0' termitator into the end of name
  dest->name[namelen]='\0';
  //let data points to the location after ',' character
  newline=newline+namelen+1;
  return newline;
}

void isValidNumberString(char * str,char *line){
  if(*str=='\0'||*str=='\n'){
    fprintf(stderr,"Non-standard input: No population data in line \n");
    fprintf(stderr,"%s\n",line);
    exit(EXIT_FAILURE);
  }
  //find whether exist characters other than number in line, if so, exit with error.
  for (size_t i=0;str[i]!='\0'&&str[i]!='\n';i++){
    if(!isdigit(str[i])){
      fprintf(stderr,"Non-standard input: There exists character other than number at position %td.\n",str-line);
      fprintf(stderr,"%s\n%*s\n",line,(int)(str+i-line+1),"^");
      exit(EXIT_FAILURE);
    }
  }
}
