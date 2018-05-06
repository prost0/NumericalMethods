#ifndef __LUP__
#define __LUP__

#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>
#include "matrix.hpp"
#include "vector.hpp"


using namespace std;

int m_detSign = 1;

void m_frontSub(Matrix &mat, vector <double> &vec, vector <double> &vecP, vector <double> &vecZ)
{
    int n = mat.getSize();
    
    for (int i = 0; i < n; ++i) {
        double sum = 0.0;
        
        for (int j = 0; j < i; ++j) {
            sum += mat.get(i, j) * vecZ[j];
        }
        
        vecZ[i] = vec[(int)vecP[i]] - sum;
    }
}


void m_backSub(Matrix &mat, vector <double> &vec, vector <double> &vecX)
{
    int n = mat.getSize();
    
    for (int i = n - 1; i >= 0; --i) {
        double sum = 0.0;
        
        for (int j = i + 1; j < n; ++j) {
            sum += mat.get(i, j) * vecX[j];
        }
        vecX[i] = (vec[i] - sum) / mat.get(i, i);
    }
}


bool m_lup(Matrix &mat, Matrix &matL, Matrix &matU, vector <double> &vecP)
{
    int n = mat.getSize();
    
    m_detSign = 1;
    matU.copy(mat);
    
    for (int i = 0; i < n; ++i) {
        vecP[i] = i;
    }
    
    for (int j = 0; j < n; ++j) {
        int row = -1;
        double max = 0.0;
        
        for (int i = j; i < n; ++i) {
            double element = abs(matU.get(i, j));
            
            if (element > max) {
                max = element;
                row = i;
            }
        }
        
        if (row == -1) {
            return false;
        }
        
        if (row != j) {
            m_detSign *= -1;
        }
        
        matU.swapRows(j, row);
        matL.swapRows(j, row);
        matL.set(j, j, 1);
        
        swap(vecP[j], vecP[row]);
        
        for (int i = j + 1; i < n; ++i) {
            double ratio = matU.get(i, j) / matU.get(j, j);
            
            for (int k = j; k < n; ++k) {
                matU.set(i, k, matU.get(i, k) - matU.get(j, k) * ratio);
            }
            
            matL.set(i, j, ratio);
        }
    }
    
    return true;
}



void matInverse(Matrix &mat, Matrix &matInv)
{
    int n = mat.getSize();
    vector <double> vec1(n);
    vector <double> vec2(n);
    vector <double> vecP(n);
    vector <double> vecX(n);
    Matrix matL(n);
    Matrix matU(n);
    Matrix matE(n);
    
    m_lup(mat, matL, matU, vecP);
    matE.identity();
    
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            vec1[i] = matE.get(i, j);
        }
        
        m_frontSub(matL, vec1, vecP, vec2);
        m_backSub(matU, vec2, vecX);
        
        for (int i = 0; i < n; ++i) {
            matInv.set(i, j, vecX[i]);
        }
    }
}

double matDet(Matrix &mat)
{
    int n = mat.getSize();
    double res = 1.0;
    Matrix matL(n);
    Matrix matU(n);
    vector <double> vecP(n);
    
    m_lup(mat, matL, matU, vecP);
    
    for (int i = 0; i < n; ++i) {
        res *= matU.get(i, i);
    }
    
    return res * m_detSign;
}



bool lup(Matrix &mat, vector <double> &vec, vector <double> &vecX)
{
    int n = mat.getSize();
    Matrix matL(n);
    Matrix matU(n);
    vector <double> vecP(n);
    vector <double> vecZ(n);
    
    if (!m_lup(mat, matL, matU, vecP)) {
        return false;
    }
    
    m_frontSub(matL, vec, vecP, vecZ);
    m_backSub(matU, vecZ, vecX);
    
    return true;
}


void method1()
{
    ifstream fin("../data/in1.txt");
    ofstream fout("../data/out1.txt");
    int n, tmp;
    
    
    fin >> n;//int n;
    Matrix mat(n, n);
    vector <double> vec(n);
    vector <double> vecX(n);
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fin >> tmp;
            mat.set(i, j, tmp);
        }
    }
    
    for (int i = 0; i < n; ++i) {
        fin >> vec[i];
    }
    
    Matrix matInv(n);
    
    if (!lup(mat, vec, vecX)) {
        fout << "Degenerate matrix\n";
    } else {
        matInverse(mat, matInv);
        
        fout << "Answer (vector):\n";
        for (int i = 0; i < n; ++i) {
            fout << vecX[i] << " ";
        }
        fout << "\nInverse matrix:\n";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                fout << matInv.get(i, j) << " ";
            }
            fout << "\n";
        }
        fout << "Determinant: " << matDet(mat) << "\n";
    }
}

#endif