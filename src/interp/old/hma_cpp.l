%{
/*
    #include <string>
    #include <iostream>
    #include <fstream>
*/
    #include <stdio.h>
    #include "hma_types.h"

%}

%%

"@"*             { printf("%s\n", yytext); return DEFINITION; }
"("              { return BEGIN_NOTE; }
")"              { return END_NOTE; }
"{"              { return BEGIN_NOTEGROUP; }
"}"              { return END_NOTEGROUP; }
"|"[^";"]              { return NEWSEC; }
"|;"             { return END_BAR; }
"@I"[0-9]"V"[0-9]":" {return BEGIN_BAR; }

[A-G]?[0-9]      { return SCI_NOTE; }
"ut"?[0-9]|"do"?[0-9]|"re"?[0-9]|"mi"?[0-9]   { return LATIN_NOTE; }
"fa"?[0-9]|"sol"?[0-9]|"la"?[0-9]|"si"?[0-9] { return LATIN_NOTE; }
"r"|"R"          { return REST; }
["b"|"B"]"l"[an]?"k"  { return BLANK; }
","              { return COMMA; }
[0-9]+"/"[0-9]+  { return DURATION; }
[ \t\n]   ;       /* ignore white space and newline */
"%"*\n  ;         /* ignore comments */

%%
/*
//int main(void) {
yyFlexLexer lex(&std::cin);
//while (lex.yylex()) { }
lex.yylex();
std::ifstream  file("sample.txt");
yyFlexLexer  anotherLexer(&file);
anotherLexer.yylex();
//while(anotherLexer.yylex()) { }
//return 0;}

int yyFlexLexer::yywrap()
{
    return true;
}*/
