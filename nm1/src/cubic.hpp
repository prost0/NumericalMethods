//
// Source code recreated from a .class file by IntelliJ IDEA
// (powered by Fernflower decompiler)
//

package libnm.math.polynom;

import libnm.math.Matrix;
import libnm.math.Vector;
import libnm.math.method.MethodSle;

public class PolynomCubic
{
    private Vector m_vecX;
    private Vector m_vecA;
    private Vector m_vecB;
    private Vector m_vecC;
    private Vector m_vecD;
    
    public PolynomCubic(Vector vecX, Vector vecY)
    {
        int n = vecX.getSize();
        Matrix mat = new Matrix(n - 2);
        Vector vec = new Vector(n - 2);
        MethodSle method = new MethodSle();
        Vector vecH = new Vector(n - 1);
        this.m_vecX = vecX;
        this.m_vecA = new Vector(n - 1);
        this.m_vecB = new Vector(n - 1);
        this.m_vecC = new Vector(n - 1);
        this.m_vecD = new Vector(n - 1);
        
        int i;
        for (i = 0; i < n - 1; ++i) {
            vecH.set(i, this.m_vecX.get(i + 1) - this.m_vecX.get(i));
        }
        
        for (i = 0; i < n - 2; ++i) {
            vec.set(i, 3.0D * ((vecY.get(i + 2) - vecY.get(i + 1)) / vecH.get(i) - (vecY.get(i + 1) - vecY.get(i)) / vecH.get(i + 1)));
        }
        
        mat.set(0, 0, 2.0D * (vecH.get(0) + vecH.get(1)));
        mat.set(0, 1, vecH.get(1));
        
        for (i = 1; i < n - 3; ++i) {
            mat.set(i, i - 1, vecH.get(i - 1));
            mat.set(i, i, 2.0D * (vecH.get(i - 1) + vecH.get(i)));
            mat.set(i, i + 1, vecH.get(i));
        }
        
        mat.set(n - 3, n - 4, vecH.get(n - 3));
        mat.set(n - 3, n - 3, 2.0D * (vecH.get(n - 4) + vecH.get(n - 3)));
        method.tma(mat, vec, this.m_vecC, false);
        
        for (i = n - 2; i > 0; --i) {
            this.m_vecC.set(i, this.m_vecC.get(i - 1));
        }
        
        this.m_vecC.set(0, 0.0D);
        
        for (i = 0; i < n - 1; ++i) {
            this.m_vecA.set(i, vecY.get(i));
        }
        
        for (i = 0; i < n - 2; ++i) {
            double h = vecH.get(i);
            this.m_vecB.set(i, (vecY.get(i + 1) - vecY.get(i)) / h - h * (this.m_vecC.get(i + 1) + 2.0D * this.m_vecC.get(i)) / 3.0D);
            this.m_vecD.set(i, (this.m_vecC.get(i + 1) - this.m_vecC.get(i)) / (3.0D * h));
        }
        
        double h = vecH.get(n - 2);
        this.m_vecB.set(n - 2, (vecY.get(n - 1) - vecY.get(n - 2)) / h - 2.0D * h * this.m_vecC.get(n - 2) / 3.0D);
        this.m_vecD.set(n - 2, -this.m_vecC.get(n - 2) / (3.0D * h));
    }
    
    public double getValue(double x)
    {
        for (int i = 0; i < this.m_vecX.getSize() - 1; ++i) {
            if (this.m_vecX.get(i) <= x && x <= this.m_vecX.get(i + 1)) {
                double h = x - this.m_vecX.get(i);
                return this.m_vecA.get(i) + this.m_vecB.get(i) * h + this.m_vecC.get(i) * Math.pow(h, 2.0D) + this.m_vecD.get(i) * Math.pow(h, 3.0D);
            }
        }
        
        return 0.0D;
    }
    
    public String toString()
    {
        int n = this.m_vecX.getSize();
        String res = "";
        
        for (int i = 0; i < n - 1; ++i) {
            String strH = "(x-" + this.m_vecX.get(i) + ")";
            res = res + "S(" + (i + 1) + ")=";
            res = res + this.m_vecA.get(i);
            if (this.m_vecB.get(i) >= 0.0D) {
                res = res + "+";
            }
            
            res = res + this.m_vecB.get(i) + strH + "^1";
            if (this.m_vecC.get(i) >= 0.0D) {
                res = res + "+";
            }
            
            res = res + this.m_vecC.get(i) + strH + "^2";
            if (this.m_vecD.get(i) >= 0.0D) {
                res = res + "+";
            }
            
            res = res + this.m_vecD.get(i) + strH + "^3";
            if (i + 1 < n - 1) {
                res = res + "\n";
            }
        }
        
        return res;
    }
}
