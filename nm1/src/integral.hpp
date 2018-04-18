//
// Source code recreated from a .class file by IntelliJ IDEA
// (powered by Fernflower decompiler)
//

package libnm.math.method;

import libnm.math.expression.ExpTree;

public class MethodIntegral
{
    private ExpTree m_expr;
    private double m_x0;
    private double m_x1;
    private double m_h;
    
    public MethodIntegral(ExpTree expr, double x0, double x1, double h)
    {
        this.m_expr = expr;
        this.m_x0 = x0;
        this.m_x1 = x1;
        this.m_h = h;
    }
    
    public double rectangle()
    {
        double res = 0.0D;
        
        for (double x = this.m_x0 + this.m_h; x <= this.m_x1; x += this.m_h) {
            res += this.m_expr.setVar("x", (2.0D * x - this.m_h) / 2.0D).calculate();
        }
        
        return res * this.m_h;
    }
    
    public double trapezoidal()
    {
        double res = this.m_expr.setVar("x", this.m_x0).calculate() / 2.0D;
        
        for (double x = this.m_x0 + this.m_h; x <= this.m_x1 - this.m_h; x += this.m_h) {
            res += this.m_expr.setVar("x", x).calculate();
        }
        
        res += this.m_expr.setVar("x", this.m_x1).calculate() / 2.0D;
        return res * this.m_h;
    }
    
    public double simpson()
    {
        double res = this.m_expr.setVar("x", this.m_x0).calculate();
        boolean isTwo = false;
        
        for (double x = this.m_x0 + this.m_h; x <= this.m_x1 - this.m_h; x += this.m_h) {
            res += this.m_expr.setVar("x", x).calculate() * (isTwo ? 2.0D : 4.0D);
            isTwo = !isTwo;
        }
        
        res += this.m_expr.setVar("x", this.m_x1).calculate();
        return res * this.m_h / 3.0D;
    }
    
    public void setH(double h)
    {
        this.m_h = h;
    }
}
