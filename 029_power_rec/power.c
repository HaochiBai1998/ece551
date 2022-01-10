unsigned power(unsigned x,unsigned y){
  if (y!=0)
    return x*power(x,y-1);
  else
    return 1;
}
