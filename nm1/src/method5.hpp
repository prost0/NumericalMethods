#ifndef __method_5__
#define __method_5__
#include <vector>
#include <cmath>
#include <fstream>
#include "matrix.hpp"
#include "vector.hpp"
#include "complex.hpp"


using namespace std;

void m_qr(Matrix &mat, Matrix &matQ, Matrix &matR)
{
    int n = mat.getSize();
    Matrix matA(n);
    Matrix matE(n);
    Matrix matResQ(n);
    
    matA.copy(mat);
    matE.identity();
    matResQ.identity();
    
    for (int j = 0; j < n - 1; ++j) {
        vector <double> vec(n);
        Matrix ratioBottom(n);
        double sum = 0.0;
        
        for (int i = j; i < n; ++i) {
            sum += pow(matA.get(i, j), 2.0);
        }
        
        vec[j] = matA.get(j, j) + (matA.get(j, j) >= 0.0 ? 1.0 : -1.0) * sqrt(sum);
        
        for (int i = j + 1; i < n; ++i) {
            vec[i] = matA.get(i, j);
        }
        
        sum = 0.0;
        
        for (int i = 0; i < n; ++i) {
            sum += pow(vec[i], 2.0);
            
            for (int k = 0; k < n; ++k) {
                ratioBottom.set(i, k, vec[i] * vec[k]);
            }
        }
        
        Matrix matH = matE.sub(ratioBottom.mul(2.0 / sum));
        
        matA = matH.mul(matA);
        matResQ = matResQ.mul(matH);
    }
    
    matQ.copy(matResQ);
    matR.copy(matA);
}


void m_qrSolveBlock(Matrix &mat, int &col, Complex &c1, Complex &c2)
{
    double b = -(mat.get(col, col) + mat.get(col + 1, col + 1));
    double c = mat.get(col, col) * mat.get(col + 1, col + 1) - mat.get(col, col + 1) * mat.get(col + 1, col);
    double d = pow(b, 2.0) - 4.0 * c;
    
    if (d >= 0.0) {
        double dRoot = sqrt(d);
        
        c1.setRe((-b - dRoot) / 2.0);
        c2.setRe((-b + dRoot) / 2.0);
    } else {
        double dRoot = sqrt(-d);
        
        c1.setRe(-b / 2.0);
        c1.setIm(-dRoot / 2.0);
        c2.setRe(-b / 2.0);
        c2.setIm(dRoot / 2.0);
    }
}


double m_qrNorm(Matrix &mat, int &col)
{
    double res = 0.0;
    
    for (int i = col + 1; i < mat.getSize(); ++i) {
        res += pow(mat.get(i, col), 2.0);
    }
    
    return sqrt(res);
}


bool qr(Matrix &mat, vector <Complex> &res, double &eps, int &iterCnt)
{
    int n = mat.getSize();
    Matrix matA(n);
    vector <Complex> prev(n, Complex(1e+6, 0.0));
    vector <bool> isComplex(n, true);
    iterCnt = 0;
    double error = eps + 1.0;
    
    if ((n & 1) == 1) {
        isComplex[n - 1] = false;
    }
    
    matA.copy(mat);
    
    while (error > eps) {
        Matrix matQ(n);
        Matrix matR(n);
        double errorRat = 0.0;
        double errorCom = 0.0;
        
        ++iterCnt;
        
        m_qr(matA, matQ, matR);
        matA = matR.mul(matQ);
        
        for (int j = 0; j < n; ++j) {
            if (isComplex[j]) {
                if (m_qrNorm(matA, j) <= eps) {
                    if (j + 2 < n) {
                        for (int i = n - 1; i > j; --i) {
                            isComplex[i] = isComplex[i - 1];
                            prev[i] = prev[i - 1];
                            res[i] = res[i - 1];
                        }
                    } else {
                        isComplex[n - 1] = false;
                        prev[n - 1] = Complex(0.0, 0.0);
                    }
                    
                    isComplex[j] = false;
                    prev[j] = Complex(0.0, 0.0);
                    res[j] = Complex(0.0, 0.0);
                    --j;
                } else {
                    m_qrSolveBlock(matA, j, res[j], res[j + 1]);
                    
                    errorCom = max(errorCom, res[j].sub(prev[j]).abs());
                    errorCom = max(errorCom, res[j + 1].sub(prev[j + 1]).abs());
                    
                    ++j;
                }
            } else {
                res[j].setRe(matA.get(j, j));
                errorRat = max(errorRat, m_qrNorm(matA, j));
            }
        }
        
        for (int i = 0; i < n; ++i) {
            if (isComplex[i]) {
                prev[i].setRe(res[i].getRe());
                prev[i].setIm(res[i].getIm());
            }
        }
        
        error = max(errorRat, errorCom);
        
        if (iterCnt > MAX_ITERATIONS) {
            return false;
        }
    }
    return true;
}




void method5()
{
    ifstream fin("../data/in5.txt");
    ofstream fout("../data/out5.txt");
    int n, iterCnt;
    fin >> n;
    double eps;
    fin >> eps;
    Matrix mat(n);
    fin >> mat;
    vector <Complex> res(n);
    
    fout << "Метод 5: QR - алгоритм\n";
    fout << "Исходная матрица:\n";
    fout << mat;
    
    for (int i = 0; i < n; ++i) {
        res[i] = Complex(0.0, 0.0);
    }
    
    if (!qr(mat, res, eps, iterCnt)) {
        fout << "Превышен лимит итераций.\n";
        return;
    }
    
    fout << "Количество интераций: " << iterCnt << "\n";
    fout << ("Собственные значения:\n");
    
    for (int i = 0; i < n; ++i) {
        fout << "Lambda #" << i + 1 << ": Re = " << res[i].getRe() << " Im = " << res[i].getIm() << "\n";
    }
}

#endif