#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
using namespace std;


void simpleIteration(vector <double> &vecPrev, vector <double> &vecX, double eps, double q)
{
    int n = exprs.length;
    int iterCnt = 1;
    
    while (true) {
        vector <double> vecTmp = new vector <double>(n);
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                exprs[i].setVar("x" + (j + 1), vecPrev.get(j));
            }
            
            vecTmp.set(i, exprs[i].calculate());
        }
        
        vecX.copy(vecTmp);
        
        if (m_logger != null) {
            m_logger.writeln("Итерация #" + iterCnt + ": " + vecX);
        }
        
        if (vecX.sub(vecPrev).normC() * q / (1.0 - q) <= eps) {
            break;
        }
        
        vecPrev.copy(vecX);
        ++iterCnt;
    }
}

void newton(vector <double> &vecPrev, vector <double> &vecX, double eps)
{
    int n = exprs.length;
    int iterCnt = 1;
    TExpTree[][] matJ = new TExpTree[n][n];
    MethodSle method = new MethodSle();
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matJ[i][j] = exprs[i].derivateBy("x" + (j + 1));
        }
    }
    
    while (true) {
        Matrix mat = new Matrix(n);
        vector <double> vec = new vector <double>(n);
        vector <double> vecDelta = new vector <double>(n);
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    matJ[i][j].setVar("x" + (k + 1), vecPrev.get(k));
                }
                
                mat.set(i, j, matJ[i][j].calculate());
                exprs[i].setVar("x" + (j + 1), vecPrev.get(j));
            }
            
            vec.set(i, -exprs[i].calculate());
        }
        
        method.lup(mat, vec, vecDelta);
        vecX.copy(vecPrev.add(vecDelta));
        
        if (m_logger != null) {
            m_logger.writeln("Итерация #" + iterCnt + ": " + vecX);
        }
        
        if (vecX.sub(vecPrev).normC() <= eps) {
            break;
        }
        
        vecPrev.copy(vecX);
        ++iterCnt;
    }
}


void method11()
{
    m_method1("src/data/input/in11.txt", "src/data/output/out11.txt");
}

void method12()
{
    m_method2("src/data/input/in12.txt", "src/data/output/out12.txt");
}

void method21()
{
    m_method1("src/data/input/in21.txt", "src/data/output/out21.txt");
}

void method22()
{
    m_method2("src/data/input/in22.txt", "src/data/output/out22.txt");
}

void m_method1(string inputName, string outputName)
{
    ifstream fin(inputName);
    ofstream fout(outputName);
    int n;
    double a, q, eps;
    fin >> n >> a >> q >> eps;
    
    vector <double> vec(n);
    inputVec(vec, fin);
    vector <double> vecX(n);
    //TExpTree[] exprs = new TExpTree[n];
    
    fout << "Метод 1: Метод простой итерации\n";
    
    // for (int i = 0; i < n; ++i) {
    //     exprs[i] = new TExpTree(reader.readLine());
    //     exprs[i].setVar("a", a);
    // }
    
    simpleIteration(exprs, vec, vecX, eps, q);
    
    fout << "Решение: ";
    printVec(vecX, fout);
    
}

void m_method2(string inputName, string outputName)
{
    ifstream fin(inputName);
    ofstream fout(outputName);
    int n;
    double a, eps;
    fin >> n >> a >> eps;
    
    vector <double> vec(n);
    inputVec(vec, fin);
    vector <double> vecX(n);
    TExpTree[] exprs = new TExpTree[n];
    
    output.writeln("Метод 2: Метод Ньютона");
    
    for (int i = 0; i < n; ++i) {
        exprs[i] = new TExpTree(reader.readLine());
        exprs[i].setVar("a", a);
    }
    
    m_method.setLogger(logger);
    m_method.newton(exprs, vec, vecX, eps);
    
    cout << "Решение: ";
    printVec(vecX, fout);
    // output.close();
    // logger.close();
    // reader.close();
}