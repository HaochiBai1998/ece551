#include "rand_story.h"

int main(int argc, char ** argv){
  //check valid arguments
  if (argc!=2) exitFail("Usage: storyFile.");
  mallocedElements * m=init_m();
  //check file open
  m->f=fopen(argv[1],"r");
  if (m->f==NULL){
    fprintf(stderr,"Input FileName:%s\n",argv[1]);
    exitFail("Cannot Open Input File!");
  }
  char * line=NULL;
  size_t sz;
  m->strs=malloc(sizeof(*m->strs));
  m->strsSize=0;
  while(getline(&line,&sz,m->f)>=0){
    //parseLine should find out start and end '_' in a line and detect invalid line format,
    //then parse converted strings to m->strs. 
    if(strlen(line)==0)
      continue;
    parseLine(line,m,0,0);
  }
  free(line);
  printStrs(m->strs,m->strsSize);
  freeAll(m);
  return EXIT_SUCCESS;
}
