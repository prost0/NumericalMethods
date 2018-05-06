#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "matrix.hpp"
#include "vector.hpp"
#include "error.hpp"
#include "diffEqBoundary.hpp"

using namespace std;

inline double correctX1(double x)
{
    return cos(x) + sin(x) * 11 / 8 - sin(3 * x) / 8;
}

inline double correctX2(double x)
{
    return x != 0 ? exp(x) / x : 0;
}


void part1()
{
    ifstream fin("../data/in1.txt");
    ofstream fout("../data/out1.txt");
    string exprP;
    fin >> exprP;
    string exprQ;
    fin >> exprQ;
    string exprF;
    fin >> exprF;
    string exprA;
    fin >> exprA;
    double y0;
    fin >> y0;
    double z0;
    fin >> z0;
    double a;
    fin >> a;
    double b;
    fin >> b;
    double h;
    fin >> h;
    double h2 = h / 2.0;
    MethodDiffEqCauchy method(exprP, exprQ, exprF, y0, z0, a, b, h);
    int n = method.getN();
    
    vector <double> vecX1(n);
    vector <double> vecY1(n);
    vector <double> vecZ1(n);
    vector <double> vecX2(n * 2);
    vector <double> vecY2(n * 2);
    vector <double> vecZ2(n * 2);
    vector <double> vecY(n);
    method.euler(vecX1, vecY1);
    method.setH(h2);
    method.euler(vecX2, vecY2);
    method.setH(h);
    
    for (int i = 0; i < n; ++i) {
        vecY[i] = correctX1(vecX1[i]);
    }
    
    fout << ("Метод 1: Метод Эйлера\n");
    fout << ("Решение:\n");
    fout << "X: ";
    printVec(vecX1, fout);
    fout << "Y: ";
    printVec(vecY1, fout);
    fout << ("Точное решение:\n");
    fout << "Y: ";
    printVec(vecY, fout);
    fout << "Погрешность относительно точного решения:\n" << calcError1(vecX1, vecY1) << "\n";
    fout << ("Погрешность методом Рунге-Ромберга:\n");
    
    for (int i = 0; i < n; ++i) {
        fout << "X[" << i << "]: " << rungeRomberg(h, h2, vecY1[i], vecY2[i * 2], 2.0) << "\n";
    }
    
    method.rungeKutta(vecX1, vecY1, vecZ1);
    method.setH(h2);
    method.rungeKutta(vecX2, vecY2, vecZ2);
    method.setH(h);
    
    fout << ("\nМетод 2: Метод Рунге-Кутты\n");
    fout << ("Решение:");
    fout << "X: ";
    printVec(vecX1, fout);
    fout << "Y: ";
    printVec(vecY1, fout);
    fout << ("Точное решение:");
    fout << "Y: ";
    printVec(vecY, fout);
    fout << "Погрешность относительно точного решения:\n";
    fout << calcError1(vecX1, vecY1) << "\n";
    fout << ("Погрешность методом Рунге-Ромберга:\n");
    
    for (int i = 0; i < n; ++i) {
        fout << "X[" << i << "]: ";
        fout << rungeRomberg(h, h2, vecY1[i], vecY2[i * 2], 4.0) << "\n";
    }
    
    method.adams(vecX1, vecY1);
    method.setH(h2);
    method.adams(vecX2, vecY2);
    method.setH(h);
    
    fout << ("\nМетод 3: Метод Адамса\n");
    fout << ("Решение:\n");
    fout << "X: ";
    printVec(vecX1, fout);
    fout << "Y: ";
    printVec(vecY1, fout);
    fout << ("Точное решение:\n");
    fout << "Y: ";
    printVec(vecY, fout);
    fout << "Погрешность относительно точного решения: ";
    fout << calcError1(vecX1, vecY1) << "\n";
    fout << "Погрешность методом Рунге-Ромберга:\n";
    
    for (int i = 0; i < n; ++i) {
        fout << "X[" << i << "]: ";
        fout <<  rungeRomberg(h, h2, vecY1[i], vecY2[i * 2], 4.0) << "\n";
    }
    
    fin.close();
    fout.close();
}


void part2()
{
    ifstream fin("../data/in2.txt");
    ofstream fout("../data/out2.txt");
    string exprR;
    fin >> exprR;
    string exprP;
    fin >> exprP;
    string exprQ;
    fin >> exprQ;
    string exprF;
    fin >> exprF;
    string exprA;
    fin >> exprA;
    double a;
    fin >> a;
    double b;
    fin >> b;
    double h;
    fin >> h;
    double alpha;
    fin >> alpha;
    double beta;
    fin >> beta;
    double delta;
    fin >> delta;
    double gamma;
    fin >> gamma;
    double y0;
    fin >> y0;
    double y1;
    fin >> y1;
    double eps;
    fin >> eps;
    double h2 = h / 2.0;
    MethodDiffEqBoundary method(exprR, exprP, exprQ, exprF, a, b, h, alpha, beta, delta, gamma, y0, y1);
    int n = method.getN();
    vector <double> vecX1(n);
    vector <double> vecY1(n);
    vector <double> vecX2(n * 2);
    vector <double> vecY2(n * 2);
    vector <double> vecY(n);
    vector <double> vecError(n);
    
    method.shooting(vecX1, vecY1, eps);
    method.setH(h2);
    method.shooting(vecX2, vecY2, eps);
    method.setH(h);
    
    for (int i = 0; i < n; ++i) {
        vecY[i] =  correctX2(vecX1[i]);
    }
    
    fout << ("Метод 1: Метод стрельбы\n");
    fout << ("Решение:\n");
    fout << "X: ";
    printVec(vecX1, fout);
    fout << "Y: ";//
    printVec(vecY1, fout);
    fout << "Точное решение:\n";
    fout << "Y: ";
    printVec(vecY, fout);
    fout << "Погрешность относительно точного решения:\n";
    fout << calcError2(vecX1, vecY1) << "\n";
    fout << "Погрешность методом Рунге-Ромберга:" << "\n";
    
    for (int i = 0; i < n; ++i) {
        vecError[i] = rungeRomberg(h, h2, vecY1[i], vecY2[i * 2], 2.0);
        fout << "X[" << i << "]: " << vecError[i] << "\n";
    }
    
    method.finiteDifference(vecX1, vecY1);
    method.setH(h2);
    method.finiteDifference(vecX2, vecY2);
    method.setH(h);
    
    fout << ("\nМетод 2: Метод конечных разностей\n");
    fout << ("Решение:\n");
    fout << "X: ";
    printVec(vecX1, fout);
    fout << "Y: ";
    printVec(vecY1, fout);
    fout << ("Точное решение:\n");
    fout << "Y: ";
    printVec(vecY, fout);
    fout << "Погрешность относительно точного решения:\n" << calcError2(vecX1, vecY1) << "\n";
    fout << "Погрешность методом Рунге-Ромберга:\n";
    
    for (int i = 0; i < n; ++i) {
        vecError[i] = rungeRomberg(h, h2, vecY1[i], vecY2[i * 2], 2.0);
        fout << "X[" << i << "]: " << vecError[i] << "\n";
    }
    
    fin.close();
    fout.close();
}


int main()
{
    part1();
    part2();
    
    return 0;
}