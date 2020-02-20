#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <stdio.h>

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
    if (element == NULL) {
        puts("Error at creating element");
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
    StackEntry popped = CHAR_MIN;
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

StackEntry peek(Stack* stack) {
    StackEntry peeked = CHAR_MIN;
    if (isEmpty(stack)) {
        puts("Error: current stack is empty");
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