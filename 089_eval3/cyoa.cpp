#include "cyoa.hpp"


void Story::addPage(const Page & P){
    Pages.push_back(P);
}

size_t Story::getPageSize(){
    return Pages.size();
}

void Story::allPageReferenced(){
    size_t pageSize=getPageSize();
    //a vector to store whether all pages are referenced.
    vector<bool> isReferenced(pageSize,false);
    isReferenced[0]=true;
    bool containWinPage=false;
    bool containLosePage=false;
    for(auto it_page=Pages.begin();it_page!=Pages.end();++it_page){
        if(it_page->getStatus()==WIN_STAT){
            containWinPage=true;
        }
        else if(it_page->getStatus()==LOSE_STAT){
            containLosePage=true;
        }
        else{
            //get page number from navigation field of Page.
            vector<size_t> PageIndexs=it_page->naviForPageNum();
            for(auto it_navi=PageIndexs.begin();it_navi!=PageIndexs.end();++it_navi){
                //navigate to non-exist page.
                if(*it_navi>pageSize){
                    errorHandler(INVALID_REFERENCE_PAGE_NUMBER);
                }
                isReferenced[*it_navi-1]=true;
            }
        }
    }
    //check all pages are referenced & check WIN LOSE pages
    if(containLosePage==true&&containWinPage==true){
        for(auto it=isReferenced.begin();it!=isReferenced.end();++it){
            if(*it==false){
                errorHandler(EXIST_UNREFERENCED_PAGE);
            }
        }
        return ;
    }
    errorHandler(NO_WIN_LOSE_PAGE);
}

void Story::readStory(){
    auto it=Pages.begin();
    while(it->getStatus()!=WIN_STAT&&it->getStatus()!=LOSE_STAT){
        //get number of page can refer to in the navigation field.
        size_t naviSize=it->getNaviReferNum();
        it->printPage();
        string line;
        while(getline(cin,line)){
            //check cin until user input  a valid reference
            if(AreDigits(line)){
                size_t choice=stoi(line);
                if(choice>naviSize||choice<=0){
                    cout<<"That is not a valid choice, please try again"<<endl;
                    continue;
                }
                else{
                    size_t pageNum=it->naviForPageNum(choice);
                    it=Pages.begin()+pageNum-1;
                }
                break;
            }
            else{
                    cout<<"That is not a valid choice, please try again"<<endl;
                    continue;
            }
        }
        if(cin.eof()){
            errorHandler(INVALID_STORY_TERMINATATION);
        }
    }
    if(it->getStatus()==WIN_STAT||it->getStatus()==LOSE_STAT){
        it->printPage();
        return;
    }
}

void Story::getPageDepth(size_t PageNum, vector<int> & PageDepth,int currDepth){
    //refer to current page.
    currDepth++;
    auto it_Page=Pages.begin()+PageNum-1;
    //base case: reach WIN/LOSE page or no way to refer to.
    if(it_Page->getStatus()==WIN_STAT||
        it_Page->getStatus()==LOSE_STAT||it_Page->getNaviReferNum()==0){
        PageDepth[PageNum-1]=currDepth;
        return;
    }
    PageDepth[PageNum-1]=currDepth;
    //iterate through all the Paths this page can navigate to
    //if the page has not been navigated or its a shorter path.
    for(size_t i=1;i<=it_Page->getNaviReferNum();i++){
            size_t nextPageNum=it_Page->naviForPageNum(i);
            int nextPageDepth=PageDepth[nextPageNum-1];
            if((nextPageDepth==UNDEF_DEPTH)||
                (currDepth<nextPageDepth)){
                getPageDepth(nextPageNum,PageDepth,currDepth);
            }
    }
}

void Story::printPageDepth(vector<int> PageDepth){
    int counter=1;
    for(auto it=PageDepth.begin();it!=PageDepth.end();++it){
        if(*it==UNDEF_DEPTH){
            cout<<"Page "<<counter<<" is not reachable"<<endl;
        }
        else{
            cout<<"Page "<<counter<<":"<<*it<<endl;
        }
        counter++;
    }
}

