// Migration to C++ required
%{ 
#include <stdio.h>

int  yylex ( void );
void  yyerror ( char  const *);
%}

%token DEFINITION

%token BEGIN_BAR ENDBAR NEWSEC

%token SCI_NOTE LATIN_NOTE REST BLANK

%token BEGIN_NOTE ENG_NOTE BEGIN_NOTEGROUP END_NOTEGROUP

%token COMMA DURATION


