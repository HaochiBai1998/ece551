#include "rand_story.h"
mallocedElements *init_m(){
  mallocedElements * m;
  m=malloc(sizeof(*m));
  m->strs=NULL;
  m->strsSize=0;
  m->f=NULL;
  m->cats=NULL;
  m->usedName=NULL;
  m->usedNameSize=0;
  return m;
}

void exitFail(const char * str){
  fprintf(stderr,"%s\n",str);
  exit(EXIT_FAILURE);
}

void freeCats(catarray_t * cats){
  for (int i=0;i<cats->n;i++){
    //free each category name
    free(cats->arr[i].name);
    for(int j=0;j<cats->arr[i].n_words;j++){
      //free each word in a category
      free(cats->arr[i].words[j]);
    }
    free(cats->arr[i].words);
  }
  free(cats->arr);
  free(cats);
  return;
}

void freeStrs(char ** strs, size_t sz){
  for(int i=0;i<sz;i++){
    free(strs[i]);
  }
  free(strs);
}

void freeAll(mallocedElements * m){
  if (m==NULL)
    return;
  if (m->strs!=NULL){
    freeStrs(m->strs,m->strsSize);
  }
  if(m->cats!=NULL){
    freeCats(m->cats);
  }
  if(m->f!=NULL){
    if(fclose(m->f)!=0) exitFail("Cannot close file!");
  }
  if(m->usedName!=NULL){
    freeStrs(m->usedName,m->usedNameSize);
  }
  free(m);
}

char * mixStrs(char * str1, const char * str2,size_t dupLen){
  size_t resultStrLen=strlen(str1)+dupLen+1;
  char * tmpStr=strndup(str2,dupLen);
  str1=realloc(str1,resultStrLen*sizeof(*str1));
  strcat(str1,tmpStr);
  free(tmpStr);
  return str1;
}

void printStrs(char ** str1,size_t sz){
  for(int i=0;i<sz;i++){
    printf("%s",str1[i]);
  }
}

size_t AreDigits(char * str){
  if(strlen(str)==0)
    return 0;
  while(*str!='\0'){
    //when detect any character in str is non-digit return 0
    if(!isdigit(*str))
      return 0;
    str++;
  }
  return 1;
}

char ** addUsedName(const char * str,char ** usedNames, size_t * usedNamesSize){
  //realloc memory to add a recently used name
  usedNames=realloc(usedNames,(*usedNamesSize+1)*sizeof(*usedNames));
  usedNames[*usedNamesSize]=strdup(str);
  (*usedNamesSize)++;
  return usedNames;
}

const char * convertCatToWord(char * head,char * catName,mallocedElements * m,size_t preUsedOption){
  const char * nameRnt;
  if(AreDigits(catName)&&preUsedOption==1){
    size_t i=atoi(catName);
    //if catName is integer and the number within the range of usedName string array,duplicate to outline
    if(i==0||i>m->usedNameSize){
      fprintf(stderr,"Line:\n%s Index:\n%s\n",head,catName);
      free(head);
      free(catName);
      freeAll(m);
      exitFail("Invalid used name Index out of reused string array scope");
    }
    nameRnt=m->usedName[m->usedNameSize-i];
  }
  else{
    nameRnt=chooseWord(catName,m->cats);
  }
  return nameRnt;
}
  
char * findUnderscore(char * head,char * line,char ** outLine,mallocedElements * m,size_t removeOption,size_t preUsedOption){
  //find first '_' 
  char * startUnderscore=strchr(line,'_');
  //if no '_' exists in line, directly duplicate string line to outline
  if(startUnderscore==NULL){
    *outLine=mixStrs(*outLine,line,strlen(line));
    line=line+strlen(line);
    return line;
  }
  size_t dupLen=startUnderscore-line;
  *outLine=mixStrs(*outLine,line,dupLen);
  char * endUnderscore=strchr(startUnderscore+1,'_');
  //if no second '_' exists in line, its not a valid line, exit
  if(endUnderscore==NULL) {
    fprintf(stderr,"Line:\n%s\n",head);
    free(head);
    freeAll(m);
    exitFail("Invalid line without endUnderscore");
  }
  size_t nameLen=endUnderscore-startUnderscore-1;
  char * catName=strndup(startUnderscore+1,nameLen);
  const char *nameRnt=convertCatToWord(head,catName,m,preUsedOption);
  m->usedName=addUsedName(nameRnt,m->usedName,&(m->usedNameSize));
  *outLine=mixStrs(*outLine,nameRnt,strlen(nameRnt));
  //let line points to the location whether we have not executed
  line=endUnderscore+1;
  if(removeOption==1){
    removeWord(catName,nameRnt,m->cats);
  }
  free(catName);
  return line;
}

