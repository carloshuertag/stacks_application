/************************************************************************************************
 * stacks_application
 * @author: Carlos Huerta García
 * @description: Receives an infix expression and displays the postfix expression and its result
 * *********************************************************************************************/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>

typedef char StackEntry;

typedef struct StackElement {
    StackEntry entry;
    struct StackElement* next;
} StackElement;

typedef struct StackInt {
    int entry;
    struct StackInt* next;
} StackInt;

typedef struct Stack {
    StackElement* top;
} Stack;

typedef struct intStack {
    StackInt* top;
} intStack;

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

intStack* createiStack() {
    intStack* stack = (intStack*)malloc(sizeof(intStack));
    stack->top = NULL;
    return stack;
}

StackElement* createElement(StackEntry item) {
    StackElement* element = (StackElement*)malloc(sizeof(StackElement));
    if (element == NULL) {
        puts("Error at creating element");
        exit(1);
    }
    element->entry = item;
    element->next = NULL;
    return element;
}

StackInt* createInt(int item) {
    StackInt* element = (StackInt*)malloc(sizeof(StackInt));
    if (element == NULL) {
        puts("Error at creating int");
        exit(1);
    }
    element->entry = item;
    element->next = NULL;
    return element;
}

bool isEmpty(Stack* stack) {
    return !stack->top;
}

bool isIEmpty(intStack* stack) {
    return !stack->top;
}

void push(StackEntry item, Stack* stack) {
    StackElement* element = createElement(item);
    element->next = stack->top;
    stack->top = element;
}

void pushInt(int item, intStack* stack) {
    StackInt* element = createInt(item);
    element->next = stack->top;
    stack->top = element;
}

StackEntry pop(Stack* stack) {
    StackEntry popped = ' ';
    if (isEmpty(stack)) {
        puts("Error: current stack is empty");
        return popped;
    }
    StackElement* temp = stack->top;
    stack->top = stack->top->next;
    popped = temp->entry;
    free(temp);
    return popped;
}

int popInt(intStack* stack) {
    int popped = INT_MIN;
    if (isIEmpty(stack)) {
        puts("Error: current int stack is empty");
        return popped;
    }
    StackInt* temp = stack->top;
    stack->top = stack->top->next;
    popped = temp->entry;
    free(temp);
    return popped;
}

StackEntry peek(Stack* stack) {
    StackEntry peeked = ' ';
    if (isEmpty(stack)) {
        puts("Error: current stack is empty");
        return peeked;
    }
    return stack->top->entry;
}

int peekInt(intStack* stack) {
    int peeked = INT_MIN;
    if (isIEmpty(stack)) {
        puts("Error: current int stack is empty");
        return peeked;
    }
    return stack->top->entry;
}

void print(Stack* stack) {
    if (isEmpty(stack)) {
        puts("[ ]");
        return;
    }
    StackElement* element = stack->top;
    while (element->next != NULL) {
        printf("[%c]->", element->entry);
        element = element->next;
    }
    printf("[%c]->", element->entry);
}

void printi(intStack* stack) {
    if (isIEmpty(stack)) {
        puts("[ ]");
        return;
    }
    StackInt* element = stack->top;
    while (element->next != NULL) {
        printf("[%d]->", element->entry);
        element = element->next;
    }
    printf("[%d]->", element->entry);
}

void clear(Stack* stack) {
    if(!isEmpty(stack)){
        StackElement* element;
        while ((element = stack->top) != NULL) {
            stack->top = stack->top->next;
            free(element);
        }
    } else {
        puts("Error: current char stack is empty");
        return;
    }
}

void cleari(intStack* stack) {
    if(!isIEmpty(stack)){
        StackInt* element;
        while ((element = stack->top) != NULL) {
            stack->top = stack->top->next;
            free(element);
        }
    } else {
        puts("Error: current int stack is empty");
        return;
    }
}

bool isOperator(char c) {
    return (c > 41) && (c < 44) || c == '-' || c == '/' || c == '^';
}

int operatorPrecedence(char operator) {
    if (isOperator(operator)) {
        if(operator == '(' || operator == ')')
            return 4;
        if (operator == '^')
            return 3;
        if (operator == '/' || operator == '*')
            return 2;
        if (operator == '+' || operator == '-')
            return 1;
    }
    return 0;
}

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

int calculate(int a, char operator, int b) {
    switch (operator) {
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

int postfixResult(const char* postfix_expression) {
    intStack *stack_application = createiStack();
    int a, b, i;
    char aux[2] = {' ', '\0'};
    for (i = 0; i < strlen(postfix_expression); i++) {
        if(isdigit(postfix_expression[i])){
            aux[0] = postfix_expression[i];
            pushInt((int)atoi(aux), stack_application);
        }
        if(isOperator(postfix_expression[i])){
            b = popInt(stack_application);
            a = popInt(stack_application);
            pushInt(calculate(a, postfix_expression[i], b), stack_application);
        }
        if(isalpha(postfix_expression[i])){
            return INT_MIN;
        }
    }
    i = peekInt(stack_application);
    cleari(stack_application);
    return i;
}

void main() {
    puts("\ninfix2Postfix\n@author: Carlos Huerta Garcia\nDescription: Receives an infix expression and displays the postfix expression and its result\n\nEnter an infix expression with single operands:");
    char* infix_expression;
    gets(infix_expression);
    char postfix_expression[] ={' '};
    infixToPostfix(infix_expression, postfix_expression);
    printf("\nPostfix expression: %s\n", postfix_expression);
    int result = postfixResult(postfix_expression);
    if(result != INT_MIN)
        printf("Result: %d\n", result);
}
