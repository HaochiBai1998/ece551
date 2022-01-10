#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

/*
struct _kvpair_t {
  //DEFINE ME!
  char * key;
  char * value;
};
typedef struct _kvpair_t kvpair_t;
key = '%s' value = '%s'\n"
struct _kvarray_t {
  //DEFINE ME!
  kvpair_t * pairArr;
  size_t arrSize;
};
typedef struct _kvarray_t kvarray_t;
*/
kvpair_t split(char * line){
  kvpair_t pair;
  char *pch=strchr(line,'=');
  if(pch==NULL){
    fprintf(stderr,"Invalid input line: No '=' character");
    exit(EXIT_FAILURE);
  }
  if (pch-line==0){
    fprintf(stderr,"No key \n");
    exit(EXIT_FAILURE);
  }
  *pch='\0';
  char *pch2=strchr(pch+1,'\n');
  if(pch2==NULL){
    fprintf(stderr,"cannot find end of line\n");
    exit(EXIT_FAILURE);
  }
  if(pch2-pch+1==0){
    fprintf(stderr,"No value \n");
    exit(EXIT_FAILURE);
  }
  pair.key=malloc((pch-line+1)*sizeof(*line));
  if(pair.key==NULL){
    fprintf(stderr,"cannot malloc memory");
    exit(EXIT_FAILURE);
  }
  pair.value=malloc((pch2-pch)*sizeof(*(pch+1)));
  if(pair.value==NULL){
    fprintf(stderr,"cannot malloc memory");
    exit(EXIT_FAILURE);
  }
  *pch2='\0';
  strncpy(pair.key,line,pch-line+1);
  strncpy(pair.value,pch+1,pch2-pch);
  return pair;
}
kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  kvarray_t * dataArr=malloc(sizeof(*dataArr));
  if(dataArr==NULL){
    fprintf(stderr,"cannot malloc memory");
    exit(EXIT_FAILURE);
  }
  dataArr->arrSize=0;
  dataArr->pairArr=NULL;
  char * line=NULL;
  size_t sz;
  FILE * f=fopen(fname,"r");
  if (f==NULL){
    fprintf(stderr,"cannot openfile %s\n",fname);
    exit(EXIT_FAILURE);
  }
  size_t index=0;
  while(getline(&line,&sz,f)>=0){
    dataArr->arrSize++;
    dataArr->pairArr=realloc(dataArr->pairArr,dataArr->arrSize*sizeof(*dataArr->pairArr));
    if(dataArr->pairArr==NULL){
      fprintf(stderr,"cannot malloc memory");
      exit(EXIT_FAILURE);
    }
    kvpair_t  * ptr= dataArr->pairArr+index;
    *ptr=split(line);
    index++;
  }
  if(fclose(f)==EOF){
    fprintf(stderr,"cannot closefile %s\n",fname);
    exit(EXIT_FAILURE);
  }
  free(line);
  return dataArr;
}
void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i=0;i<pairs->arrSize;i++){
    free(pairs->pairArr[i].key);
    free(pairs->pairArr[i].value);
  }
  free(pairs->pairArr);
  free(pairs);
}


void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i=0;i<pairs->arrSize;i++){
    printf("key = '%s' value = '%s'\n",pairs->pairArr[i].key,pairs->pairArr[i].value); 
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i=0;i<pairs->arrSize;i++){
    if(strcmp(pairs->pairArr[i].key,key)==0)
      return pairs->pairArr[i].value;
  }
  return NULL;
}
