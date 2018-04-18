#ifndef __method_3_1__
#define __method_3_1__

#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>
#include "method3_2.hpp"

using namespace std;

bool simpleIteration(Matrix &mat, vector <double> &vec, vector <double> &vecX, double &eps, int &cnt)
{
    int n = mat.getSize();
    Matrix matA(n);
    vector <double> vecB(n);
    vector <double> vecPrev(n);
    int iterCnt = 1;
    
    vecB = vec;
    
    for (int j = 0; j < n; ++j) {
        if (mat.get(j, j) == 0) {
            int rowForSwap = -1;
            for (int i = 0; i < n; ++i) {
                if (j != i) {
                    if (mat.get(i, j) != 0 && mat.get(j, i) != 0) {
                        rowForSwap = i;
                        break;
                    }
                }
            }
            if (rowForSwap == -1) {
                return false;
            }
            mat.swapRows(j, rowForSwap);
        }
    }
    
    
    for (int i = 0; i < n; ++i) {
    
        if (mat.get(i, i) == 0) {
        
            return false;
        }
        
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                matA.set(i, j, -mat.get(i, j) / mat.get(i, i));
            } else {
                matA.set(i, j, 0);
            }
        }
        
        vecB[i] = vecB[i] / mat.get(i, i);
    }
    
    vecPrev = vecB;
    
    while (true) {
        vecX = matA.mul(vecPrev);//
        for (int i = 0; i < vecB.size(); ++i) {
            vecX[i] += vecB[i];//
        }
        
        // if (m_logger != Complex(0.0, 0.0)) {
        //     m_logger.writeln("Итерация #" + iterCnt + ": " + vecX);
        // }
        double normC = 0;
        for (int i = 0; i < n; ++i) {
            normC = max(normC, abs(vecX[i] - vecPrev[i]));//
        }
        if (normC <= eps) {
            break;
        }
        
        vecPrev = vecX;
        ++iterCnt;
        
        if (iterCnt > MAX_ITERATIONS) {
            return false;
        }
    }
    cnt = iterCnt;
    return true;
}


void method3_1()
{
    ifstream fin("../data/in3_1.txt");
    ofstream fout("../data/out3_1.txt");
    
    int n;
    double eps;
    fin >> n >> eps;
    Matrix mat(n);
    fin >> mat;
    vector <double> vec(n);
    inputVec(vec, fin);
    vector <double> vecX(n);
    
    fout << "Метод 3: Метод простых итераций\n";
    fout << "Исходная матрица:\n";
    fout << mat;
    fout << "Исходный вектор:\n";
    printVec(vec, fout);
    int cnt = 0;
    
    if (!simpleIteration(mat, vec, vecX, eps, cnt)) {
        fout << "Превышен лимит итераций\n";
        return;
    }
    
    fout << "Решение:\n";
    printVec(vecX, fout);
    fout << "Количество интераций " << cnt;
}

#endif