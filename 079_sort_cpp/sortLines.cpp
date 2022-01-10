#include <iostream>
#include <istream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cstdlib>

void doSort(std::istream & is)
{
  std::vector<std::string> strs;
  std::string line;
  while(getline(is,line)){
    strs.push_back(line);
  }
  if (!is.eof()) {
    std::cerr << "failed to read file" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::sort(strs.begin(),strs.end());
  std::vector<std::string>::iterator it=strs.begin();
  while(it!=strs.end()){
    std::cout<<*it<<std::endl;
    ++it;
  }
}

int main(int argc, char **argv)
{
  if(argc<=0){
    std::cout<<"Usage: fileNames "<<std::endl;
    exit(EXIT_FAILURE);
  }
  if(argc==1){
    doSort(std::cin);
  }
  else{
    for(int i=1;i<argc;i++){
      std::ifstream iFile(argv[i]);
      if (!iFile) {
        std::cerr << "failed to open " << argv[i] << std::endl;
        exit(EXIT_FAILURE);
      }
      doSort(iFile);
    }
  }
  return 0;
}
