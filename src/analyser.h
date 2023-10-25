#ifndef ANALYSER_H
#define ANALYSER_H

#include "grammar.h"
#include "lexer.h"
#include "token.h"
#include "stack.h"

extern int table[21][29] ;
extern int *productions[];

int runSyntax(lexer_T *lexer);

#endif
