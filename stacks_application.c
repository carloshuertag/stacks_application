#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef char StackEntry;

typedef struct StackElement {
    StackEntry entry;
    struct StackElement* next;
} StackElement;

typedef struct Stack {
    StackElement* top;
} Stack;

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

StackElement* createElement(StackEntry item) { 
    StackElement* element = (StackElement*)malloc(sizeof(StackElement));
    if(element == NULL) {
        puts("Error al asignar memoria");
        exit(1);
    }
    element->entry = item;
    element->next = NULL; 
    return element;
}

bool isEmpty(Stack* stack) { 
    return !stack->top; 
}

void push(StackEntry item, Stack* stack) { 
    StackElement* element = createElement(item); 
    element->next = stack->top;
    stack->top = element;
}

StackEntry pop(Stack* stack) {
    StackEntry popped;
    if (isEmpty(stack)){
        puts("Error: current stack is empty");
        return popped; 
    }
    StackElement* temp = stack->top;
    stack->top = stack->top->next; 
    popped = temp->entry;
    free(temp); 
    return popped; 
}

StackEntry peek(Stack* stack) {
    StackEntry peeked;
    if (isEmpty(stack)) {
        puts("Error: current stack is empty");
        return peeked;
    }
    return stack->top->entry;
}

void print(Stack* stack) {
    if (isEmpty(stack)){
        puts("[ ]");
        return;
    }
    StackElement* element = stack->top;
    while (element->next != NULL){
        printf("[%c]->", element->entry);
        element = element->next;
    }
    printf("[%c]->", element->entry);
}

void clear(Stack * s) {
    StackElement* element;
    while ((element = s->top) != NULL) {
        s->top = s->top->next;
        free(element);
    }
}

bool isNumberOrLetter(char c) {
    return (c > 47) && (c < 58) || (c > 64) && (c < 91)|| (c > 96) && (c < 123);
}

bool isOperator(char c) {
    return (c > 41) && (c < 44) || c == '-' || c == '/' || c == '^'; 
}

char* stacks_application(const char* infix_expression) {
    char* postfix_expression = "";
    char aux[] = " ";
    Stack* stack = createStack();
    int i = 0;
    while(infix_expression[i] != '\0') {
        if(isNumberOrLetter(infix_expression[i])){
            aux[0] = infix_expression[i];
            strcat(postfix_expression, aux);
        } else {
            if(infix_expression[i] == '('){
                aux[0] = pop(stack);
                strcat(postfix_expression, aux);
                push(infix_expression[i], stack);
            } else {
                if(infix_expression[i] == ')'){
                    while((aux[0] = pop(stack)) != '(') {
                        strcat(postfix_expression, aux);
                    }
                } else { //isOperator
                    if (infix_expression[i] == '*' || infix_expression[i] == '/') {
                        if (peek(stack) == '^') {
                            aux[0] = pop(stack);
                            strcat(postfix_expression, aux);
                            push(infix_expression[i], stack);
                        } else{
                            push(infix_expression[i], stack);
                        }
                    } else {
                        if (infix_expression[i] == '+' || infix_expression[i] == '-') {
                            if (peek(stack) == '*' || peek(stack) == '/') {
                                aux[0] = pop(stack);
                                strcat(postfix_expression, aux);
                                push(infix_expression[i], stack);
                            } else { //is ^
                                push(infix_expression[i], stack);
                            }
                        } else {
                            push(infix_expression[i], stack);
                        }
                    }
                }
            }
        }
        i++;
    }
    while(!isEmpty(stack)){
        aux[0] = pop(stack);
        strcat(postfix_expression, aux);
    }
    clear(stack);
    return postfix_expression;
}

void main() {
    puts("\n**************************************************\nstacks_application\n**************************************************\n@author: Carlos Huerta Garcia\n**************************************************\nDescription: Receives an infix expression and displays the postfix expression\n**************************************************\n\nEnter an infix expression:");
    char* infix_expression;
    gets(infix_expression);
    puts(stacks_application(infix_expression));
}