void Story::findWinRoute(size_t pageNum, Path currentPath,set<Path>  & allWinPath){
    auto it_page=Pages.begin()+pageNum-1;
    //base case: find a WIN/LOSE page or no way to navigate.
    if(it_page->getStatus()==WIN_STAT){
        currentPath.push_back(pageNum,0);
        allWinPath.insert(currentPath);
        return;
    }
    else if(it_page->getStatus()==LOSE_STAT||it_page->getNaviReferNum()==0){
        return;
    }
    //navigate all the pages in the navigation field of a page if no loop happens.
    for(size_t i=1;i<=it_page->getNaviReferNum();i++){
        size_t nextPageNum=it_page->naviForPageNum(i);
        // loop happens.
        if(currentPath.find(nextPageNum)||nextPageNum==pageNum){
            continue;
        }
        currentPath.push_back(pageNum,i);
        findWinRoute(nextPageNum,currentPath,allWinPath);
        currentPath.pop_back();
    }
}

void Story::printWinRoute(const set<Path> &allWinPath) {
    if(allWinPath.size()==0){
        cout<<"This story is unwinnable!"<<endl;
    }
    for(auto it=allWinPath.begin();it!=allWinPath.end();++it){
        it->printPath();
    }
}

void Page::add(istream & is){
    string line;
    // define status of a page.
    if(getline(is,line)){
        if(line=="WIN"){
            status=WIN_STAT;
        }
        else if (line=="LOSE"){
            status=LOSE_STAT;
        }
        else {
            status=NAV_STAT;
            storeNavi(line);
        }
    }
    //the next line of a WIN/LOSE page need to start with '#'
    if(status==WIN_STAT||status==LOSE_STAT){
        if(getline(is,line)){
            if(line[0]!='#'){
                errorHandler(INVALID_PAGE_FORMAT);
            }
        }
        while(getline(is,line)){
            text.push_back(line);
        }
    }
    else if(status==NAV_STAT){
        bool containNumSign=false;
        while(getline(is,line)){
            if(line[0]=='#'){
                containNumSign=true;
                break;
            }
            storeNavi(line);
        }
        //No # in a page
        if(containNumSign==false){
            errorHandler(INVALID_PAGE_FORMAT);       
        }
        while(getline(is,line)){
            text.push_back(line);
        }
    }
    else{
        errorHandler(INVALID_PAGE_FORMAT_EMPTY_PAGE);       
    }
    return ;
}

void Page::storeNavi(const string & line){
    size_t found=line.find(':');
    //check valid lines, then store to navigation field.
    if(found!=string::npos){    
        string digits=line.substr(0,found);
        if(AreDigits(digits)){  
            size_t pageIndex=(size_t)stoi(digits);
            navigation.push_back({pageIndex,line.substr(found+1)});
        }
        else{
            errorHandler(INVALID_NAVIGATION_FORMAT);       
        }
    }
    else{
        errorHandler(INVALID_NAVIGATION_FORMAT); 
    }
    return;
}

vector<size_t> Page::naviForPageNum(){
    vector<size_t> PageIndexs;
    for(auto it=navigation.begin();it!=navigation.end();++it){
        PageIndexs.push_back(it->first);
    }
    return PageIndexs;
}

size_t Page::naviForPageNum(const size_t & choice){
    return navigation[choice-1].first;
}

size_t Page::getStatus(){
    return status;
}
size_t Page::getNaviReferNum(){
    return navigation.size();
}

void Page::printPage(){
    for(auto it=text.begin();it!=text.end();++it){
        cout<<*it<<endl;
    }
    cout<<endl;
    switch(status){
        case WIN_STAT: 
            cout<<"Congratulations! You have won. Hooray!"<<endl;
            break;
        case LOSE_STAT:
            cout<<"Sorry, you have lost. Better luck next time!"<<endl;
            break;
        case NAV_STAT:
            cout<<"What would you like to do?"<<endl<<endl;
            size_t count=1;
            for(auto it=navigation.begin();it!=navigation.end();++it){
	      cout<<" "<<count<<". "<<it->second<<endl;
                count++;
            }

    }
}

