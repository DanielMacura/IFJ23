#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Struct representing a stack data structure.
 * 
 */
typedef struct {
    int* data;  /**< Pointer to the data array. */
    int size;   /**< Maximum size of the stack. */
    int top;    /**< Index of the top element in the stack. */
} Stack;

/**
 * @brief Creates a new stack with the given size.
 * 
 * @param size The size of the stack to be created.
 * @return A pointer to the newly created stack.
 */
Stack *createStack(int size);

/**
 * @brief Pushes a new integer value onto the stack.
 * If the stack is full, doubles the size of the stack.
 *
 * @param stack The stack to push the value onto.
 * @param value The integer value to push onto the stack.
 */
void push(Stack *stack, int value);

/**
 * @brief Removes and returns the top element from the stack.
 * If the stack is empty, returns -1.
 *
 * @param stack The stack to pop from.
 * @return The value of the popped element, or -1 if the stack is empty.
 */
int pop(Stack *stack);
/**
 * @brief Returns the top element of the stack without removing it.
 * If the stack is empty, returns -1.
 *
 * @param stack The stack to peek from.
 * @return The value of the top element, or -1 if the stack is empty.
 */
int peek(Stack *stack);

/**
 * @brief Frees the memory allocated for a stack.
 * 
 * @param stack The stack to free.
 */
void freeStack(Stack *stack);

#endif