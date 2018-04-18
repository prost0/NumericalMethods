#ifndef __method_2__
#define __method_2__

#include <vector>
#include <cmath>
#include <fstream>
#include "vector.hpp"
#include "matrix.hpp"


using namespace std;


bool m_tmaCheck(Matrix &mat)
{
    int n = mat.getSize();
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j - 1 || i == j || i == j + 1) {
                if (mat.get(i, j) == 0.0) {
                    return false;
                }
            } else if (mat.get(i, j) != 0.0) {
                return false;
            }
        }
    }
    
    if (abs(mat.get(0, 0)) < abs(mat.get(0, 1)) ||
            abs(mat.get(n - 1, n - 1)) < abs(mat.get(n - 1, n - 2))) {
        return false;
    }
    
    for (int i = 1; i < n - 1; ++i) {
        if (abs(mat.get(i, i)) < abs(mat.get(i, i - 1)) + abs(mat.get(i, i + 1))) {
            return false;
        }
    }
    
    return true;
}



bool tma(Matrix &mat, vector <double> &vec, vector <double> &vecX, bool checkCond)
{
    if (checkCond && !m_tmaCheck(mat)) {
        return false;
    }
    
    int n = mat.getSize();
    vector <double> vecP(n, 0);
    vector <double> vecQ(n);
    
    vecP[0] = -mat.get(0, 1) / mat.get(0, 0);
    vecQ[0] = vec[0] / mat.get(0, 0);
    
    for (int i = 1; i < n - 1; ++i) {
        double a = mat.get(i, i - 1);
        double b = mat.get(i, i);
        double c = mat.get(i, i + 1);
        
        vecP[i] = -c / (b + a * vecP[i - 1]);
        vecQ[i] = (vec[i] - a * vecQ[i - 1]) / (b + a * vecP[i - 1]);
    }
    
    double resUp = vec[n - 1] - mat.get(n - 1, n - 2) * vecQ[n - 2];
    double resDown = mat.get(n - 1, n - 1) + mat.get(n - 1, n - 2) * vecP[n - 2];
    
    vecQ[n - 1] = resUp / resDown;
    vecX[n - 1] = vecQ[n - 1];
    
    for (int i = n - 2; i >= 0; --i) {
        vecX[i] = vecP[i] * vecX[i + 1] + vecQ[i];
    }
    
    return true;
}

void method2()
{
    ifstream fin("../data/in2.txt");
    ofstream fout("../data/out2.txt");
    //fout.setf(ios::left);
    int n;
    fin >> n;
    Matrix mat(n);
    fin >> mat;
    vector <double> vec(n);
    
    for (int i = 0; i < n; ++i) {
        fin >> vec[i];
    }
    
    vector <double> vecX(n);
    
    fout << "Метод 2: Метод прогонки\n";
    fout << "Исходная матрица:\n";
    fout << mat;
    fout << "Исходный вектор:\n" ;
    printVec(vec, fout);
    
    
    if (!tma(mat, vec, vecX, true)) {
        fout << "Матрица A не является трехдиагональной или не выполнено условие |b| >= |a| + |c|\n";
    } else {
        fout << "Решение:\n";
        printVec(vecX, fout);
    }
}

#endif