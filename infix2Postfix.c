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

void infixToPostfix(const char * infix_expression, char postfix_expression[]) {
    char aux[] = {' ', '\0'};
    Stack * stack_application = createStack();
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

void infix2Prefix(const char * infix_expression, char tmp[], char prefix_expression[]){
    int i;
    char aux[] = {' ', '\0'}, prefix_tmp[] = "";
    Stack * stack_application = createStack();
    for (i = 0; i < strlen(infix_expression); i++)
        push(infix_expression[i], stack_application);
    while(!isEmpty(stack_application)){
        aux[0] = pop(stack_application);
        strcat(prefix_expression, aux);
    } // Reversed infix expression
    for (i = 0; i < strlen(prefix_expression); i++){
        if(prefix_expression[i] == '(')
            prefix_expression[i] = ')';
        if(prefix_expression[i] == ')')
            prefix_expression[i] = '(';
        if(prefix_expression[i] == '[')
            prefix_expression[i] = ']';
        if(prefix_expression[i] == ']')
            prefix_expression[i] = '[';
        if(prefix_expression[i] == '{')
            prefix_expression[i] = '}';
        if(prefix_expression[i] == '}')
            prefix_expression[i] = '{';
    } // fix agrupation order
    infixToPostfix(prefix_expression, prefix_tmp); // Postfix reversed expression
    for(i = 0; prefix_tmp[i] != '\0'; i++)
        push(prefix_tmp[i], stack_application);
    aux[1] = '\0';
    for (i = 0; !isEmpty(stack_application); i++){
        aux[0] = pop(stack_application);
        strcat(tmp, aux);
    } // Reversed postfix reversed expression
    clear(stack_application);
    free(stack_application);
}

int postfixResult(const char * postfix_expression) {
    iStack * stack_application = createiStack();
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
    i = popi(stack_application);
    cleari(stack_application);
    free(stack_application);
    return i;
}

int prefixResult(const char * prefix_expression) {
    iStack * stack_application = createiStack();
    int a, b, i;
    char aux[] = {' ', '\0'};
    for (i = strlen(prefix_expression) - 1; i >= 0; i--) {
        if(isdigit(prefix_expression[i])){
            aux[0] = prefix_expression[i];
            pushi((int)atoi(aux), stack_application);
        }
        if(isOperator(prefix_expression[i])){
            b = popi(stack_application);
            a = popi(stack_application);
            pushi(calculate(a, prefix_expression[i], b), stack_application);
        }
        if(isalpha(prefix_expression[i])){
            return INT_MIN;
        }
    }
    i = popi(stack_application);
    cleari(stack_application);
    free(stack_application);
    return i;
}

void infix2PostfixNPrefix(const char * infix_expression) {
    char postfix_expression[] = "", prefix_expression[] = "", tmp[] = "";
    infixToPostfix(infix_expression, postfix_expression);
    printf("\nPostfix expression: %s\n\n", postfix_expression);
    int result = postfixResult(postfix_expression);
    if(result != INT_MIN)
        printf("Postfix Result: %d\n", result);
    infix2Prefix(infix_expression, tmp, prefix_expression);
    printf("\nPrefix expression: %s\n\n", tmp);
    result = prefixResult(tmp);
    if(result != INT_MIN)
        printf("Prefix Result: %d\n", result);
}

void main() {
    puts("\ninfix2Postfix\n@author: Carlos Huerta Garcia\nDescription: Receives an infix expression and displays the postfix expression and its result\n\nEnter an infix expression with operands from 0 to 9 and parentheses only:");
    char* infix_expression;
    gets(infix_expression);
    infix2PostfixNPrefix(infix_expression);
}