void Path::push_back(size_t pageNum,size_t choice){
    path.push_back({pageNum,choice});
}

bool Path::find(size_t pageNum){
    for(auto it=path.begin(); it!=path.end();++it){
        if(it->first==pageNum){
            return true;
        }
    }
    return false;
}

void Path::printPath() const {
    for(auto it=path.begin();it!=path.end();++it){
        if(it==path.begin()){
            cout<<it->first<<"("<<it->second<<")";
            continue;
        }
        cout<<","<<it->first<<"(";
        it->second==0   ?  cout<<"win"  :   cout<<it->second;
        cout<<")";
    }
    cout<<endl;
}

vector<pair<size_t,size_t> > Path::getPath() {
    return path;
}

bool Path::operator<(const Path & rhs) const  {
    return true;
}

void Path::pop_back(){
    path.erase(path.end()-1);
    return;
}

string getPageName(const string & dictName,size_t count){
    return dictName+"/page"+to_string(count)+".txt";
}

int rntFail(const string & str,const string & str2){
    cerr<<str<<str2<<endl;
    return EXIT_FAILURE;
}

int rntFail(const string & str){
    cerr<<str<<endl;
    return EXIT_FAILURE;
}
void errorHandler(int errorType){
    /*
    INVALID_REFERENCE_PAGE_NUMBER,
    EXIST_UNREFERENCED_PAGE,
    NO_WIN_LOSE_PAGE,
    INVALID_NAVIGATION_FORMAT,
    INVALID_STORY_TERMINATATION,
    INVALID_PAGE_FORMAT_EMPTY_PAGE
    */
    switch (errorType){
        case INVALID_REFERENCE_PAGE_NUMBER:
            cerr<<"Navigate to non-exist page !"<<endl;
            break;
        case EXIST_UNREFERENCED_PAGE:
            cerr<<"Exist unreferenced page !"<<endl;
            break;
        case NO_WIN_LOSE_PAGE:
            cerr<<"Story lack WIN or LOSE page!"<<endl;
            break;
        case INVALID_NAVIGATION_FORMAT:
            cerr<<"Invalid navigation format!"<<endl;
            break;
        case INVALID_STORY_TERMINATATION:
            cerr<<"cin reaches EOF while story has not finished!"<<endl;
            break;
        case INVALID_PAGE_FORMAT_EMPTY_PAGE:
            cerr<<"Exist empty page!"<<endl;
            break;
        case INVALID_PAGE_FORMAT:
            cerr<<"Invalid page format!"<<endl;
            break;
        case INVALID_ARGUMENT_FORMAT_CYOA1:
            cerr<<"Usage: Pagefile"<<endl;
            break;
        case INVALID_ARGUMENT_FORMAT_CYOA2:
            cerr<<"Usage: Pagefile"<<endl;
            break;
        case INVALID_ARGUMENT_FORMAT_CYOA3:
            cerr<<"Usage: storyDirectory"<<endl;
            break;
        case INVALID_ARGUMENT_FORMAT_CYOA4:
            cerr<<"Usage: storyDirectory"<<endl;
            break;
        case EMPTY_STORY:
            cerr<<"No page in story!"<<endl;
            break;
        case OPEN_FILE_FAILURE:
            cerr<<"Cannot open file!"<<endl;
            break;
        case CLOSE_FILE_FAILURE:
            cerr<<"Cannot close file!"<<endl;
            break;
            
        default:
            break;
    }
    exit(EXIT_FAILURE);
}

bool AreDigits(const string & digits){
    if(digits.size()==0)
        return false;
    for(size_t i=0;i<digits.size();i++){
        //non digits return false
        if(digits[i]<'0'||digits[i]>'9'){
            return false;
        }
    }
    return true;
}