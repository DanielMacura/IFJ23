/**
 * @file verbose.c
 * @author Daniel Mačura (xmacur09@vutbr.cz)
 * @brief Implementation of verbose.h
 * @version 0.1
 * @date 2023-11-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "verbose.h"
extern Stack *recursion_stack;


bool Verbose = false;

void setVerbose(bool setting) {
    Verbose = setting;
}

int verbose(const char * restrict format, ...) {
    if( !Verbose )
        return 0;

    va_list args;
    va_start(args, format);
    int ret = vprintf(format, args);
    va_end(args);

    return ret;
}

int generatePrint(const char * restrict format, ...){
    int recursion = peek(recursion_stack);
    for (int i = 0; i < recursion; i++) {
        printf("\t");
    }
    va_list args;
    va_start(args, format);
    int ret = vprintf(format, args);
    va_end(args);

    return ret;
}