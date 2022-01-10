#include "IntMatrix.h"
/*class IntMatrix {
 private:
  int numRows;
  int numColumns;
  IntArray ** rows;
 public:
  IntMatrix();
  IntMatrix(int r, int c);
  IntMatrix(const IntMatrix & rhs);
  ~IntMatrix();
  IntMatrix & operator=(const IntMatrix & rhs);
  int getRows() const;
  int getColumns() const;
  const IntArray & operator[](int index) const;
  IntArray & operator[](int index);
  bool operator==(const IntMatrix & rhs) const;
  IntMatrix operator+(const IntMatrix & rhs) const;


  };*/
IntMatrix::IntMatrix():numRows(0),numColumns(0),rows(NULL){  

}
IntMatrix::IntMatrix(int r, int c):numRows(r),numColumns(c) {
  rows=new IntArray * [numRows];
  for (int i=0;i<numRows;i++){
    rows[i]=new IntArray(numColumns);
  }
}
IntMatrix::IntMatrix(const IntMatrix & rhs)  {
  numRows=rhs.numRows;
  numColumns=rhs.numColumns;
  rows=new IntArray * [numRows];
  for (int i=0;i<numRows;i++){
    rows[i]=new IntArray(numColumns);
    *rows[i]=*rhs.rows[i];
  }
}
IntMatrix::~IntMatrix() {
  for (int i=0;i<numRows;i++){
    delete rows[i];
  }
  delete [] rows;
}
IntMatrix &IntMatrix::operator=(const IntMatrix & rhs) {
  if (this!=&rhs){
    for (int i=0;i<numRows;i++){
      delete rows[i];
    }
    delete [] rows;
    numRows=rhs.numRows;
    numColumns=rhs.numColumns;
    rows=new IntArray * [numRows];
    for (int i=0;i<numRows;i++){
      rows[i]=new IntArray(numColumns);
      *rows[i]=*rhs.rows[i];
    }
  }
  return *this;
}

int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert(index>=0&&index<numRows);
  return *rows[index];
}
IntArray & IntMatrix::operator[](int index){
  assert(index>=0&&index<numRows);
  return *rows[index];
}

/*bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (numRows!=rhs.numRows||numColumns!=rhs.numColumns)
    return false;
  for(int i=0;i<numRows;i++){
    if(*rows[i]!=*rhs.rows[i]){
      return false;
    }
  }
  return true;
  }*/


bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (numRows != rhs.numRows || numColumns != rhs.numColumns) {
    return false;
  }
  for (int i = 0; i < numRows; i++) {
    if (*(rows[i])!=*(rhs.rows[i])) {
      return false;
    }
  }
  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numRows==rhs.numRows&&numColumns==rhs.numColumns);
  IntMatrix temp(numRows,numColumns);
  for (int i=0;i<numRows;i++){
    for(int j=0;j<rhs.numColumns;j++){
      *temp.rows[i]=*rows[i]+*rhs.rows[i];
    }
  }
  return temp;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s<<"[ ";
  if(rhs.getRows()!=0)
    s<<rhs[0];
  for (int i=1;i<rhs.getRows();i++){
    s<<",\n";
    s<<rhs[i];
  }
  s<<" ]";
  return s;
}
