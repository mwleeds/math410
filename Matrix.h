// File: Matrix.h
// Author: Matthew Leeds

#include <string>
#include <fstream>

using namespace std;

class Matrix {
    public:
        Matrix(int rows, int cols);
        Matrix(ifstream& inFile, int rows, int cols);
        ~Matrix();
        int findMaxMagnitude() const;
        friend ostream& operator<<(ostream& os, const Matrix& m);
        friend Matrix* operator*(const Matrix& m1, const Matrix& m2);
        int** _matrix;
        int _rows;
        int _cols;
};
