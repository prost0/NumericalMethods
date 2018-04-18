#include <vector>
#include <cmath>
#include <fstream>
#include "vector.hpp"


vector <double> vecAdd(vector <double> a, vector <double> b)
{
    vector <double> c(a.size());
    for (int i = 0; i < a.size(); ++i) {
        c[i] = a[i] + b[i];
    }
    return c;
}


vector <double> vecSub(vector <double> a, vector <double> b)
{
    vector <double> c(a.size());
    for (int i = 0; i < a.size(); ++i) {
        c[i] = a[i] - b[i];
    }
    return c;
}


double vecNormC(vector <double> v)
{
    double res = 0.0;
    
    for (int i = 0; i < v.size(); ++i) {
        res = max(res, abs(v[i]));
    }
    return res;
}


void inputVec(vector <double> &vec, ifstream &ifs)
{
    for (int i = 0; i < vec.size(); ++i) {
        ifs >> vec[i];
    }
}


void printVec(vector <double> &vec, ofstream &ofs)
{
    for (int i = 0; i < vec.size(); ++i) {
        ofs.width(10);
        ofs << vec[i] << " ";
    }
    ofs << "\n";
}