#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__
#include "provided.h"
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<ctype.h>

/*mallocedElements struct will store all the elements you malloced, which
can benefit free process not only when the code finish but error occurs

char ** strs is used to store converted story template, its size is strsSize.
char ** usedName is used to memorize names you have used, its size is usedNameSize
FILE * f is the file you have opened.
catarray_t * cats is used to store categories from input word file and names in each category 
*/
struct mallocedElements_t{
  char **strs;
  size_t strsSize;
  char ** usedName;
  size_t usedNameSize;
  FILE * f;
  catarray_t * cats;
};
typedef struct mallocedElements_t mallocedElements;
/*
init_m() function: output is a initialized mallocedElements pointer m.

this function will do 3 tasks:
1.create a mallocedElements * m pointer and malloc size for it first.
2.set strs,usedName,f,cats to NULL,set strsSize,usedNameSize to 0.
3.return m back.
*/
mallocedElements * init_m();
/*
exitFail function: input str is the error message you want to print
-------------------------------------------------------------------------------------------
when error occurs, exitFail function will call this function to print error message in stderr
 and exit failure.
------------------------------------------------------------------------------------------- 
*/
void exitFail(const char * str);
/*
freeCats function: input cats is a catarray_t pointer that we need to free memory.
-------------------------------------------------------------------------------------------
this function will free all the elements in cats.
-------------------------------------------------------------------------------------------
*/
void freeCats(catarray_t * cats);
/*
freeStrs function: 
input (strs) is a double char pointer which we need to free memory.
-------------------------------------------------------------------------------------------
this function will free all the elements in strs.
-------------------------------------------------------------------------------------------
*/
void freeStrs(char ** strs, size_t sz);
/*
freeAll function: 
input (m) stores all the elements we have malloced.
-------------------------------------------------------------------------------------------
this function will free m->strs & m->usedName & m->f if any of them is not a NULL pointer. 
-------------------------------------------------------------------------------------------
*/
void freeAll(mallocedElements * m);
/*
mixStrs function : 
input (str1) and (str2) are two strings.
input (dupLen) indicates the number of characters we want to concatenate from str2.
-------------------------------------------------------------------------------------------
this function will first realloc memory for concatenation task.
Then concatinate dupLen characters from str2 to str1, and return str1 pointer.
-------------------------------------------------------------------------------------------
*/
char * mixStrs(char * str1, const char * str2,size_t dupLen);
/*
printStrs function: 
input (str1) stores many strings 
input (sz) indicates the number of strings in str1.
-------------------------------------------------------------------------------------------
this function will print out all the strings in str1 and return void. 
-------------------------------------------------------------------------------------------
*/
void printStrs(char ** str1,size_t sz);
/*
convertCatToWord function:
input (head) is a pointer points to the head of line, which benefits printing error messages.
input (catName) is the string inside two '_' we need to convert.
input (preUsedOption) controls whether the function of reading strings from previous used 
string array is active
-------------------------------------------------------------------------------------------
this function will first check whether catName is a string only contains digits, if so,
this function will convert string to size_t number, if the number exceed m->usedNameSize or
N=0, this function will print error messages and exit with failure.
Otherwise, this function will call chooseWord function to convert catName to word.
-------------------------------------------------------------------------------------------
 */
const char * convertCatToWord(char * head,char * catName,mallocedElements * m,size_t preUsedOption);
/*
findUnderscore function: 
input (line) stores the string of story template need to be converted,
input (outLine) is a double pointer to a string to store converted output stroy template.
input (removeOption) determines whether we need to delete a name in a category after save to
output story template.
input (preUsedOption) controls whether the function of reading strings from previous used 
string array is active
-------------------------------------------------------------------------------------------
this function will find the next two '_' after line pointer,if no '_' have been found, string
line is directly copied to outLine.
If two '_' have been found, it will find a word from the category (ex. _animal_) in m->cats and 
replace it, then store the converted result to outLine and return changed line pointer.
-------------------------------------------------------------------------------------------
*/
char * findUnderscore(char * head,char * line,char ** outLine,mallocedElements * m,size_t removeOption,size_t preUsedOption);

/*
parseLine function, 
input (line) stores a string
input (removeOption) determines whether we need to delete a name in a category after save to
output story template.
input (preUsedOption) controls whether the function of reading strings from previous used 
string array is active
-------------------------------------------------------------------------------------------
*/
void parseLine(char * line,mallocedElements * m,size_t removeOption,size_t preUsedOption);
/*
addNewCat function: 
input (name) indicates a category string
input (word) indicates a word string.
input (cats) indicates where to add cat to.
-------------------------------------------------------------------------------------------
this function will malloc memory for m->cats and create a new category. name string indicates the 
new category name, word string indicates the first word save in that category. 
-------------------------------------------------------------------------------------------
*/
void addNewCat(char * name, char * word, catarray_t * cats);
/*
split function:  input line is a string that need to be splited.
-------------------------------------------------------------------------------------------
this function will split line by ':' character, characters before ':' indicates category,
characters after ':' indicates name, and later store in m->cats.
-------------------------------------------------------------------------------------------
 */
void split(char * line,mallocedElements * m);
/*
AreDigits function: 
input (cat) is a string.
-------------------------------------------------------------------------------------------
this function will check whether all the elements in cat string are digits.
Return 1 if they are all digits.
-------------------------------------------------------------------------------------------
 */
size_t AreDigits(char * cat);
/*
addUsedName function: 
input (str) is a name string.
input (usedNames) is a string array to store the new string
input usedNamesSize indicates the number of strings in usedNames
-------------------------------------------------------------------------------------------
this function will malloc new memory for m->usedName, then store str into
m->usedName and return void.
-------------------------------------------------------------------------------------------
 */
char ** addUsedName(const char * str,char ** usedNames, size_t *usedNamesSize);
/*
getCatWords function: 
input (filename) is a string indicates the file we need to open.
-------------------------------------------------------------------------------------------
this function will split each line in that file to category and name if line is valid.
Then store category and name into m->cat if there is not duplicated category&name exists
in m->cats. After the whole file is read, return void .
-------------------------------------------------------------------------------------------
 */
void getCatWords(mallocedElements * m,char * filename);
/*
getStoryTemp function: 
input (filename) is a string indicates the file we need to open,
input (removeOption) indicates whether we need to remove a word in a category,
input (preUsedOption) controls whether the function of reading strings from previous used 
string array is active
-------------------------------------------------------------------------------------------
this function will check whether each line in that file is valid. A valid line need to contain
even number of '_',the string between two '_' characters(ex. "_animal_"), need to be replaced to
randomly selected word from corresponding category form m->cats. Then convertedd lines will 
be stored in m->strs. After the whole file is read, return void.
-------------------------------------------------------------------------------------------
 */
void getStoryTemp(mallocedElements * m,char * filename, size_t removeOption,size_t preUsedOption);
/*
removeNthElementInStr function: 
input (strs) is a string array
input (strsSize) indicates string number,
input (index) indicates Nth string in strs we want to remove.
-------------------------------------------------------------------------------------------
this function will free Nth string, push other strings after that to its location then realloc
memory for m->cats->arr->words
-------------------------------------------------------------------------------------------
 */
char ** removeNthElementInStrs(char ** strs,size_t * strsSize,size_t index);

/*
removeWord function: 
input (word) indicates the word in catName category we need to remove.
-------------------------------------------------------------------------------------------
this function will find the word of category catName in m->cats, if find word in m->cats, it will
be removed and realloc memory.
-------------------------------------------------------------------------------------------
 */
void removeWord(char *catName,const char * word,catarray_t * cats);

#endif
