#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <fstream>

class Complex
{
public:
    Complex()
    {
        m_re = 0;
        m_im = 0;
    }
    
    Complex(double re, double im)
    {
        m_re = re;
        m_im = im;
    }
    
    double getRe()
    {
        return m_re;
    }
    
    void setRe(double re)
    {
        m_re = re;
    }
    
    double getIm()
    {
        return m_im;
    }
    
    void setIm(double im)
    {
        m_im = im;
    }
    
    Complex sub(Complex other)
    {
        return Complex(m_re - other.getRe(), m_im - other.getIm());
    }
    
    double abs()
    {
        return sqrt(pow(m_re, 2.0) + pow(m_im, 2.0));
    }
    
    
    // std::string toString()
    // {
    //     std::string res = string.valueOf(m_re);
    
    //     if (m_im != 0.0) {
    //         if (m_im > 0.0) {
    //             res += "+";
    //         }
    
    //         res += m_im + "*i";
    //     }
    
    //     return res;
    // }
    
private:
    double m_re;
    double m_im;
};