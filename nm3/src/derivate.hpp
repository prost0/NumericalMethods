#ifndef __DERIVATE__
#define __DERIVATE__

#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include "matrix.hpp"
#include "vector.hpp"

using namespace std;

class MethodDerivate
{
private:
    vector <double> m_vecX;
    vector <double> m_vecY;
    double m_x;
    
public:
    MethodDerivate(vector <double> vecX, vector <double> vecY, double x)
    {
        m_vecX = vecX;
        m_vecY = vecY;
        m_x = x;
    }
    
    double deriv1()
    {
        int i = 0;
        double res = 0.0;
        
        for (int j = 0; j < m_vecX.size(); ++j) {
            if (m_vecX[j] == m_x) {
                i = j;
                break;
            }
        }
        
        res += (m_vecY[i + 1] - m_vecY[i]) / (m_vecX[i + 1] - m_vecX[i]);
        res -= (m_vecY[i] - m_vecY[i - 1]) / (m_vecX[i] - m_vecX[i - 1]);
        res /= m_vecX[i + 1] - m_vecX[i - 1];
        res *= 2.0 * m_x - m_vecX[i - 1] - m_vecX[i];
        res += (m_vecY[i] - m_vecY[i - 1]) / (m_vecX[i] - m_vecX[i - 1]);
        return res;
    }
    
    double deriv2()
    {
        int i = 0;
        double res = 0.0;
        
        for (int j = 0; j < m_vecX.size(); ++j) {
            if (m_vecX[j] == m_x) {
                i = j;
                break;
            }
        }
        
        res += (m_vecY[i + 1] - m_vecY[i]) / (m_vecX[i + 1] - m_vecX[i]);
        res -= (m_vecY[i] - m_vecY[i - 1]) / (m_vecX[i] - m_vecX[i - 1]);
        res /= m_vecX[i + 1] - m_vecX[i - 1];
        res *= 2.0;
        return res;
    }
};

#endif