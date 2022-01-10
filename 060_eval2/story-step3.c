#include "rand_story.h"
int main(int argc, char ** argv){

  if (argc!=3) exitFail("Usage: Wordfile Storyfile");
  mallocedElements * m=init_m();
  //split lines in Wordfile into words&categories then store in m->cats.
  getCatWords(m,argv[1]);
  if(fclose(m->f)!=0){
    freeAll(m);
    exitFail("Cannot Close File!");
  }
  //read words from different categories in m->cats and convert lines in Storyfile to
  //Output story template and store in m->strs.
  getStoryTemp(m,argv[2],0,1);
  printStrs(m->strs,m->strsSize);
  freeAll(m);
  return EXIT_SUCCESS;
}
