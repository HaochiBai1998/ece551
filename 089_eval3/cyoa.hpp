#ifndef __CYOA_HPP__
#define __CYOA_HPP__
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::exception;
using std::filebuf;
using std::ios;
using std::istream;
using std::pair;
using std::queue;
using std::set;
using std::string;
using std::to_string;
using std::vector;
#define UNDEF_DEPTH -1
/*
*@brief enum define the status of a Page.

* UNDEF_STAT indicates undefined status.
* NAV_STAT indicates navigation page
* WIN_STAT indicates navigation page
* LOSE_STAT indicates navigation page
*/
enum {
    UNDEF_STAT,
    NAV_STAT,
    WIN_STAT,
    LOSE_STAT
};
/*
*@brief this enum define different error types

*/
enum {
    OPEN_FILE_FAILURE,
    CLOSE_FILE_FAILURE,
    EMPTY_STORY,
    INVALID_ARGUMENT_FORMAT_CYOA1,
    INVALID_ARGUMENT_FORMAT_CYOA2,
    INVALID_ARGUMENT_FORMAT_CYOA3,
    INVALID_ARGUMENT_FORMAT_CYOA4,
    INVALID_REFERENCE_PAGE_NUMBER,
    EXIST_UNREFERENCED_PAGE,
    NO_WIN_LOSE_PAGE,
    INVALID_NAVIGATION_FORMAT,
    INVALID_STORY_TERMINATATION,
    INVALID_PAGE_FORMAT_EMPTY_PAGE,
    INVALID_PAGE_FORMAT
};
/**
 * @brief Path class:
 *          Path class contains all the essential information and methods
 *          related to the page transfer path in a story
 * @field path:
 *          a vector of pair to store the page transfer path, the first element
 *          represents page number, the second element represents the choice of
 *          story.
 */

class Path {
    vector<pair<size_t, size_t> > path;
public:
    /**
     * @brief  operator < compares path.size() between two Path object.
     */
    bool operator<(const Path & rhs) const ;
    
    /**
     * @brief   push a pair {pageNum,choice} into vector path.
     * 
     * @param pageNum: story page number.
     * @param choice: choice of user to navigate next page.
     */
    void push_back(size_t pageNum, size_t choice);

    /**
     * @brief   pop the last element out from vector path.
     */
    void pop_back();
    
    /**
     * @brief   find whether a page exists in a path.
     * 
     * @param pageNum: the page number to find.
     * @return true if find that page, elsewise false.
     */ 
    bool find(size_t pageNum);
    /**
     * @brief   print vector path into cout.
     */ 
    void printPath()const;
        
    /**
     * @brief   get the vector path from Path object.
     * 
     * @return the path from Path object.
     */ 
    vector<pair<size_t,size_t> > getPath()  ;
};

/**
 * @brief Page class:
 *          Page class contains some essential information of
 *          a single page. 
 * @field navigation:
 *          Some pages have navigation section, each pair 
 *          in a navigation field indicates the number   
 *          of page it can reach and the text information.
 * @field text: 
 *          The content of the page.
 * @field status:
 *          The status of page
 */

class Page {
    vector<pair<size_t, string> > navigation;
    vector<string> text;
    size_t status;

public:
    /**
     * @brief   Print the content of a Page. 
     */
    void printPage();
    /**
     * @brief   This method will check whether input file is a valid file.
     *          If input is valid, change the status of page and
     *          then read page from input file stream.
     * 
     * @param is: input file stream
     */
    void add(istream &is);
    /**
     * @brief   Convert a line to a pair of page number and text,
     *          then push this pair to navigation vector field.
     * 
     * @param line: navigation string.
     */
    void storeNavi(const string &line);
    /**
     * @brief   Get all the page number where this page can refer to and store to a vector
     * 
     * @return page number vector. 
     */
    vector<size_t> naviForPageNum();
    /**
     * @brief   Get a particular page number where this page can refer to,
     *          (choice)th page in navigation field.
     * 
     * @param choice: (choice)th page in navigation
     * @return the page number. 
     */
    size_t naviForPageNum(const size_t &choice);
    /**
     * @brief   Get the status of this page
     * 
     * @return the status of this page 
     */
    size_t getStatus();
    /**
     * @brief   Get the number of page that this page can refer to.
     * 
     * @return  the number of page 
     */
    size_t getNaviReferNum();
    /**
     * @brief   Construct a new Page object with undefined status
     */
    Page() : status(UNDEF_STAT){};
};
/**
 * @brief Story class:
 *          A story is made up of many pages, this class contains
 *          some essential information of a story.
 * @field Pages:
 *          A Page vector stores all the loaded pages in a story.
 * @field reachablePages:
 *          a set of number indicates all the reachable pages in this story.
 */
class Story {
    vector<Page> Pages;
public:

    /**
     * @brief   First check whether a page is valid, if valid add the page
     *          into story.
     * 
     * @param P: a const reference to a page.
     */
    void addPage(const Page &P);

    /**
     * @brief   Get the number of page inside a story.
     * 
     * @return the number of page. 
     */
    size_t getPageSize();

    /**
     * @brief   Check whether all pages in this Story are referenced, if 
     *          any error happened, exit with failure.
     */
    void allPageReferenced();

    /**
     * @brief   Start to read the pages in this Story, user can make a choice
     *          to get different results.
     */
    void readStory();

    /**
     * @brief   Using DFS recursively find the minimum depth of all reachable pages 
     *          inside this story and store in PageDepth vector. 
     * 
     * @param PageNum indicates current page number.
     * @param PageDepth a vector to store all the depth information, the depth of
     *                  unreferenced page will be -1
     * @param currDepth indicates the depth of current page.
     */
    void getPageDepth(size_t PageNum, vector<int> &PageDepth, int currDepth);
    
    /**
     * @brief   print out the minimum page depth of all reachable pages inside Story,
     *          if unreachable, print corresponding information into cout.
     */
    void printPageDepth(vector<int> PageDepth);

    /**
     * @brief   Using DFS recursively find all the win route of Story and store 
     *          into allWinPath set, method will return if it finds a WIN/LOSE page or
     *          no page can navigate to.
     * 
     * @param pageNum indicates current page number.
     * @param currentPath a Path object indicates current path.
     * @param allWinPath a set to store all the win path.
     */
    void findWinRoute(size_t pageNum, Path currentPath, set<Path> &allWinPath);

    /**
     * @brief   print out all the win path into cin
     * 
     * @param allWinPath a const reference to a set, which stores all the win path.
     */
    void printWinRoute(const set<Path> &allWinPath);
};

/*
 *@AreDigits function is used to check whether all the elements in a string are digits.
 *@param digits: A const reference to string.
 *@return bool.
*/
bool AreDigits(const string &digits);

/*
 *@getPageName function is used to get page name in a dictionary.
 *@param dictName: A const reference to string.
 *@param count: A unsigned page counter. 
 *@return string.
*/
string getPageName(const string &dictName, size_t count);

/*
 *@rntFail function is used to get page name in a dictionary.
 *@param dictName: A const reference to string.
 *@param count: A unsigned page counter. 
 *@return EXIT_FAILURE.
*/
int rntFail(const string &str);
int rntFail(const string &str, const string &str2);

void errorHandler(int errorType);
#endif