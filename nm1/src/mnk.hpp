//
// Source code recreated from a .class file by IntelliJ IDEA
// (powered by Fernflower decompiler)
//

package libnm.math.polynom;

import libnm.math.Matrix;
import libnm.math.Vector;
import libnm.math.method.MethodSle;

public class PolynomMNK
{
    private Vector m_vecX;
    private Vector m_vecY;
    private Polynom m_poly;
    
    public PolynomMNK(Vector vecX, Vector vecY, int degree)
    {
        int n = vecX.getSize();
        int m = degree + 1;
        int sumCnt = degree * 2 + 1;
        double[] sumsMat = new double[sumCnt];
        double[] sumsVec = new double[m];
        Matrix mat = new Matrix(m);
        Vector vec = new Vector(m);
        Vector vecA = new Vector(m);
        MethodSle method = new MethodSle();
        this.m_vecX = vecX;
        this.m_vecY = vecY;
        
        int i;
        int j;
        for (i = 0; i < sumCnt; ++i) {
            for (j = 0; j < n; ++j) {
                sumsMat[i] += Math.pow(this.m_vecX.get(j), (double)i);
            }
        }
        
        for (i = 0; i < m; ++i) {
            for (j = 0; j < n; ++j) {
                sumsVec[i] += this.m_vecY.get(j) * Math.pow(this.m_vecX.get(j), (double)i);
            }
        }
        
        for (i = 0; i < m; ++i) {
            for (j = 0; j < m; ++j) {
                mat.set(i, j, sumsMat[i + j]);
            }
        }
        
        for (i = 0; i < m; ++i) {
            vec.set(i, sumsVec[i]);
        }
        
        method.lup(mat, vec, vecA);
        this.m_poly = new Polynom(vecA);
    }
    
    public double getSumOfSquares()
    {
        double res = 0.0D;
        
        for (int i = 0; i < this.m_vecX.getSize(); ++i) {
            res += Math.pow(this.m_poly.getValue(this.m_vecX.get(i)) - this.m_vecY.get(i), 2.0D);
        }
        
        return res;
    }
    
    public double getValue(double x)
    {
        return this.m_poly.getValue(x);
    }
    
    public String toString()
    {
        return this.m_poly.toString();
    }
}
