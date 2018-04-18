#ifndef __method_4__
#define __method_4__

#include <vector>
#include <cmath>
#include <fstream>
#include "method5.hpp"

#define PI acos(-1.0)

using namespace std;

bool m_rotationCheck(Matrix &mat)
{
    int n = mat.getSize();
    
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (mat.get(i, j) != mat.get(j, i)) {
                return false;
            }
        }
    }
    
    return true;
}


bool rotation(Matrix &mat, Matrix &matX, vector <double> &vecX, double &eps, int &iterCnt)
{
    if (!m_rotationCheck(mat)) {
        return false;
    }
    
    int n = mat.getSize();
    Matrix matA(n);
    iterCnt = 1;
    
    matA.copy(mat);
    matX.identity();
    
    while (true) {
        double max = 0.0;
        int maxRow = -1;
        int maxCol = -1;
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i < j) {
                    double element = abs(matA.get(i, j));
                    
                    if (element > max) {
                        max = element;
                        maxRow = i;
                        maxCol = j;
                    }
                }
            }
        }
        
        double a1 = matA.get(maxRow, maxRow);
        double a2 = matA.get(maxCol, maxCol);
        double fiZero = PI / 4.0;
        
        if (a1 != a2) {
            fiZero = 0.5 * atan(2.0 * matA.get(maxRow, maxCol) / (a1 - a2));
        }
        
        double fiCos = cos(fiZero);
        double fiSin = sin(fiZero);
        Matrix matU(n);
        
        matU.identity();
        matU.set(maxRow, maxRow, fiCos);
        matU.set(maxRow, maxCol, -fiSin);
        matU.set(maxCol, maxRow, fiSin);
        matU.set(maxCol, maxCol, fiCos);
        
        matX.copy(matX.mul(matU));
        matA = matU.transpose().mul(matA).mul(matU);
        
        // if (m_logger != Complex(0.0, 0.0)) {
        //     m_logger.writeln("Итерация #" + iterCnt + ":\n" + matA);
        // }
        
        double sum = 0.0;
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i < j) {
                    sum += pow(matA.get(i, j), 2.0);
                }
            }
        }
        
        if (sqrt(sum) <= eps) {
            break;
        }
        
        ++iterCnt;
        
        if (iterCnt > MAX_ITERATIONS) {
            return false;
        }
    }
    
    for (int i = 0; i < n; ++i) {
        vecX[i] = matA.get(i, i);
    }
    
    return true;
}



void method4()
{
    ifstream fin("../data/in4.txt");
    ofstream fout("../data/out4.txt");
    int n, iterCnt;
    fin >> n;
    double eps;
    fin >> eps;
    Matrix mat(n);
    fin >> mat;
    Matrix matX(n);
    vector <double> vecX(n);
    
    fout << "Метод 4: Метод вращений\n";
    fout << "Исходная матрица:\n";
    fout <<  mat;
    
    //m_method.setLogger(logger);
    
    if (!rotation(mat, matX, vecX, eps, iterCnt)) {
        fout << "Матрица А не является симметричной или превышено количество итераций\n";
    } else {
        fout << "Количество интераций: " << iterCnt << "\n";
        fout << "Собственные значения:\n";
        
        for (int i = 0; i < n; ++i) {
            fout << "Lambda #" << i + 1 << ": " << vecX[i] << "\n";
        }
        
        fout << "Матрица собственных векторов:\n";
        fout << matX;
    }
    
    // output.close();
    // logger.close();
    // reader.close();
}

#endif