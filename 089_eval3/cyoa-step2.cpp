#include"cyoa.hpp"

int main(int argc, char ** argv){
    if(argc!=2){
        errorHandler(INVALID_ARGUMENT_FORMAT_CYOA2);
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
    size_t storyPageSize=story.getPageSize();
    if(storyPageSize==0){
        errorHandler(EMPTY_STORY);
    }

    story.allPageReferenced();
    story.readStory();
    return EXIT_SUCCESS;
}