#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

bool isOperator(char c) {
    return (c > 41) && (c < 44) || c == '-' || c == '/' || c == '^';
}

int operatorPrecedence(char op) {
    if (isOperator(op)) {
        if(op == '{' || op == '}')
            return 6;
        if(op == '[' || op == ']')
            return 5;
        if(op == '(' || op == ')')
            return 4;
        if (op == '^')
            return 3;
        if (op == '/' || op == '*')
            return 2;
        if (op == '+' || op == '-')
            return 1;
    }
    return 0;
}

int calculate(int a, char op, int b) {
    switch (op) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    case '^':
        return pow(a, b);
    default:
        puts("Not an operator");
        return INT_MIN;
    }
}
