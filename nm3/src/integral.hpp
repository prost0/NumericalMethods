#ifndef __INTEGRAL__
#define __INTEGRAL__

#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include "matrix.hpp"
#include "vector.hpp"

using namespace std;

class MethodIntegral
{
private:
    double m_x0;
    double m_x1;
    double m_h;
    
public:
    MethodIntegral(double x0, double x1, double h)
    {
        m_x0 = x0;
        m_x1 = x1;
        m_h = h;
    }
    
    double function(double x)
    {
        return  x / (2 * x + 5);
    }
    
    double rectangle()
    {
        double res = 0.0;
        
        for (double x = m_x0 + m_h; x <= m_x1; x += m_h) {
            res += function((2.0 * x - m_h) / 2.0);
        }
        
        return res * m_h;
    }
    
    
    double trapezoidal()
    {
        double res = function(m_x0) / 2.0;
        
        for (double x = m_x0 + m_h; x <= m_x1 - m_h; x += m_h) {
            res += function(x);
        }
        
        res += function(m_x1) / 2.0;
        return res * m_h;
    }
    
    
    double simpson()
    {
        double res = function(m_x0);
        bool isTwo = false;
        
        for (double x = m_x0 + m_h; x <= m_x1 - m_h; x += m_h) {
            res += function(x) * (isTwo ? 2.0 : 4.0);
            isTwo = !isTwo;
        }
        
        res += function(m_x1);
        return res * m_h / 3.0;
    }
    
    
    void setH(double h)
    {
        m_h = h;
    }
};
#endif
