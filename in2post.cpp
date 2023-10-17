#include "stack.h"
#include<iostream>
#include<string>
#include <cstring>
#include <cmath>
#include <regex>
#include <sstream>
#include <fstream>


using namespace std;
using namespace cop4530;


using namespace std;


int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    return 0;
}

double applyOp(char op, double b, double a) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    case '^': return pow(a, b);
    }
    return 0;
}

bool isOperand(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

string evaluatePostfix(string exp) {
    stack<double> st;
    string result = "";
    for (int i = 0; i < exp.length(); i++) {
        
        if (exp[i] == ' ')
            continue;
        else if (isdigit(exp[i])) {
            double num = 0;
            while (isdigit(exp[i])) {
                num = num * 10 + (double)(exp[i] - '0');
                i++;
            }
            i--;
            st.push(num);
        }
        else {
            if (st.size() < 2) {
                // If there are less than 2 operands in the stack,
                // the expression is invalid, so return the original postfix string
                return exp;
            }
            double b = st.top();
            st.pop();
            double a = st.top();
            st.pop();
            double res = applyOp(exp[i], b, a);
            st.push(res);
        }
    }
    if (st.size() == 1) {
        // If there is exactly one operand in the stack,
        // return it as a string
        result = to_string(st.top());
    } else {
        // If there are more than one operands in the stack,
        // the expression is invalid, so return the original postfix string
        result = exp;
    }
    return result;
}


string infixToPostfix(string exp) {
    string postfix = "";
    stack<char> st;
    for (int i = 0; i < exp.length(); i++) {
        if (exp[i] == ' ')
            continue;
        else if (isdigit(exp[i])) {
            while (isdigit(exp[i])) {
                postfix += exp[i];
                i++;
            }
            i--;
            postfix += ' ';
        }
        else if (isOperand(exp[i])) {
            postfix += exp[i];
            postfix += ' ';
        }
        else {
            if (exp[i] == '(') {
                st.push(exp[i]);
            } else if (exp[i] == ')') {
                while (!st.empty() && st.top() != '(') {
                    postfix += st.top();
                    st.pop();
                    postfix += ' ';
                }
                if (st.empty()) {
                    // Mismatched parentheses
                    return "";
                }
                st.pop();
            } else {
                // Operator
                while (!st.empty() && precedence(st.top()) >= precedence(exp[i])) {
                    postfix += st.top();
                    st.pop();
                    postfix += ' ';
                }
                st.push(exp[i]);
            }
        }
    }
    while (!st.empty()) {
        postfix += st.top();
        st.pop();
        postfix += ' ';
    }
    return postfix;
}


int main(int argc, char *argv[]) {


    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input file>" << endl;
        return 1;
    }
    ifstream infile(argv[1]);
    if (!infile.is_open()) {
        cerr << "Error: Could not open file '" << argv[1] << "'" << endl;
        return 1;
    }
    string infix;
    while (getline(infile, infix)) {
        string postfix = infixToPostfix(infix);
        //cout << postfix << endl;
        cout << evaluatePostfix(postfix) << endl;
    }
    infile.close();
    /*
    string infix = "( 5 + 3 ) * ( ) + 12 - 7 ";
    string postfix = infixToPostfix(infix);
    cout << evaluatePostfix(postfix) << endl;
    */
    return 0;

}