#ifndef __ERROR__
#define __ERROR__

#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include "matrix.hpp"
#include "vector.hpp"

using namespace std;

double func1(double x)
{
    return  cos(x) + sin(x) * 11 / 8 - sin(3 * x) / 8;
}

double calcError1(vector <double> vecX, vector <double> vecY)
{
    double res = 0.0;
    
    for (int i = 0; i < vecX.size(); ++i) {
        res += abs(func1(vecX[i]) - vecY[i]);
    }
    
    return res;
}

double func2(double x)
{
    return  exp(x) / x;
}

double calcError2(vector <double> vecX, vector <double> vecY)
{
    double res = 0.0;
    
    for (int i = 0; i < vecX.size(); ++i) {
        res += abs(func2(vecX[i]) - vecY[i]);
    }
    
    return res;
}

double rungeRomberg(double h1, double h2, double y1, double y2, double p)
{
    double r = h2 / h1;
    return (y1 - y2) / (pow(r, p) - 1.0);
}

#endif
