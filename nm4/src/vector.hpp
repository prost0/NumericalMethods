#ifndef __VECTOR__
#define __VECTOR__

#include <vector>
#include <cmath>
#include <fstream>

#define MAX_ITERATIONS 1000

using namespace std;

vector <double> vecAdd(vector <double> a, vector <double> b);
vector <double> vecSub(vector <double> a, vector <double> b);
double vecNormC(vector <double> v);
void inputVec(vector <double> &vec, ifstream &ifs);
void printVec(vector <double> &vec, ofstream &ofs);

#endif