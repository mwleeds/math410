// File: main.cpp
// Author: Matthew Leeds
// Purpose: Perform various operations on matrices
// Usage: $ ./math410 <filename1> <filename2>
// where the files' first two lines specify the number of rows and columns
// and the rest are comma delimited values

#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <fstream>
#include <tuple>
#include "Matrix.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./math410 <filename>" << endl;
        return 1;
    }

    const char* filename1 = argv[1];
    ifstream inFile1(filename1);
    if (!inFile1.is_open()) {
        cerr << "Error: File '" << filename1 << "' not found or inaccessible." << endl;
        return 2;
    }

    // Assume the data file is formatted correctly.
    string line1;
    inFile1 >> line1;
    int num_rows = atoi(line1.c_str());
    string line2;
    inFile1 >> line2;
    int num_cols = atoi(line2.c_str());
    Matrix* matrix1 = new Matrix(inFile1, num_rows, num_cols);
    inFile1.close();

    cout << "A:" << endl << *matrix1 << endl;
    tuple<Matrix*, Matrix*, Matrix*> plu = matrix1->GEpivot();
    Matrix* P = get<0>(plu);
    Matrix* L = get<1>(plu);
    Matrix* U = get<2>(plu);
    cout << "P:" << endl << *P << endl;
    cout << "L:" << endl << *L << endl;
    cout << "U:" << endl << *U << endl;

    delete P;
    delete L;
    delete U;
    delete matrix1;
    return 0;
}
