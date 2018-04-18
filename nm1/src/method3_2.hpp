#ifndef __method_3_2__
#define __method_3_2__

#include <vector>
#include <cmath>
#include <fstream>
#include "method4.hpp"

using namespace std;

bool seidel(Matrix &mat, vector <double> &vec, vector <double> &vecX, double &eps, int &cnt)
{
    int n = mat.getSize();
    Matrix matA(n);
    Matrix matB(n);
    Matrix matC(n);
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
            }
        }
        
        vecB[i] = vecB[i] / mat.get(i, i);
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j < i) {
                matB.set(i, j, matA.get(i, j));
            } else {
                matC.set(i, j, matA.get(i, j));
            }
        }
    }
    
    vecPrev = vecB;
    
    while (true) {
        vecX = vecAdd(matB.mul(vecX), vecAdd(matC.mul(vecPrev), vecB));
        
        if (vecNormC(vecSub(vecX, vecPrev)) <= eps) {
            cnt = iterCnt;
            return true;
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



void method3_2()
{
    ifstream fin("../data/in3_2.txt");
    ofstream fout("../data/out3_2.txt");
    int n;
    double eps;
    fin >> n >> eps;
    Matrix mat(n);
    fin >> mat;
    vector <double> vec(n);
    inputVec(vec, fin);
    vector <double> vecX(n);
    int cnt = 0;
    
    fout << "Метод 4: Метод Зейделя\n";
    fout << "Исходная матрица:\n";
    fout << mat;
    fout << "Исходный вектор:\n";
    printVec(vec, fout);
    
    seidel(mat, vec, vecX, eps, cnt);
    
    fout << "Решение:\n";
    printVec(vecX, fout);
    
    fout << "Количество интераций " << cnt;
}


#endif