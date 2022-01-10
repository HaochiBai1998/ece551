#include"cyoa.hpp"

int main(int argc, char ** argv){    
    if(argc!=2){
        errorHandler(INVALID_ARGUMENT_FORMAT_CYOA1);
    }
    filebuf page;  
    if(!page.open(argv[1],ios::in)){
        errorHandler(OPEN_FILE_FAILURE);
    }
    istream is(&page);
    Page P;
    P.add(is);
    P.printPage();
    if(page.close()==NULL){
        errorHandler(CLOSE_FILE_FAILURE);
    }
    return EXIT_SUCCESS;
}
