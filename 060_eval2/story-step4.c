#include "rand_story.h"
int main(int argc, char ** argv){
  if (argc!=3 && argc!=4) exitFail("Usage: (ReuseOption:'-n') WordFile StoryFile");
  mallocedElements * m=init_m();
  //if Reuse Option=1, words in categories can be reused after store to output story template.
  if (argc==3){
    getCatWords(m,argv[1]);
    if(fclose(m->f)!=0){
      fprintf(stderr,"File name:%s\n",argv[1]);
      freeAll(m);
      exitFail("Cannot Close File");
    }
    getStoryTemp(m,argv[2],0,1);
    printStrs(m->strs,m->strsSize);
  }
  //if Reuse Option=0, words in categories should be deleted after store to output story template
  if(argc==4){
    if(strcmp(argv[1],"-n")) exitFail("Usage: (ReuseOption:'-n') WordFile StoryFile");
    getCatWords(m,argv[2]);
    if(fclose(m->f)!=0){
      fprintf(stderr,"File name:%s\n",argv[2]);
      freeAll(m);
      exitFail("Cannot Close File");
    }
    getStoryTemp(m,argv[3],1,1);
    printStrs(m->strs,m->strsSize);
  }
  freeAll(m);
  return EXIT_SUCCESS;
}
