/**
 * @file stack.c
 * @author Daniel Mačura (xmacur09@vutbr.cz)
 * @brief Implementation of stack, used in table parser
 * @version 0.1
 * @date 2023-11-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "stack.h"

/**
 * @brief Creates a new stack with the given size.
 *
 * @param size The size of the stack to be created.
 * @return A pointer to the newly created stack.
 */
Stack *createStack(int size) {
    Stack *stack = malloc(sizeof(Stack));
    stack->data = malloc(size * sizeof(int));
    stack->size = size;
    stack->top = -1;
    return stack;
}

/**
 * @brief Pushes a new integer value onto the stack.
 * If the stack is full, doubles the size of the stack.
 *
 * @param stack The stack to push the value onto.
 * @param value The integer value to push onto the stack.
 */
void push(Stack *stack, int value) {
    if (stack->top == stack->size - 1) {
        stack->size *= 2;
        stack->data = realloc(stack->data, stack->size * sizeof(int));
    }
    stack->top++;
    stack->data[stack->top] = value;
}

/**
 * @brief Removes and returns the top element from the stack.
 * If the stack is empty, returns -1.
 *
 * @param stack The stack to pop from.
 * @return The value of the popped element, or -1 if the stack is empty.
 */
int pop(Stack *stack) {
    if (stack->top == -1) {
        return -1;
    }
    int value = stack->data[stack->top];
    stack->top--;
    return value;
}

/**
 * @brief Returns the top element of the stack without removing it.
 * If the stack is empty, returns -1.
 *
 * @param stack The stack to peek from.
 * @return The value of the top element, or -1 if the stack is empty.
 */
int peek(Stack *stack) {
    if (stack->top == -1) {
        return -1;
    }
    return stack->data[stack->top];
}

/**
 * @brief Frees the memory allocated for a stack.
 *
 * @param stack The stack to free.
 */
void freeStack(Stack *stack) {
    free(stack->data);
    free(stack);
}

/**
 * @brief Prints the contents of the stack to stdout.
 *
 * @param stack The stack to print.
 */
void printStack(Stack *stack) {
    verbose("Stack: ");
    for (int i = 0; i <= stack->top; i++) {
        verbose("%d ", stack->data[i]);
    }
    verbose("\n");
}
