#ifndef __DIFF_EQ_CAUCHY__
#define __DIFF_EQ_CAUCHY__

#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "matrix.hpp"
#include "vector.hpp"
using namespace std;

class MethodDiffEqCauchy
{
public:
    MethodDiffEqCauchy(string exprP, string exprQ, string exprF, double y0, double z0, double a, double b, double h)
    {
        m_exprP = exprP;
        m_exprQ = exprQ;
        m_exprF = exprF;
        m_y0 = y0;
        m_z0 = z0;
        m_a = a;
        m_b = b;
        m_h = h;
    }
    
    void euler(vector <double> &vecX, vector <double> &vecY)
    {
        int n = getN();
        vector <double> vecZ(n);
        
        vecX[0] = m_a;
        vecY[0] = m_y0;
        vecZ[0] = m_z0;
        
        for (int i = 1; i < n; ++i) {
            vecX[i] = vecX[i - 1] + m_h;
            vecY[i] = vecY[i - 1] + m_h * vecZ[i - 1];
            vecZ[i] = vecZ[i - 1] + m_h * g(vecX[i - 1], vecY[i - 1], vecZ[i - 1]);
        }
    }
    
    void rungeKutta(vector <double> &vecX, vector <double> &vecY, vector <double> &vecZ)
    {
        int n = getN();
        
        vecX[0] = m_a;
        vecY[0] = m_y0;
        vecZ[0] = m_z0;
        
        for (int i = 1; i < n; ++i) {
            vecX[i] = vecX[i - 1] + m_h;
            vecY[i] = vecY[i - 1] + dy(vecX[i - 1], vecY[i - 1], vecZ[i - 1]);
            vecZ[i] = vecZ[i - 1] + dz(vecX[i - 1], vecY[i - 1], vecZ[i - 1]);
        }
    }
    
    void rungeKutta2(vector <double> &vecX, vector <double> &vecY, vector <double> &vecZ)
    {
        int n = getN();
        
        vecX[0] = m_a;
        vecY[0] = m_y0;
        vecZ[0] = m_z0;
        
        for (int i = 1; i < n; ++i) {
            vecX[i] = vecX[i - 1] + m_h;
            vecY[i] = vecY[i - 1] + dy2(vecX[i - 1], vecY[i - 1], vecZ[i - 1]);
            vecZ[i] = vecZ[i - 1] + dz2(vecX[i - 1], vecY[i - 1], vecZ[i - 1]);
        }
    }
    
    void adams(vector <double> &vecX, vector <double> &vecY)
    {
        int n = getN();
        double b = m_b;
        vector <double> vecZ(n);
        
        setB(m_a + 3.0 * m_h);
        rungeKutta(vecX, vecY, vecZ);
        setB(b);
        
        for (int i = 4; i < n; ++i) {
            double deltaY = 0.0;
            double deltaZ = 0.0;
            
            deltaY += 55.0 * vecZ[i - 1];
            deltaY -= 59.0 * vecZ[i - 2];
            deltaY += 37.0 * vecZ[i - 3];
            deltaY -= 9.0 * vecZ[i - 4];
            deltaY /= 24.0;
            
            deltaZ += 55.0 * g(vecX[i - 1], vecY[i - 1], vecZ[i - 1]);
            deltaZ -= 59.0 * g(vecX[i - 2], vecY[i - 2], vecZ[i - 2]);
            deltaZ += 37.0 * g(vecX[i - 3], vecY[i - 3], vecZ[i - 3]);
            deltaZ -= 9.0 * g(vecX[i - 4], vecY[i - 4], vecZ[i - 4]);
            deltaZ /= 24.0;
            
            vecX[i] = vecX[i - 1] + m_h;
            vecY[i] = vecY[i - 1] + m_h * deltaY;
            vecZ[i] = vecZ[i - 1] + m_h * deltaZ;
        }
    }
    
    int getN()
    {
        return (int)((m_b - m_a) / m_h) + 1;
    }
    
    void setH(double h)
    {
        m_h = h;
    }
    
private:
    void setB(double b)
    {
        m_b = b;
    }
    
    double g(double x, double y, double z)
    {
    
        return -(0 * z + 1 * y + (-sin(3 * x)));
    }
    
    double g2(double x, double y, double z)
    {
    
        return -(2 / x * z + (-x / x) * y + 0);
    }
    
    
    
    double k1(double z)
    {
        return m_h * z;
    }
    
    double l1(double x, double y, double z)
    {
        return m_h * g(x, y, z);
    }
    
    double k2(double x, double y, double z)
    {
        return m_h * (z + 0.5 * l1(x, y, z));
    }
    
    double l2(double x, double y, double z)
    {
        return m_h * g(x + 0.5 * m_h, y + 0.5 * k1(z), z + 0.5 * l1(x, y, z));
    }
    
    double k3(double x, double y, double z)
    {
        return m_h * (z + 0.5 * l2(x, y, z));
    }
    
    double l3(double x, double y, double z)
    {
        return m_h * g(x + 0.5 * m_h, y + 0.5 * k2(x, y, z), z + 0.5 * l2(x, y, z));
    }
    
    double k4(double x, double y, double z)
    {
        return m_h * (z + l3(x, y, z));
    }
    
    double l4(double x, double y, double z)
    {
        return m_h * g(x + m_h, y + k3(x, y, z), z + l3(x, y, z));
    }
    
    double k1_2(double z)
    {
        return m_h * z;
    }
    
    double l1_2(double x, double y, double z)
    {
        return m_h * g2(x, y, z);
    }
    
    double k2_2(double x, double y, double z)
    {
        return m_h * (z + 0.5 * l1_2(x, y, z));
    }
    
    double l2_2(double x, double y, double z)
    {
        return m_h * g2(x + 0.5 * m_h, y + 0.5 * k1_2(z), z + 0.5 * l1_2(x, y, z));
    }
    
    double k3_2(double x, double y, double z)
    {
        return m_h * (z + 0.5 * l2_2(x, y, z));
    }
    
    double l3_2(double x, double y, double z)
    {
        return m_h * g2(x + 0.5 * m_h, y + 0.5 * k2_2(x, y, z), z + 0.5 * l2_2(x, y, z));
    }
    
    double k4_2(double x, double y, double z)
    {
        return m_h * (z + l3_2(x, y, z));
    }
    
    double l4_2(double x, double y, double z)
    {
        return m_h * g2(x + m_h, y + k3_2(x, y, z), z + l3_2(x, y, z));
    }
    
    double dy(double x, double y, double z)
    {
        return (k1(z) + 2.0 * k2(x, y, z) + 2.0 * k3(x, y, z) + k4(x, y, z)) / 6.0;
    }
    
    double dz(double x, double y, double z)
    {
        return (l1(x, y, z) + 2.0 * l2(x, y, z) + 2.0 * l3(x, y, z) + l4(x, y, z)) / 6.0;
    }
    
    double dy2(double x, double y, double z)
    {
        return (k1_2(z) + 2.0 * k2_2(x, y, z) + 2.0 * k3_2(x, y, z) + k4_2(x, y, z)) / 6.0;
    }
    
    double dz2(double x, double y, double z)
    {
        return (l1_2(x, y, z) + 2.0 * l2_2(x, y, z) + 2.0 * l3_2(x, y, z) + l4_2(x, y, z)) / 6.0;
    }
    
    string m_exprP;
    string m_exprQ;
    string m_exprF;
    double m_y0;
    double m_z0;
    double m_a;
    double m_b;
    double m_h;
};

#endif