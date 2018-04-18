//
// Source code recreated from a .class file by IntelliJ IDEA
// (powered by Fernflower decompiler)
//

package libnm.math.method;

import libnm.math.Vector;

public class MethodDerivate
{
    private Vector m_vecX;
    private Vector m_vecY;
    private double m_x;
    
    public MethodDerivate(Vector vecX, Vector vecY, double x)
    {
        this.m_vecX = vecX;
        this.m_vecY = vecY;
        this.m_x = x;
    }
    
    public double deriv1()
    {
        int i = 0;
        double res = 0.0D;
        
        for (int j = 0; j < this.m_vecX.getSize(); ++j) {
            if (this.m_vecX.get(j) == this.m_x) {
                i = j;
                break;
            }
        }
        
        res += (this.m_vecY.get(i + 1) - this.m_vecY.get(i)) / (this.m_vecX.get(i + 1) - this.m_vecX.get(i));
        res -= (this.m_vecY.get(i) - this.m_vecY.get(i - 1)) / (this.m_vecX.get(i) - this.m_vecX.get(i - 1));
        res /= this.m_vecX.get(i + 1) - this.m_vecX.get(i - 1);
        res *= 2.0D * this.m_x - this.m_vecX.get(i - 1) - this.m_vecX.get(i);
        res += (this.m_vecY.get(i) - this.m_vecY.get(i - 1)) / (this.m_vecX.get(i) - this.m_vecX.get(i - 1));
        return res;
    }
    
    public double deriv2()
    {
        int i = 0;
        double res = 0.0D;
        
        for (int j = 0; j < this.m_vecX.getSize(); ++j) {
            if (this.m_vecX.get(j) == this.m_x) {
                i = j;
                break;
            }
        }
        
        res += (this.m_vecY.get(i + 1) - this.m_vecY.get(i)) / (this.m_vecX.get(i + 1) - this.m_vecX.get(i));
        res -= (this.m_vecY.get(i) - this.m_vecY.get(i - 1)) / (this.m_vecX.get(i) - this.m_vecX.get(i - 1));
        res /= this.m_vecX.get(i + 1) - this.m_vecX.get(i - 1);
        res *= 2.0D;
        return res;
    }
}
