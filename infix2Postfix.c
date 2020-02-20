/************************************************************************************************
 * infix2Postfix
 * @author: Carlos Huerta García
 * @description: Receives an infix expression and displays the postfix expression and its result
 * *********************************************************************************************/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "charStack.h"
#include "intStack.h"
#include "Operator.h"

void infixToPostfix(const char* infix_expression, char postfix_expression[]) {
    char aux[] = {' ', '\0'};
    Stack* stack_application = createStack();
    int i;
    for (i = 0; i < strlen(infix_expression); i++) {
        if(isalnum(infix_expression[i])){ //number or letter
            aux[0] = infix_expression[i];
            strcat(postfix_expression, aux);
            continue;
        }
        if(infix_expression[i] == '('){ //is (
            push(infix_expression[i], stack_application);
            continue;
        } 
        if(infix_expression[i] == ')'){ //is )
            while(!isEmpty(stack_application) && ((aux[0] = pop(stack_application)) != '(')) {
                strcat(postfix_expression, aux);
            }
            continue;
        }
        if(infix_expression[i] == '['){ //is [
            push(infix_expression[i], stack_application);
            continue;
        } 
        if(infix_expression[i] == ']'){ //is ]
            while(!isEmpty(stack_application) && ((aux[0] = pop(stack_application)) != '[')) {
                strcat(postfix_expression, aux);
            }
            continue;
        }
        if(infix_expression[i] == '{'){ //is {
            push(infix_expression[i], stack_application);
            continue;
        } 
        if(infix_expression[i] == '}'){ //is }
            while(!isEmpty(stack_application) && ((aux[0] = pop(stack_application)) != '{')) {
                strcat(postfix_expression, aux);
            }
            continue;
        }
        if(isOperator(infix_expression[i])){ //isOperator
            while(!isEmpty(stack_application) && (operatorPrecedence(peek(stack_application)) >= operatorPrecedence(infix_expression[i]))){ 
                aux[0] = pop(stack_application);
                strcat(postfix_expression, aux);
            }
            push(infix_expression[i], stack_application);
        }
    }
    while(!isEmpty(stack_application)){
        aux[0] = pop(stack_application);
        strcat(postfix_expression, aux);
    }
    clear(stack_application);
    free(stack_application);
}



int postfixResult(const char* postfix_expression) {
    iStack* stack_application = createiStack();
    int a, b, i;
    char aux[2] = {' ', '\0'};
    for (i = 0; i < strlen(postfix_expression); i++) {
        if(isdigit(postfix_expression[i])){
            aux[0] = postfix_expression[i];
            pushi((int)atoi(aux), stack_application);
        }
        if(isOperator(postfix_expression[i])){
            b = popi(stack_application);
            a = popi(stack_application);
            pushi(calculate(a, postfix_expression[i], b), stack_application);
        }
        if(isalpha(postfix_expression[i])){
            return INT_MIN;
        }
    }
    i = peeki(stack_application);
    cleari(stack_application);
    free(stack_application);
    return i;
}

void main() {
    puts("\ninfix2Postfix\n@author: Carlos Huerta Garcia\nDescription: Receives an infix expression and displays the postfix expression and its result\n\nEnter an infix expression with operands from 0 to 9 and parentheses only:");
    char* infix_expression;
    gets(infix_expression);
    char postfix_expression[] ={' '};
    infixToPostfix(infix_expression, postfix_expression);
    printf("\nPostfix expression: %s\n\n", postfix_expression);
    int result = postfixResult(postfix_expression);
    if(result != INT_MIN)
        printf("Result: %d\n", result);
}
