#include "node.h"
void Node::buildMap(BitString b, std::map<unsigned,BitString> & theMap) {
  //WRITE ME!
  if(sym!=NO_SYM){
    theMap[sym]=b;
    return;
  }
  left->buildMap(b.plusZero(),theMap);
  right->buildMap(b.plusOne(),theMap);
}

