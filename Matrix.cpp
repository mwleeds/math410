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

// This constructor allocates space for the matrix
// and optionally makes it the identity matrix
Matrix::Matrix(int rows, int cols, bool identity) {
    this->_rows = rows;
    this->_cols = cols;
    this->_matrix = new float*[this->_rows];
    for (int i = 0; i < this->_rows; i++) {
        this->_matrix[i] = new float[this->_cols];
        if (identity) {
            for (int j = 0; j < this->_cols; j++)
                this->_matrix[i][j] = (i == j ? 1 : 0);
        }
    }
}

// This constructor allocates space and fills the matrix with values from a file.
// It is assumed that the file is formatted correctly, and that the
// ifstream object is seeked to the right position before being passed to this.
Matrix::Matrix(ifstream& inFile, int rows, int cols) {
    this->_rows = rows;
    this->_cols = cols;
    this->_matrix = new float*[this->_rows];
    for (int i = 0; i < this->_rows; i++) {
        this->_matrix[i] = new float[this->_cols];
    }
    // For each line, interpret everything but commas as integers
    for (int i = 0; i < this->_rows; i++) {
        string line = "";
        inFile >> line;
        stringstream ss(line);
        int j = 0;
        float num;
        while (ss >> num) {
            this->_matrix[i][j] = num;
            j++;
            if (ss.peek() == ',') {
                ss.ignore();
            }
        }
    }
}

void swap(Matrix& first, Matrix& second) {
    swap(first._rows, second._rows);
    swap(first._cols, second._cols);
    swap(first._matrix, second._matrix);
}

Matrix& Matrix::operator=(Matrix other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

Matrix::Matrix(const Matrix &m) {
    this->_rows = m._rows;
    this->_cols = m._cols;
    this->_matrix = new float*[this->_rows];
    for (int i = 0; i < this->_rows; i++) {
        this->_matrix[i] = new float[this->_cols];
        for (int j = 0; j < this->_cols; j++) {
            this->_matrix[i][j] = m._matrix[i][j];
        }
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < this->_rows; i++) {
        delete []this->_matrix[i];
    }
    delete []this->_matrix;
}

// Find the maximum width of the string representations of the values in the
// matrix. This can be useful for determining how wide to make columns when
// printing it out.
int Matrix::findMaxWidth() const{
    int maxWidth = 0;
    for (int i = 0; i < this->_rows; i++) {
        for (int j = 0; j < this->_cols; j++) {
            string valString;
            ostringstream convert;
            convert << this->_matrix[i][j];
            valString = convert.str();
            if (valString.size() > maxWidth)
                maxWidth = valString.size();
        }
    }
    return maxWidth;
}

// This overloads the redirection operator so matrices can be printed using cout.
// Values are printed in fixed-width columns, right-aligned.
ostream& operator<<(ostream& os, const Matrix& m) {
    int maxWidth = m.findMaxWidth();
    int extraSpace = 2;
    int fieldWidth = extraSpace + maxWidth;
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
  Matrix* product = new Matrix (m1._rows, m2._cols, false);
  for (int i = 0; i < m2._cols; i++) {
      for (int j = 0; j < m1._rows; j++) {
          float sum = 0;
          for (int k = 0; k < m1._cols; k++) {
              sum += m1._matrix[j][k] * m2._matrix[k][i];
          }
          product->_matrix[j][i] = sum;
      }
  }
  return product;
}

// This implements Gaussian Elimination with partial (row) pivoting.
// P is the permutation matrix, L is lower-triangular and U is upper-triangular,
// with the property that PA = LU where A is this matrix.
tuple<Matrix*, Matrix*, Matrix*> Matrix::GEpivot() {
    Matrix* P = new Matrix(this->_rows, this->_cols, true);
    Matrix* L = new Matrix(this->_rows, this->_cols, true);
    Matrix* U = new Matrix(*this);
    tuple<Matrix*, Matrix*, Matrix*> t = make_tuple(P, L, U);
    if (this->_rows != this->_cols) {
        cerr << "GEpivot only implemented for square matrices, quitting" << endl;
        return t;
    }
    for (int i = 0; i < this->_cols - 1; i++) {
        // Find row with largest value
        int max_row = i;
        for (int j = i; j < this->_rows; j++) {
            if (abs(U->_matrix[j][i]) > abs(U->_matrix[max_row][i]))
                max_row = j;
        }
        if (max_row != i) {
            // Swap max_row and row i in all 3 matrices
            swap(U->_matrix[i], U->_matrix[max_row]);
            for (int k = 0; k < i; k++)
                swap(L->_matrix[i][k], L->_matrix[max_row][k]);
            swap(P->_matrix[i], P->_matrix[max_row]);
        }

        // Do the row operation that will zero out this column
        for (int l = i + 1; l < this->_cols; l++) {
            L->_matrix[l][i] = U->_matrix[l][i] / U->_matrix[i][i];
            for (int m = i; m < this->_cols; m++)
                U->_matrix[l][m] = U->_matrix[l][m] - (L->_matrix[l][i] * U->_matrix[i][m]);
        }
    }
    return t;
}
