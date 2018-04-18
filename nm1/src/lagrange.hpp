
package libnm.math.polynom;

import libnm.math.Vector;
import libnm.math.expression.ExpTree;

public class PolynomLagrange
{
    private Vector m_vecX;
    private Vector m_vecY;
    
    public PolynomLagrange(Vector vecX, ExpTree expr)
    {
        this.m_vecX = vecX;
        this.m_vecY = new Vector(this.m_vecX.getSize());
        Vector vecW = new Vector(this.m_vecX.getSize());
        
        int i;
        for (i = 0; i < this.m_vecX.getSize(); ++i) {
            this.m_vecY.set(i, expr.setVar("x", this.m_vecX.get(i)).calculate());
        }
        
        for (i = 0; i < this.m_vecX.getSize(); ++i) {
            double w = 1.0D;
            
            for (int j = 0; j < this.m_vecX.getSize(); ++j) {
                if (i != j) {
                    w *= this.m_vecX.get(i) - this.m_vecX.get(j);
                }
            }
            
            vecW.set(i, w);
        }
        
        for (i = 0; i < this.m_vecX.getSize(); ++i) {
            this.m_vecY.set(i, this.m_vecY.get(i) / vecW.get(i));
        }
        
    }
    
    public double getValue(double x)
    {
        int n = this.m_vecX.getSize();
        double res = 0.0D;
        
        for (int i = 0; i < n; ++i) {
            double w = 1.0D;
            
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    w *= x - this.m_vecX.get(j);
                }
            }
            
            res += this.m_vecY.get(i) * w;
        }
        
        return res;
    }
    
    public String toString()
    {
        int n = this.m_vecX.getSize();
        String res = String.valueOf(this.m_vecY.get(0));
        
        int i;
        for (i = 1; i < n; ++i) {
            res = res + "(x-" + this.m_vecX.get(i) + ")";
        }
        
        for (i = 1; i < n; ++i) {
            if (this.m_vecY.get(i) >= 0.0D) {
                res = res + "+";
            }
            
            res = res + this.m_vecY.get(i);
            
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    res = res + "(x-" + this.m_vecX.get(j) + ")";
                }
            }
        }
        
        return res;
    }
}
