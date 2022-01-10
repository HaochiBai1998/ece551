/*

struct _one_count_t {
  //DEFINE ME
  char * inputName;
  char * counts;
};
typedef struct _one_count_t one_count_t;

struct _counts_t {
  //DEFINE ME
  one_count_t * arr;
  size_t arrSize;
};
typedef struct _counts_t counts_t;


*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * countsArr=malloc(sizeof(*countsArr));
  countsArr->arr=NULL;
  countsArr->arrSize=0;
  return countsArr;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name==NULL){
    addCount(c,"<unknown>");
    return;
  }
  size_t i=0;
  for (i=0;i<c->arrSize;i++){
    if (strcmp(c->arr[i].inputName,name)==0){
      c->arr[i].counts++;
      return;
    }
  }
  c->arrSize++;
  c->arr=realloc(c->arr,c->arrSize*sizeof(*c->arr));
  c->arr[i].inputName=malloc((strlen(name)+1)*sizeof(char));
  strcpy(c->arr[i].inputName,name);
  c->arr[i].counts=1;
  return;
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  one_count_t * unknown=NULL;
  
  for (int i=0;i<c->arrSize;i++){
    if(strcmp(c->arr[i].inputName,"<unknown>")==0){
      unknown=c->arr+i;

    }
    else fprintf(outFile,"%s: %ld\n",c->arr[i].inputName,c->arr[i].counts);
   }
   if(unknown!=NULL)
      fprintf(outFile,"%s: %ld\n",unknown->inputName,unknown->counts);
  
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i=0;i<c->arrSize;i++){
    free(c->arr[i].inputName);
  }
  free(c->arr);
  free(c);
}
