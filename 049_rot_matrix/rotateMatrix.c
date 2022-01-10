#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char ** argv){
  char matrix[10][10];
  char pch[110];
  int c;
  int index=0;
  if(argc!=2) goto error;
  FILE *f= fopen(argv[1],"r");
  if (f==NULL) goto error;
  while((c=fgetc(f))!=EOF){
    if (index>=110) goto error;
    if (c>=128) goto error;
    if (c=='\n'&&index%11!=10) goto error;
    if (c!='\n'&&index%11==10) goto error;
    pch[index]=c;
    index++;
  }
  if (index!=110) goto error;
  for (int i=0;i<10;i++){
    for (int j=0;j<10;j++){
      matrix[j][9-i]=pch[i*11+j];
    }
  }
  for (int i=0;i<10;i++){
    for (int j=0;j<10;j++){
      fprintf(stdout,"%c",matrix[i][j]);
    }
    fprintf(stdout,"\n");
  }
  if(fclose(f)!=0) goto error;  
  return EXIT_SUCCESS;
 error:
  fprintf(stderr,"error\n");
  return EXIT_FAILURE;
}
