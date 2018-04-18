#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <fstream>
#include "matrix.hpp"

using namespace std;


Matrix::Matrix() {}

Matrix::Matrix(int size)
{
    m_mat.resize(size);
    for (int i = 0; i < size; i++) {
        m_mat[i].resize(size);
    }
}


Matrix::Matrix(int rows, int cols)
{
    m_mat.resize(rows);
    for (int i = 0; i < cols; i++) {
        m_mat[i].resize(cols);
    }
}


void Matrix::resize(int rows, int cols)
{
    m_mat.resize(rows);
    for (int i = 0; i < cols; i++) {
        m_mat[i].resize(cols);
    }
}

double Matrix::get(int row, int col)
{
    return m_mat[row][col];
}

void Matrix::set(int row, int col, double value)
{
    m_mat[row][col] = value;
}

int Matrix::getSize()
{
    return m_mat.size();
}

int Matrix::getM()
{
    return getSize();
}

int Matrix::getN()
{
    return m_mat[0].size();
}

Matrix Matrix::sub(Matrix other)
{
    int n = getSize();
    Matrix res(n);
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            res.set(i, j, get(i, j) - other.get(i, j));
        }
    }
    
    return res;
}

Matrix Matrix::mul(double value)
{
    int n = getSize();
    Matrix res(n);
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            res.set(i, j, get(i, j) * value);
        }
    }
    
    return res;
}

Matrix Matrix::mul(Matrix other)
{
    int n = getSize();
    Matrix res(n);
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double sum = 0.0;
            
            for (int k = 0; k < n; ++k) {
                sum += get(i, k) * other.get(k, j);
            }
            
            res.set(i, j, sum);
        }
    }
    
    return res;
}

vector <double> Matrix::mul(vector <double> other)
{
    int n = getSize();
    vector <double> res(n);
    
    for (int i = 0; i < n; ++i) {
        double sum = 0.0;
        
        for (int j = 0; j < n; ++j) {
            sum += get(i, j) * other[j];
        }
        
        res[i] = sum;
    }
    
    return res;
}

Matrix Matrix::transpose()
{
    int n = getSize();
    Matrix res(n);
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            res.set(i, j, get(j, i));
        }
    }
    
    return res;
}

void Matrix::identity()
{
    int n = getSize();
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                set(i, j, 1.0);
            } else {
                set(i, j, 0.0);
            }
        }
    }
}

void Matrix::copy(Matrix other)
{
    for (int i = 0; i < getM(); ++i) {
        for (int j = 0; j < getN(); ++j) {
            set(i, j, other.get(i, j));
        }
    }
}

void Matrix::swapRows(int index1, int index2)
{
    swap(m_mat[index1], m_mat[index2]);
    //double tmp = m_mat[index1];
    
    //m_mat[index1] = m_mat[index2];
    //m_mat[index2] = tmp;
}

string Matrix::toString()
{
    // string res = Arrays.toString(m_mat[0]);
    
    // for (int i = 1; i < getM(); ++i) {
    //     res += '\n' + Arrays.toString(m_mat[i]);
    // }
    string res = "To string doesnt work\n";
    return res;
}



ifstream &operator >> (ifstream &ifstr,  Matrix &m)
{
    for (int i = 0; i < m.m_mat.size(); ++i) {
        for (int j = 0; j < m.m_mat[0].size(); ++j) {
            ifstr >> m.m_mat[i][j];
        }
    }
    return ifstr;
}

ofstream &operator << (ofstream &ofstr,  Matrix &m)
{
    for (int i = 0; i < m.m_mat.size(); ++i) {
        for (int j = 0; j < m.m_mat[0].size(); ++j) {
            ofstr.width(10);
            ofstr << m.get(i, j) << " ";
        }
        ofstr << "\n";
    }
    return ofstr;
}