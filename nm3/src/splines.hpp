#ifndef __SPLINES__
#define __SPLINES__

#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>
#include "matrix.hpp"
#include "vector.hpp"
#include "lagrange.hpp"
#include "newton.hpp"
#include "cubic.hpp"
#include "mnk.hpp"
#include "derivate.hpp"
#include "integral.hpp"
#include "error.hpp"
using namespace std;

void m_lagrangeNewton(string inputName, string outputName);
void lagrangeNewton();
void cubic();
void mnk();
void derivate();
void integral();
#endif