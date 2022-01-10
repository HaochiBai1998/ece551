
#include "rand_story.h"

int main(int argc, char ** argv){
  //check valid arguments
  if(argc!=2) exitFail("Usage: wordFile");
  mallocedElements * m=init_m();
  //check file open
  m->f=fopen(argv[1],"r");
  if(m->f==NULL) {
    freeAll(m);
    fprintf(stderr,"Word file name:%s\n",argv[1]);
    exitFail("Cannot Open word file!");
  }
  char * line=NULL;
  size_t sz;
  m->cats=malloc(sizeof(*m->cats));
  m->cats->n=0;
  m->cats->arr=NULL;
  //split each line in a word file and check whether each line is valid,
  //if its valid, split lines into category strings and word strings then store in m->cats.
  while(getline(&line,&sz,m->f)>=0){
    if(*line=='\0')
      continue;
    split(line,m);
  }
  free(line);
  printWords(m->cats);
  freeAll(m);
  return EXIT_SUCCESS;
}
