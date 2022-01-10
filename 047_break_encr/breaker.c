#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
void counter(FILE * f,int * array);
int eFinder(int* counter);
int main(int argc, char **argv){
  if (argc!=2){
    fprintf(stderr,"Usage: breaker inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1],"r");
  if (f==NULL){
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  int array[26] = {0};
  counter(f,array);
  if(fclose(f)!=0){
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  int index_e = eFinder(array);
  int key=(index_e-4+26)%26;
  printf("%d\n",key);
  return EXIT_SUCCESS;
}

void counter (FILE * f,int * array){
  int c;
  while ((c=fgetc(f))!=EOF){
    if (isalpha(c)){
      c=tolower(c);
      array[c-'a']++;
    }
  }
}

int eFinder(int * counter){
  int index_e;
  int max=0;
  for (int i=0;i<26;i++){
    if(max<counter[i]){
      index_e=i;
      max=counter[i];
    }
  }
  return index_e;
}
