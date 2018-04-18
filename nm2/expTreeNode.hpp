#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <stack>
#include <string>

using namespace std;

class ExpTreeNode
{
    ExpTreeNode(string value, int type, bool sign)
    {
        m_sign = sign;
        m_type = type;
        m_value = value;
        m_left = nullptr;
        m_right = nullptr;
    }
    
    int getType()
    {
        return m_type;
    }
    
    void setType(int type)
    {
        m_type = type;
    }
    
    bool getSign()
    {
        return m_sign;
    }
    
    void setSign(bool sign)
    {
        m_sign = sign;
    }
    
    string getValue()
    {
        return m_value;
    }
    
    void setValue(string value)
    {
        m_value = value;
    }
    
    ExpTreeNode *getLeft()
    {
        return m_left;
    }
    
    void setLeft(ExpTreeNode *left)
    {
        m_left = left;
    }
    
    ExpTreeNode *getRight()
    {
        return m_right;
    }
    
    void setRight(ExpTreeNode *right)
    {
        m_right = right;
    }
    
private:
    bool is_null;
    int m_type;
    bool m_sign;
    string m_value;
    ExpTreeNode *m_left;
    ExpTreeNode *m_right;
};