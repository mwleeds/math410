// File: Matrix.cpp
// Author: Matthew Leeds
// This class defines a matrix that can be used for multiplication/addition/subtraction.

#include "Matrix.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <cmath>

// This constructor allocates space for the matrix.
Matrix::Matrix(int rows, int cols) {
    this->_rows = rows;
    this->_cols = cols;
    this->_matrix = new int*[this->_rows];
    for (int i = 0; i < this->_rows; i++) {
        this->_matrix[i] = new int[this->_cols];
    }
}

// This constructor allocates space and fills the matrix with values from a file.
// It is assumed that the file is formatted correctly, and that the
// ifstream object is seeked to the right position before being passed to this.
Matrix::Matrix(ifstream& inFile, int rows, int cols) {
    this->_rows = rows;
    this->_cols = cols;
    this->_matrix = new int*[this->_rows];
    for (int i = 0; i < this->_rows; i++) {
        this->_matrix[i] = new int[this->_cols];
    }
    // For each line, interpret everything but commas as integers
    for (int i = 0; i < this->_rows; i++) {
        string line = "";
        inFile >> line;
        stringstream ss(line);
        int j = 0;
        int num;
        while (ss >> num) {
            this->_matrix[i][j] = num;
            j++;
            if (ss.peek() == ',') {
                ss.ignore();
            }
        }
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < this->_rows; i++) {
        delete []this->_matrix[i];
    }
    delete []this->_matrix;
}

// Find the maximum magnitude value in the matrix. This can be useful for
// determining how wide to make columns when printing it out.
int Matrix::findMaxMagnitude() const{
    int maxVal = 0;
    for (int i = 0; i < this->_rows; i++) {
        for (int j = 0; j < this->_cols; j++) {
            if (abs(this->_matrix[i][j]) > maxVal) {
                maxVal = abs(this->_matrix[i][j]);
            }
        }
    }
    return maxVal;
}

// This overloads the redirection operator so matrices can be printed using cout.
// Values are printed in fixed-width columns, right-aligned.
ostream& operator<<(ostream& os, const Matrix& m) {
    int maxVal = m.findMaxMagnitude();
    string maxValString;
    ostringstream convert;
    convert << maxVal;
    maxValString = convert.str();
    int extraSpace = 2;
    int fieldWidth = extraSpace + maxValString.size();
    for (int i = 0; i < m._rows; i++) {
        for (int j = 0; j < m._cols; j++) {
            os << right << setw(fieldWidth) << m._matrix[i][j];
        }
        os << endl;
    }
    return os;
}

// This overloads the multiplication operator
Matrix* operator*(const Matrix& m1, const Matrix& m2) {
  if (m1._cols != m2._rows) return NULL;
  Matrix* product = new Matrix (m1._rows, m2._cols);
  for (int i = 0; i < m2._cols; i++) {
      for (int j = 0; j < m1._rows; j++) {
          int sum = 0;
          for (int k = 0; k < m1._cols; k++) {
              sum += m1._matrix[j][k] * m2._matrix[k][i];
          }
          product->_matrix[j][i] = sum;
      }
  }
  return product;
}
