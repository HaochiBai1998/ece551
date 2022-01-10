#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"
void errorExit(const char * c){
  fprintf(stderr,"%s\n",c);
  exit(EXIT_FAILURE);
}
counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  counts_t * c=createCounts();
  FILE * f=fopen(filename,"r");
  if (f==NULL){
    fprintf(stderr,"%s:",filename);
    errorExit("cannot Openfile");
  }
  char *line =NULL;
  size_t sz;
  while(getline(&line,&sz,f)>=0){
    size_t i;
    char *pch=strchr(line,'\n');
    if(pch==NULL) errorExit("cannot find \n");
    *pch='\0';
    for (i=0; i<kvPairs->arrSize;i++){
      if(strncmp(line,kvPairs->pairArr[i].key,(strlen(kvPairs->pairArr[i].key)+1))==0){
	addCount(c,kvPairs->pairArr[i].value);
	break;
      }
    }
    if(i==kvPairs->arrSize)
      addCount(c,"<unknown>");
  }
  free(line);
  if(fclose(f)!=0) errorExit("cannot closefile");
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if(argc<2) errorExit("Invalid argument format\n");
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t *kvPairs=readKVs(argv[1]);
 //count from 2 to argc (call the number you count i)
  for (size_t i=2;i<argc;i++){
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t* c=countFile(argv[i],kvPairs);
    //compute the output file name from argv[i] (call this outName)
    char * outName=computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f=fopen(outName,"w");
    if (f==NULL) errorExit("Cannot Open newFile");
    //print the counts from c into the FILE f
    printCounts(c,f);
    //close f
    if(fclose(f)!=0) errorExit("Close file failure");
    //free the memory for outName and c
    freeCounts(c);
    free(outName);
  }
 //free the memory for kv
  freeKVs(kvPairs);
  return EXIT_SUCCESS;
}
