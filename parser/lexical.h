#ifndef LEXICAL_H
#include "NODE.h"
#include <stdlib.h>
#include <stdio.h>
extern int line_no;
extern int char_no;
extern FILE* fp;
extern void lex();
extern node *tok;
#endif
#define LEXICAL_H
