#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <Array.h>

//YOUR CODE GOES HERE
template<typename T>
class Matrix {
 private:
  T numRows;
  T numColumns;
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
  friend std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs);

};
