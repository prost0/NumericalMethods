#ifndef __CUBIC__
#define __CUBIC__

#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include "matrix.hpp"
#include "vector.hpp"
#include "tma.hpp"

using namespace std;

class PolynomCubic
{
private:
    vector <double> m_vecX;
    vector <double> m_vecA;
    vector <double> m_vecB;
    vector <double> m_vecC;
    vector <double> m_vecD;
    
    
public:
    PolynomCubic(vector <double> vecX, vector <double> vecY)
    {
        int n = vecX.size();
        Matrix mat(n - 2);
        vector <double> vec(n - 2);
        //MethodSle method;
        vector <double> vecH(n - 1);
        m_vecX = vecX;
        m_vecA.resize(n - 1);
        m_vecB.resize(n - 1);
        m_vecC.resize(n - 1);
        m_vecD.resize(n - 1);
        int i;
        for (i = 0; i < n - 1; ++i) {
            vecH[i] =  m_vecX[i + 1] - m_vecX[i];
        }
        for (i = 0; i < n - 2; ++i) {
            vec[i] = 3.0 * ((vecY[i + 2] - vecY[i + 1]) / vecH[i] - (vecY[i + 1] - vecY[i]) / vecH[i + 1]);
        }
        mat.set(0, 0, 2.0 * (vecH[0] + vecH[1]));
        mat.set(0, 1, vecH[1]);
        
        for (i = 1; i < n - 3; ++i) {
            mat.set(i, i - 1, vecH[i - 1]);
            mat.set(i, i, 2.0 * (vecH[i - 1] + vecH[i]));
            mat.set(i, i + 1, vecH[i]);
        }
        
        mat.set(n - 3, n - 4, vecH[n - 3]);
        mat.set(n - 3, n - 3, 2.0 * (vecH[n - 4] + vecH[n - 3]));
        tma(mat, vec, m_vecC, false);
        
        for (i = n - 2; i > 0; --i) {
            m_vecC[i] = m_vecC[i - 1];
        }
        
        m_vecC[0] = 0.0;
        
        for (i = 0; i < n - 1; ++i) {
            m_vecA[i] = vecY[i];
        }
        
        for (i = 0; i < n - 2; ++i) {
            double h = vecH[i];
            m_vecB[i] = (vecY[i + 1] - vecY[i]) / h - h * (m_vecC[i + 1] + 2.0 * m_vecC[i]) / 3.0;
            m_vecD[i] = (m_vecC[i + 1] - m_vecC[i]) / (3.0 * h);
        }
        
        double h = vecH[n - 2];
        m_vecB[n - 2] = (vecY[n - 1] - vecY[n - 2]) / h - 2.0 * h * m_vecC[n - 2] / 3.0;
        m_vecD[n - 2] = -m_vecC[n - 2] / (3.0 * h);
    }
    
    double getValue(double x)
    {
        for (int i = 0; i < m_vecX.size() - 1; ++i) {
            if (m_vecX[i] <= x && x <= m_vecX[i + 1]) {
                double h = x - m_vecX[i];
                return m_vecA[i] + m_vecB[i] * h + m_vecC[i] * pow(h, 2.0) + m_vecD[i] * pow(h, 3.0);
            }
        }
        
        return 0.0;
    }
    
    string toString()
    {
        int n = m_vecX.size();
        stringstream res;
        
        for (int i = 0; i < n - 1; ++i) {
            res << "S(" << (i + 1) << ")=";
            res << m_vecA[i];
            if (m_vecB[i] >= 0.0) {
                res << "+";
            }
            
            res << m_vecB[i] << "(x-" << m_vecX[i] << ")" << "^1";
            if (m_vecC[i] >= 0.0) {
                res << "+";
            }
            
            res << m_vecC[i] << "(x-" << m_vecX[i] << ")" << "^2";
            if (m_vecD[i] >= 0.0) {
                res << "+";
            }
            
            res << m_vecD[i] << "(x-" << m_vecX[i] << ")" << "^3";
            if (i + 1 < n - 1) {
                res << "\n";
            }
        }
        
        return res.str();
    }
};
#endif