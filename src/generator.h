/**
 * Project: IFJ23 Compiler
 * 
 * @file generator.h
 * @brief Generator header file
 * 
 * @authors xmacur09
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