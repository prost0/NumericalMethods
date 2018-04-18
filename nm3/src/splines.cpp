#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>
#include "splines.hpp"
using namespace std;

void m_lagrangeNewton(string inputName, string outputName)
{
    ifstream fin(inputName.c_str());
    ofstream fout(outputName.c_str());
    long long n;
    fin >> n;
    vector <double> vecX(n);
    inputVec(vecX, fin);
    string func;
    fin >> func;
    double x;
    fin >> x;
    
    fout << "Метод 1: Интерполяция\n";
    fout << "X: \n";
    printVec(vecX, fout);
    fout << "X*=" << x << "\n";
    
    PolynomLagrange polyL(vecX);
    PolynomNewton polyN(vecX);
    
    fout << "Полиномы:\n";
    fout << "L(x)=" << polyL.toString() << "\n";
    fout << "e(X)=" << abs(polyL.getValue(x) - sin(x)) << "\n";
    fout << "y(X)=" << polyL.getValue(x) << "\n";
    fout << "N(x)=" << polyN.toString() << "\n";
    fout << "e(X)=" << abs(polyN.getValue(x) - sin(x)) << "\n";
    fout << "y(X)=" << polyN.getValue(x) << "\n";
    
    fin.close();
    fout.close();
}

void lagrangeNewton()
{
    m_lagrangeNewton("../data/input/in1_a.txt", "../data/output/out1_a.txt");
    m_lagrangeNewton("../data/input/in2_b.txt", "../data/output/out2_b.txt");
}




void cubic()
{
    ifstream fin("../data/input/in2.txt");
    ofstream fout("../data/output/out2.txt");
    vector <double> vecX;
    inputVec(vecX, fin);
    vector <double> vecY;
    inputVec(vecY, fin);
    double x;
    fin >> x;
    
    fout << ("Метод 2: Кубический сплайн\n");
    fout << "X: ";
    printVec(vecX, fout);
    fout << "Y: ";
    printVec(vecY, fout);
    fout << "X*=" << x << "\n";
    
    PolynomCubic polyC(vecX, vecY);
    
    fout << "Сплайн S(x):\n";
    fout << polyC.toString();
    fout << "S(X*)=" << polyC.getValue(x) << "\n";
    fout.close();
    fin.close();
}

void mnk()
{
    ifstream fin("../data/input/in3.txt");
    ofstream fout("../data/output/out3.txt");
    vector <double> vecX;
    inputVec(vecX, fin);
    vector <double> vecY;
    inputVec(vecY, fin);
    vector <double> vecTmp(vecX.size());
    //Plotter plot = new Plotter(512.0, 512.0);
    
    //plot.addData(vecX, vecY, Color.RED, "f(x)");
    
    fout << "Метод 3: МНК-аппроксимация\n";
    fout << "X: ";
    printVec(vecX, fout);
    fout << "Y: ";
    printVec(vecY, fout);
    
    PolynomMNK polyM(vecX, vecY, 1);
    
    fout << "Полиномы:\n";
    fout << "P1(x)=" << polyM.toString();
    fout << "e1=" << polyM.getSumOfSquares() << "\n";
    
    for (int i = 0; i < vecTmp.size(); ++i) {
        vecTmp[i] = polyM.getValue(vecX[i]);
    }
    
    //plot.addData(vecX, vecTmp, Color.GREEN, "P1(x)");
    
    PolynomMNK polyMN(vecX, vecY, 2);
    
    fout << "P2(x)=" << polyMN.toString() << "\n";
    fout << "e2=" << polyMN.getSumOfSquares() << "\n";
    
    for (int i = 0; i < vecTmp.size(); ++i) {
        vecTmp[i] = polyMN.getValue(vecX[i]);
    }
    
    //plot.addData(vecX, vecTmp, Color.BLUE, "P2(x)");
    //plot.savePng("src/data/plot/plot3.png");
    
    fout.close();
    fin.close();
}

void derivate()
{
    ifstream fin("../data/input/in4.txt");
    ofstream fout("../data/output/out4.txt");
    vector <double> vecX;
    inputVec(vecX, fin);
    vector <double> vecY;
    inputVec(vecY, fin);
    double x;
    fin >> x;
    MethodDerivate method(vecX, vecY, x);
    
    fout << "Метод 4: Численное дифференцирование\n";
    fout << "X: ";
    printVec(vecX, fout);
    fout << "Y: ";
    printVec(vecY, fout);
    fout << "X*=" << x << "\n";
    fout << "f'(X*)=" << method.deriv1() << "\n";
    fout << "f''(X*)=" << method.deriv2() << "\n";
    fout.close();
    fin.close();
}

void integral()
{
    ifstream fin("../data/input/in5.txt");
    ofstream fout("../data/output/out5.txt");
    string line;
    fin >> line;
    double x0;
    double x1;
    double h1;
    double h2;
    fin >> x0 >> x1 >> h1 >> h2;
    MethodIntegral method(x0, x1, h1);
    
    fout << "Метод 5: Численное интегрирование\n";
    fout << "Функция:" << line;
    fout << "x0=" << x0 << "\n";
    fout << "x1=" << x1 << "\n";
    
    double rect1 = method.rectangle();
    
    fout << "h1=" << h1 << "\n";
    fout << "Прямоугольник: " << rect1 << "\n";
    
    method.setH(h2);
    
    double rect2 = method.rectangle();
    double rectError = rect1 + rungeRomberg(h1, h2, rect1, rect2, 2.0);
    
    fout << "h2=" << h2 << "\n";
    fout << "Прямоугольник: " << rect2 << "\n";
    fout << "Уточнение методом Рунге-Ромберга: " << rectError << "\n";
    
    method.setH(h1);
    
    double trap1 = method.trapezoidal();
    
    fout << "h1=" << h1 << "\n";
    fout << "Трапеция: " << trap1 << "\n";
    
    method.setH(h2);
    
    double trap2 = method.trapezoidal();
    double trapError = trap1 + rungeRomberg(h1, h2, trap1, trap2, 2.0);
    
    fout << "h2=" << h2 << "\n";
    fout << "Трапеция: " << trap2 << "\n";
    fout << "Уточнение методом Рунге-Ромберга: " << trapError << "\n";
    
    method.setH(h1);
    
    double simp1 = method.simpson();
    
    fout << "h1=" << h1 << "\n";
    fout << "Симпсон: " << simp1 << "\n";
    
    method.setH(h2);
    
    double simp2 = method.simpson();
    double simpError = simp1 + rungeRomberg(h1, h2, simp1, simp2, 2.0);
    
    fout << "h2=" << h2 << "\n";
    fout << "Симпсон: " << simp2 << "\n";
    fout << "Уточнение методом Рунге-Ромберга: " << simpError << "\n";
    
    fout.close();
    fin.close();
}