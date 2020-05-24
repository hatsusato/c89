%{
#include "parser.tab.h"
#include <string.h>
%}

%option noyywrap
%option never-interactive

integer [0-9]+
plus     "+"
minus    "-"
aster    "*"
slash    "/"
lpar     "("
rpar     ")"
ifs      [ \t\n]

%%
{integer} { yylval = atoi(yytext); return NUM; }
{plus}    { return PLUS; }
{minus}   { return MINUS; }
{aster}   { return ASTER; }
{slash}   { return SLASH; }
{lpar}    { return LPAR; }
{rpar}    { return RPAR; }
{ifs}     {;}

%%
