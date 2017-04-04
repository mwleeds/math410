// File: Matrix.h
// Author: Matthew Leeds

#include <string>
#include <fstream>
#include <tuple>

using namespace std;

class Matrix {
    public:
        Matrix(int rows, int cols, bool identity);
        Matrix(ifstream& inFile, int rows, int cols);
        Matrix(const Matrix &m);
        ~Matrix();
        int findMaxWidth() const;
        Matrix& operator=(Matrix);
        friend void swap(Matrix& first, Matrix& second);
        friend ostream& operator<<(ostream& os, const Matrix& m);
        friend Matrix* operator*(const Matrix& m1, const Matrix& m2);
        tuple<Matrix*, Matrix*, Matrix*> GEpivot();
        Matrix* myChol();

        float** _matrix;
        int _rows;
        int _cols;
};
