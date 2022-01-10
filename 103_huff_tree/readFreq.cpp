#include <stdio.h>
#include <cstdlib>
#include "readFreq.h"
#include <iostream>
#include <fstream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256 ) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  uint64_t * rnt=new uint64_t[257]();
  std::ifstream ifile(fname);
  char i;
  while(ifile.get(i)){
    rnt[(unsigned char)i]++;
  }
  rnt[256]++;
  return rnt;
}