void parseLine(char * line,mallocedElements * m,size_t removeOption, size_t preUsedOption){
  m->strs=realloc(m->strs,(m->strsSize+1)*sizeof(*m->strs));
  m->strs[m->strsSize]=malloc(sizeof(*m->strs[m->strsSize]));
  char ** outLine=&(m->strs[m->strsSize]);
  m->strsSize++;
  **outLine='\0';
  char * head=line;
  while (*line!='\0'){
    line=findUnderscore(head,line,outLine,m,removeOption,preUsedOption);
  }
  return;
}

void addNewCat(char * name, char * word, catarray_t *cats){
  for(int i=0;i<cats->n;i++){
    //if a word exists in name category, this function will no longer create a new one.
    if(!strcmp(cats->arr[i].name,name)){
      category_t * currCat=&(cats->arr[i]);
      for (int j=0;j<currCat->n_words;j++){
	if (!strcmp(currCat->words[j],word)){
	  return;
	}
      }
      //if it is a new word in a existing category, create a new word.
      currCat->words=realloc(currCat->words,(currCat->n_words+1)*sizeof(*currCat->words));
      currCat->words[currCat->n_words]=strdup(word);
      currCat->n_words++;
      return;
    }
  }
  //if it is a new category, create a new one and add a word into it.
  cats->arr=realloc(cats->arr,(cats->n+1)*sizeof(*cats->arr));
  cats->arr[cats->n].name=strdup(name);
  cats->arr[cats->n].words=malloc(sizeof(*cats->arr[cats->n].words));
  *cats->arr[cats->n].words=strdup(word);
  cats->arr[cats->n].n_words=1;
  cats->n++;
  return;
}

void getCatWords(mallocedElements * m,char * filename){
  m->f=fopen(filename,"r");
  if(m->f==NULL) {
    freeAll(m);
    exitFail("Cannot Open input File!");
  }
  char * line=NULL;
  size_t sz;
  m->cats=malloc(sizeof(*m->cats));
  m->cats->n=0;
  m->cats->arr=NULL;
  //get each line in a file, split it and then stores in m->cats
  while(getline(&line,&sz,m->f)>=0){
    if(*line=='\0')
      continue;
    split(line,m);
  }
  free(line);
  return;
}

void getStoryTemp(mallocedElements * m,char * filename,size_t removeOption,size_t preUsedOption){
  m->f=fopen(filename,"r");
  if (m->f==NULL){
    freeAll(m);
    exitFail("cannot Open Input File!");
  }
  char * line=NULL;
  size_t sz;
  m->strs=malloc(sizeof(*m->strs));
  m->strsSize=0;
  //get each line in a file, parse the converted lines as story template into m->strs.
  while(getline(&line,&sz,m->f)>=0){
    if(strlen(line)==0)
      continue;
    parseLine(line,m,removeOption,preUsedOption);
  }
  free(line);
  return;
}

void split(char * line,mallocedElements * m){
  //check valid line
  char * colonPtr=strchr(line,':');
  if (colonPtr==NULL){
    free(line);
    freeAll(m);
    exitFail("invalid word format!");
  }
  char * EnterPtr=strchr(line,'\n');
  char * name=strndup(line,colonPtr-line);
  char * word=strndup(colonPtr+1,EnterPtr-colonPtr-1);
  //add new category to m->cats
  addNewCat(name,word,m->cats);
  free(word);
  free(name);
  return;
}

char ** removeNthElementInStrs(char ** strs,size_t *strsSize, size_t index){
  //remove (index)th element in a string array, push subsequent strings to its place
  for (int i=index;i<*strsSize-1;i++){
    free(strs[i]);
    strs[i]=strdup(strs[i+1]);
  }
  free(strs[*strsSize-1]);
  //realloc memory space
  strs=realloc(strs,(*strsSize-1)*sizeof(*strs));
  (*strsSize)--;
  return strs;
}

void removeWord(char * catName, const char * word,catarray_t * cats){
  //if there is a word of catName category in m->cats category array, remove this word from that category.
  for (int i=0;i<cats->n;i++){
    if(!strcmp(cats->arr[i].name,catName)){
      for (int j=0;j<cats->arr[i].n_words;j++){
	if(!strcmp(cats->arr[i].words[j],word)){
	  cats->arr[i].words=removeNthElementInStrs(cats->arr[i].words,&(cats->arr[i].n_words),j);
	  return;
	}
      }
    }
  }
}
