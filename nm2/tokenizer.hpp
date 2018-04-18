#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <stack>
#include <regex>
#include <vector>
#include "expTreeNode.hpp"

using namespace std;

class Tokenizer
{
    Tokenizer()
    {
        vector <regex> m_patterns;
        m_patterns.push_back(regex("^(arcsin|arccos|arctg|arcctg|sin|cos|tg|ctg|sqrt|abs|ln)"));
        m_patterns.push_back(regex("^[a-z]+[0-9]*"));
        m_patterns.push_back(regex("^[0-9]+(\\.[0-9]+)?"));
        m_patterns.push_back(regex("^[\\+\\-]"));
        m_patterns.push_back(regex("^[*/]"));
        m_patterns.push_back(regex("^[\\^]"));
        m_patterns.push_back(regex("^[\\(]"));
        m_patterns.push_back(regex("^[\\)]"));
    }
    
    stack <ExpTreeNode *> getTokens(string str)
    {
        int pos = 0;
        stack<ExpTreeNode *> stackOp;
        stack<ExpTreeNode *> stackRes;
        ExpTreeNode *prevToken = null;
        
        while (true) {
            ExpTreeNode *token = m_getToken(str, pos);
            
            if (token == null) {
                if (pos < str.length()) {
                    System.out.println("Syntax error in column: " + pos);
                    
                    return null;
                }
                
                break;
            }
            
            if (token->getValue().equals("-") && (prevToken == null || isOpenBracket(prevToken))) {
                token->setSign(true);
            }
            
            if (isTerm(token)) {
                stackRes.push(token);
            } else {
                while (!stackOp.empty()) {
                    ExpTreeNode *topNode = stackOp.peek();
                    
                    if (m_isHigher(topNode, token) && !isOpenBracket(topNode)) {
                        stackRes.push(topNode);
                        stackOp.pop();
                    } else {
                        break;
                    }
                }
                
                stackOp.push(token);
                
                if (isCloseBracket(stackOp.peek())) {
                    stackOp.pop();
                    stackOp.pop();
                }
            }
            
            pos += token->getValue().length();
            prevToken = token;
        }
        
        while (!stackOp.empty()) {
            stackRes.push(stackOp.peek());
            stackOp.pop();
        }
        
        return stackRes;
    }
    
    static bool isFunc(ExpTreeNode *root)
    {
        return root->getType() == FUNCTION;
    }
    
    static bool isVar(ExpTreeNode *root)
    {
        return root->getType() == VARIABLE;
    }
    
    static bool isVal(ExpTreeNode *root)
    {
        return root->getType() == VALUE;
    }
    
    static bool isPlusMinus(ExpTreeNode *root)
    {
        return root->getType() == PLUSMINUS;
    }
    
    static bool isMulDiv(ExpTreeNode *root)
    {
        return root->getType() == MULDIV;
    }
    
    static bool isPower(ExpTreeNode *root)
    {
        return root->getType() == POWER;
    }
    
    static bool isOpenBracket(ExpTreeNode *root)
    {
        return root->getType() == OPEN_BRACKET;
    }
    
    static bool isCloseBracket(ExpTreeNode *root)
    {
        return root->getType() == CLOSE_BRACKET;
    }
    
    static bool isTerm(ExpTreeNode *root)
    {
        return isVar(root) || isVal(root);
    }
    
    static bool isOp(ExpTreeNode *root)
    {
        return isPlusMinus(root) || isMulDiv(root) || isPower(root);
    }
    
private:

    ExpTreeNode *m_getToken(string str, int start)
    {
        for (int i = 0; i < m_patterns.size(); ++i) {
            string substring = str.substr(start);
            Matcher m = regex_match(substring.begin(), substring.end() , m_patterns[i]);
            
            if (m.find()) {
                return new ExpTreeNode(m.group(), i, false);
            }
        }
        
        return null;
    }
    
    bool m_isHigher(ExpTreeNode *node1, ExpTreeNode *node2)
    {
        if (isPower(node1) && isPower(node2)) {
            return false;
        } else if (isOpenBracket(node2)) {
            return false;
        }
        
        return m_priority(node1) >= m_priority(node2);
    }
    
    int m_priority(ExpTreeNode *node)
    {
        if (isFunc(node)) {
            return 4;
        } else if (isPower(node)) {
            return 3;
        } else if (isMulDiv(node)) {
            return 2;
        } else if (isPlusMinus(node)) {
            return 1;
        }
        
        return 0;
    }
    
    static final int FUNCTION = 0;
    static final int VARIABLE = 1;
    static final int VALUE = 2;
    static final int PLUSMINUS = 3;
    static final int MULDIV = 4;
    static final int POWER = 5;
    static final int OPEN_BRACKET = 6;
    static final int CLOSE_BRACKET = 7;
    
    vector <regex> m_patterns;
}