#pragma once
#include <iostream>
#include <sstream>
#include <cmath>
#include <stdlib.h>
#include "Stack.h"

#define pi 3.14159265358979323846
#define Exp 2.71828182845904523536

using namespace std;


class calc {
private:
	string infix;
	Stack operators;
	Stack outstream;
    Stack result;
public:
    calc()
    {
        this->infix = "";
    }

    calc(string expr)
    {
        if (expr.size() == 0)
        {
            throw "Expression is empty";
        }
        this->infix = expr;
    }

    void readExpression();
    void printExpression();
    string getExpression();
    bool inputCheck();
    bool minusCheck(string, size_t);
    int precedence(string);
    void infixToPostfix();
    double calculate();
};