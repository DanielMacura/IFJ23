/**
 * @file verbose.h
 * @author Daniel Mačura (xmacur09@vutbr.cz)
 * @brief Header file for verbose.c
 * @version 0.1
 * @date 2023-11-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef VERBOSE
#define VERBOSE
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
/**
 * @brief Wrapper for printf that only prints if verbose is set to true
 * 
 * @param restrict Arguments for printf
 * @return int Retruns value from printf
 */
int verbose(const char * restrict, ...);

/**
 * @brief Sets the global variable Verbose to the given value
 * 
 * @param bool 
 */
void setVerbose(bool);

#endif