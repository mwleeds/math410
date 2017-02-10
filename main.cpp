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
    if (argc != 3) {
        cerr << "Usage: ./math410 <filename1> <filename2>" << endl;
        return 1;
    }

    const char* filename1 = argv[1];
    const char* filename2 = argv[2];
    ifstream inFile1(filename1);
    if (!inFile1.is_open()) {
        cerr << "Error: File '" << filename1 << "' not found or inaccessible." << endl;
        return 2;
    }
    ifstream inFile2(filename2);
    if (!inFile2.is_open()) {
        cerr << "Error: File '" << filename2 << "' not found or inaccessible." << endl;
        return 3;
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

    inFile2 >> line1;
    num_rows = atoi(line1.c_str());
    inFile2 >> line2;
    num_cols = atoi(line2.c_str());
    Matrix* matrix2 = new Matrix(inFile2, num_rows, num_cols);
    inFile2.close();

    Matrix* product = *matrix1 * *matrix2;
    cout << *product << endl;

    delete product;
    delete matrix1;
    delete matrix2;
    return 0;
}
