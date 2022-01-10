#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  char * line =NULL;
  size_t sz;
  size_t count=0;
  if(argc==1){
    char ** strArray=malloc(sizeof(*strArray));
    for (;getline(&line,&sz,stdin)>1;count++){
      strArray=realloc(strArray,(count+1)*sizeof(*strArray));
      strArray[count]=line;
      line=NULL;
    }
    free(line);
    sortData(strArray,count);
    for(size_t i=0; i<count;i++){
      fprintf(stdout,strArray[i],"s");
      free(strArray[i]);
    }
    free(strArray);
  }
  else if (argc>1){
    for(size_t i=0; i<argc-1;i++){
      line=NULL;
      char *fileName;
      char ** strArray=malloc(sizeof(*strArray));
      fileName=malloc((strlen(argv[i+1])+1)*sizeof(*fileName));
      strcpy(fileName,argv[i+1]);
      FILE *f=fopen(fileName,"r");
      if (f==NULL){
	free(strArray);
	fprintf(stderr,"cannot open file %s",fileName);
	free(fileName);
	exit(EXIT_FAILURE);
      }
      free(fileName);
      for(count=0;getline(&line,&sz,f)>=0;count++){
	strArray=realloc(strArray,(count+1)*sizeof(*strArray));
	strArray[count]=line;
	line=NULL;
      }
      free(line);  
      sortData(strArray,count);
      for(size_t i=0; i<count;i++){
	fprintf(stdout,strArray[i],"s");
	free(strArray[i]);
      }
      free(strArray);
      if(fclose(f)!=0){
	perror("Failed to close file!");
	exit(EXIT_FAILURE);
      }
    }
  }
  else {
    fprintf(stderr,"Usage:encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
