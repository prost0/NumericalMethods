#ifndef __matrix__
#define __matrix__

#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <fstream>

using namespace std;


class Matrix
{
public:

    friend ofstream &operator<<(ofstream &ofstr,  Matrix &m);
    friend ifstream &operator>>(ifstream &ifstr,  Matrix &m);
    Matrix();
    Matrix(int size);
    Matrix(int rows, int cols);
    void resize(int rows, int cols);
    double get(int row, int col);
    void set(int row, int col, double value);
    int getSize();
    int getM();
    int getN();
    Matrix sub(Matrix other);
    Matrix mul(double value);
    Matrix mul(Matrix other);
    vector <double> mul(vector <double> other);
    Matrix transpose();
    void identity();
    void copy(Matrix other);
    void swapRows(int index1, int index2);
    string toString();
    
private:
    vector < vector<double> > m_mat;
};

#endif