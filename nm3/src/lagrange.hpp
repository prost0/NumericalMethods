#ifndef __LAGRANGE__
#define __LAGRANGE__

#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include "matrix.hpp"
#include "vector.hpp"

using namespace std;

class PolynomLagrange
{
private:
    vector <double> m_vecX;
    vector <double> m_vecY;
    
public:
    PolynomLagrange(vector <double> vecX)
    {
        m_vecX = vecX;
        m_vecY.resize(m_vecX.size());
        vector <double> vecW(m_vecX.size());
        
        long long i;
        for (i = 0; i < m_vecX.size(); ++i) {
            m_vecY[i] = sin(m_vecX[i]);
        }
        
        for (i = 0; i < m_vecX.size(); ++i) {
            double w = 1.0;
            
            for (long long j = 0; j < m_vecX.size(); ++j) {
                if (i != j) {
                    w *= m_vecX[i] - m_vecX[j];
                }
            }
            
            vecW[i] = w;
        }
        
        for (i = 0; i < m_vecX.size(); ++i) {
            m_vecY[i] = m_vecY[i] / vecW[i];
        }
        
    }
    
    double getValue(double x)
    {
        long long n = m_vecX.size();
        double res = 0.0;
        
        for (long long i = 0; i < n; ++i) {
            double w = 1.0;
            
            for (long long j = 0; j < n; ++j) {
                if (i != j) {
                    w *= x - m_vecX[j];
                }
            }
            
            res += m_vecY[i] * w;
        }
        
        return res;
    }
    
    string toString()
    {
        long long n = m_vecX.size();
        stringstream res;
        if (m_vecX.size() > 0) {
            res << m_vecY[0];
        }
        long long i;
        for (i = 1; i < n; ++i) {
            res << "(x-" << m_vecX[i] << ")";
        }
        
        for (i = 1; i < n; ++i) {
            if (m_vecY[i] >= 0.0) {
                res << "+";
            }
            
            res << m_vecY[i];
            
            for (long long j = 0; j < n; ++j) {
                if (i != j) {
                    res << "(x-" << m_vecX[j] << ")";
                }
            }
        }
        string ress = res.str();
        return ress;
    }
};

#endif