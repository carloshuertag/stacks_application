#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <stdio.h>

typedef int iStackEntry;

typedef struct iStackElement {
    StackEntry entry;
    struct iStackElement* next;
} iStackElement;

typedef struct iStack {
    iStackElement* top;
} iStack;

iStack* createiStack() {
    iStack* stack = (iStack*)malloc(sizeof(iStack));
    stack->top = NULL;
    return stack;
}

iStackElement* createiElement(iStackEntry item) {
    iStackElement* element = (iStackElement*)malloc(sizeof(iStackElement));
    if (element == NULL) {
        puts("Error at creating element");
        exit(1);
    }
    element->entry = item;
    element->next = NULL;
    return element;
}

bool isiEmpty(iStack* stack) {
    return !stack->top;
}

void pushi(iStackEntry item, iStack* stack) {
    iStackElement* element = createiElement(item);
    element->next = stack->top;
    stack->top = element;
}

iStackEntry popi(iStack* stack) {
    iStackEntry popped = INT_MIN;
    if (isiEmpty(stack)) {
        puts("Error: current stack is empty");
        return popped;
    }
    iStackElement* temp = stack->top;
    stack->top = stack->top->next;
    popped = temp->entry;
    free(temp);
    return popped;
}

iStackEntry peeki(iStack* stack) {
    iStackEntry peeked = INT_MIN;
    if (isiEmpty(stack)) {
        puts("Error: current stack is empty");
        return peeked;
    }
    return stack->top->entry;
}

void printi(iStack* stack) {
    if (isiEmpty(stack)) {
        puts("[ ]");
        return;
    }
    iStackElement* element = stack->top;
    while (element->next != NULL) {
        printf("[%d]->", element->entry);
        element = element->next;
    }
    printf("[%d]->", element->entry);
}

void cleari(iStack* stack) {
    if(!isiEmpty(stack)){
        iStackElement* element;
        while ((element = stack->top) != NULL) {
            stack->top = stack->top->next;
            free(element);
        }
    } else {
        puts("Error: current char stack is empty");
        return;
    }
}