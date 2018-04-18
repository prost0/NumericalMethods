#ifndef __POLYNOM__
#define __POLYNOM__

#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include "matrix.hpp"
#include "vector.hpp"

public class Polynom extends Vector
{
    public Polynom(Vector vecX)
    {
        super(vecX.getSize());
        
        for (int i = 0; i < vecX.getSize(); ++i) {
            this.set(i, vecX.get(i));
        }
        
    }
    
    public double getValue(double x)
    {
        double res = 0.0D;
        
        for (int i = 0; i < this.getSize(); ++i) {
            res += this.get(i) * Math.pow(x, (double)i);
        }
        
        return res;
    }
    
    public String toString()
    {
        String res = String.valueOf(this.get(0));
        
        for (int i = 1; i < this.getSize(); ++i) {
            if (this.get(i) >= 0.0D) {
                res = res + "+";
            }
            
            res = res + this.get(i) + "x^" + i;
        }
        
        return res;
    }
}
#endif