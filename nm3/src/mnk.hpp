#ifndef __MNK__
#define __MNK__

#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include "matrix.hpp"
#include "vector.hpp"
#include "lup.hpp"

using namespace std;

class PolynomMNK
{
private:
    vector <double> m_vecX;
    vector <double> m_vecY;
    vector <double> m_poly;
    
public:
    PolynomMNK(vector <double> vecX, vector <double> vecY, long long degree)
    {
        long long n = vecX.size();
        long long m = degree + 1;
        long long sumCnt = degree * 2 + 1;
        double sumsMat[sumCnt];
        double sumsVec[m];
        Matrix mat(m);
        vector <double> vec(m);
        vector <double> vecA(m);
        m_vecX = vecX;
        m_vecY = vecY;
        
        long long i;
        long long j;
        for (i = 0; i < sumCnt; ++i) {
            for (j = 0; j < n; ++j) {
                sumsMat[i] += pow(m_vecX[j], (double)i);
            }
        }
        
        for (i = 0; i < m; ++i) {
            for (j = 0; j < n; ++j) {
                sumsVec[i] += m_vecY[j] * pow(m_vecX[j], (double)i);
            }
        }
        
        for (i = 0; i < m; ++i) {
            for (j = 0; j < m; ++j) {
                mat.set(i, j, sumsMat[i + j]);
            }
        }
        
        for (i = 0; i < m; ++i) {
            vec[i] = sumsVec[i];
        }
        
        lup(mat, vec, vecA);
        m_poly = vecA;
    }
    
    double getSumOfSquares()
    {
        double res = 0.0;
        
        for (long long i = 0; i < m_vecX.size(); ++i) {
            double sum = 0.0;
            for (int j = 0; j < m_poly.size(); ++j) {
                sum += m_poly[j] * pow(m_vecX[i], (double)j);
            }
            res += pow(sum - m_vecY[i], 2.0);
        }
        
        return res;
    }
    
    double getValue(double x)
    {
        double res = 0.0;
        
        for (int i = 0; i < m_poly.size(); ++i) {
            res += m_poly[i] * pow(x, (double)i);
        }
        
        return res;
    }
    
    string toString()
    {
        stringstream res;
        res << m_poly[0];
        
        for (int i = 1; i < m_poly.size(); ++i) {
            if (m_poly[i] >= 0.0) {
                res << "+";
            }
            
            res << m_poly[i] << "x^" << i;
        }
        
        return res.str();
    }
};

#endif