#ifndef ANALYSER_H
#define ANALYSER_H

#include "grammar.h"
#include "lexer.h"
#include "token.h"
#include "stack.h"

extern int table[24][42] ;
extern int *productions[];

int runSyntax(lexer_T *lexer);

#endif
