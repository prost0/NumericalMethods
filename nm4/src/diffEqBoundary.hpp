#ifndef __DIFF_EQ_BOUNDARY__
#define __DIFF_EQ_BOUNDARY__

#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "matrix.hpp"
#include "lup.hpp"
#include "vector.hpp"
#include "diffEqCauchy.hpp"
using namespace std;

class MethodDiffEqBoundary
{
public:
    MethodDiffEqBoundary(string exprR, string exprP, string exprQ, string exprF, double a, double b, double h, double alpha, double beta, double delta, double gamma, double y0, double y1)
    {
        m_exprR = exprR;
        m_exprP = exprP;
        m_exprQ = exprQ;
        m_exprF = exprF;
        m_a = a;
        m_b = b;
        m_h = h;
        m_alpha = alpha;
        m_beta = beta;
        m_delta = delta;
        m_gamma = gamma;
        m_y0 = y0;
        m_y1 = y1;
    }
    
    void shooting(vector <double> &vecX, vector <double> &vecY, double eps)
    {
        int n = getN();
        double yEta1;
        double yEta2;
        double eta1 = 1000000.0;
        double eta2 = -1000000.0;
        vector <double> vecZ(n);
        string strExprR = "x";
        string exprP = "2 / x";
        string exprQ = " - x / x";
        string exprF = "0 / x";
        
        yEta1 = fi(eta1, vecX, vecY, vecZ, exprP, exprQ, exprF);
        yEta2 = fi(eta2, vecX, vecY, vecZ, exprP, exprQ, exprF);
        
        double error = abs(eta2 - eta1);
        
        while (error > eps) {
            double etaN = eta2 - yEta2 * (eta2 - eta1) / (yEta2 - yEta1);
            
            yEta1 = yEta2;
            yEta2 = fi(etaN, vecX, vecY, vecZ, exprP, exprQ, exprF);
            eta1 = eta2;
            eta2 = etaN;
            error = abs(eta2 - eta1);
        }
    }
    
    void finiteDifference(vector <double> &vecX, vector <double> &vecY)
    {
        int n = getN();
        Matrix mat(n);
        vector <double> vec(n);
        
        vecX[0] = m_a;
        
        for (int i = 1; i < n; ++i) {
            vecX[i] = vecX[i - 1] + m_h;
        }
        
        mat.set(0, 0, m_alpha - 3.0 * m_beta / (2.0 * m_h));
        mat.set(0, 1, 4.0 * m_beta / (2.0 * m_h));
        mat.set(0, 2, -m_beta / (2.0 * m_h));
        vec[0] =  m_y0;
        
        for (int i = 1; i < n - 1; ++i) {
            double x = vecX[i];
            double rx = x;
            double px = 2 / rx;
            double qx = -x / rx;
            double fx = 0 / rx;
            double a = 1.0 / (m_h * m_h) - px / (2.0 * m_h);
            double b = -2.0 / (m_h * m_h) + qx;
            double c = 1.0 / (m_h * m_h) + px / (2.0 * m_h);
            
            mat.set(i, i - 1, a);
            mat.set(i, i, b);
            mat.set(i, i + 1, c);
            vec[i] = -fx;
        }
        
        mat.set(n - 1, n - 3, m_gamma / (2.0 * m_h));
        mat.set(n - 1, n - 2, -4.0 * m_gamma / (2.0 * m_h));
        mat.set(n - 1, n - 1, m_delta + 3.0 * m_gamma / (2.0 * m_h));
        vec[n - 1] = m_y1;
        
        lup(mat, vec, vecY);
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
    double fi(double eta, vector <double> &vecX, vector <double> &vecY, vector <double> &vecZ, string exprP, string exprQ, string exprF)
    {
        int n = getN();
        double y0;
        double z0;
        
        if (m_beta != 0.0) {
            y0 = eta;
            z0 = (m_y0 - m_alpha * eta) / m_beta;
        } else {
            y0 = m_y0 / m_alpha;
            z0 = eta;
        }
        
        MethodDiffEqCauchy method(exprP, exprQ, exprF, y0, z0, m_a, m_b, m_h);
        method.rungeKutta2(vecX, vecY, vecZ);
        
        return m_delta * vecY[n - 1] + m_gamma * vecZ[n - 1] - m_y1;
    }
    
    string m_exprR;
    string m_exprP;
    string m_exprQ;
    string m_exprF;
    double m_a;
    double m_b;
    double m_alpha;
    double m_beta;
    double m_delta;
    double m_gamma;
    double m_y0;
    double m_y1;
    double m_h;
};

#endif