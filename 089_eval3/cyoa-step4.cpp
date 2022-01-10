#include"cyoa.hpp"

int main(int argc, char ** argv){
    if(argc!=2){
        errorHandler(INVALID_ARGUMENT_FORMAT_CYOA4);
    }
    filebuf fb;    
    size_t count=1;
    string pageName=getPageName(argv[1],count);
    Story story;    
    while(fb.open(pageName,ios::in)){
        istream is(&fb);
        Page P;
        P.add(is);
        story.addPage(P);
        fb.close();
        count++;
        pageName=getPageName(argv[1],count);
    }
    size_t PagesSize=story.getPageSize();
    if(PagesSize==0){
        errorHandler(EMPTY_STORY);
    }
    story.allPageReferenced();
    set<Path> allWinPath;
    Path currPath;
    story.findWinRoute(1,currPath,allWinPath);
    story.printWinRoute(allWinPath);
    return EXIT_SUCCESS;
}
