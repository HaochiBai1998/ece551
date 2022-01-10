#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  if(inputName==NULL){
    perror("NULL inputName");
    exit(EXIT_FAILURE);
  }
  char * ptr=malloc((strlen(inputName)+8)*sizeof(*inputName));
  strcpy(ptr,inputName);
  strcat(ptr,".counts");
  return ptr;
}
