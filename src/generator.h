/**
 * @file generator.h
 * @author Daniel Mačura (xmacur09@vutbr.cz)
 * @brief Header file for generator.c
 * @version 0.1
 * @date 2023-11-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef GENERATOR_H
#define GENERATOR_H
#include "types.h"


#include "errors.h"
#include "lexer.h"

union data_type;

void beginGenerator();

void endGenerator();

void beginMain();

void endMain();

void defineVariable(char *name);

void popToVariable(char *name);

void generateTerm(token *token_ptr);

void operationRule(rules operation, token *token_ptr);

#endif 