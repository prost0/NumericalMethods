#ifndef __NEWTON__
#define __NEWTON__

#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include "matrix.hpp"
#include "vector.hpp"

using namespace std;

class PolynomNewton
{
private:
    vector <double> m_vecX;
    
    double m_funcDiff(long long i, long long j)
    {
        return i == j ? sin(m_vecX[i]) : (m_funcDiff(i, j - 1) - m_funcDiff(i + 1, j)) / (m_vecX[i] - m_vecX[j]);
    }
    
public:

    PolynomNewton(vector <double> vecX)
    {
        m_vecX = vecX;
    }
    
    
    double getValue(double x)
    {
        double res = 0.0;
        
        for (long long i = 0; i < m_vecX.size(); ++i) {
            double w = 1.0;
            
            for (long long j = 0; j < i; ++j) {
                w *= x - m_vecX[j];
            }
            
            res += m_funcDiff(0, i) * w;
        }
        
        return res;
    }
    
    string toString()
    {
        stringstream res;
        
        if (m_vecX.size() > 0) {
            res << m_funcDiff(0, 0);
        }
        
        for (long long i = 1; i < m_vecX.size(); ++i) {
            double f = m_funcDiff(0, i);
            if (f >= 0.0) {
                res << "+";
            }
            
            res << f;
            
            for (long long j = 0; j < i; ++j) {
                res << "(x-" << m_vecX[j] << ")";
            }
        }
        
        return res.str();
    }
};
#endif