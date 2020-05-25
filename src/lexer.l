%{
#include "parser.tab.h"
  void copy_lval(boolean);
%}

%option noyywrap
%option never-interactive

%x string

%%

[\"] {
  BEGIN(string);
  copy_lval(true);
}
<string>[^\"\n\\]* { copy_lval(false); }
<string>[\\][^\n] { copy_lval(false); }
<string>[\"] {
  BEGIN(INITIAL);
  copy_lval(false);
  return LITERAL;
}

"auto" return AUTO;
"break" return BREAK;
"case" return CASE;
"char" return CHAR;
"const" return CONST;
"continue" return CONTINUE;
"default" return DEFAULT;
"do" return DO;
"double" return DOUBLE;
"else" return ELSE;
"enum" return ENUM;
"extern" return EXTERN;
"float" return FLOAT;
"for" return FOR;
"goto" return GOTO;
"if" return IF;
"int" return INT;
"long" return LONG;
"register" return REGISTER;
"return" return RETURN;
"signed" return SIGNED;
"sizeof" return SIZEOF;
"short" return SHORT;
"static" return STATIC;
"struct" return STRUCT;
"switch" return SWITCH;
"typedef" return TYPEDEF;
"union" return UNION;
"unsigned" return UNSIGNED;
"void" return VOID;
"volatile" return VOLATILE;
"while" return WHILE;

"[" return LBRK;
"]" return RBRK;
"(" return LPAR;
")" return RPAR;
"{" return LBRC;
"}" return RBRC;
"." return DOT;
"->" return ARROW;
"++" return INC;
"--" return DEC;
"&" return AMP;
"*" return STAR;
"+" return PLUS;
"-" return MIN;
"~" return TILDA;
"!" return EXCL;
"/" return SLA;
"%" return PERC;
"<<" return LSHF;
">>" return RSHF;
"<" return LT;
">" return GT;
"<=" return LE;
">=" return GE;
"==" return EQ;
"!=" return NE;
"^" return HAT;
"|" return BAR;
"&&" return AND;
"||" return OR;
"?" return QUEST;
":" return COLON;
"=" return ASG;
"*=" return STAR_ASG;
"/=" return SLA_ASG;
"%=" return PERC_ASG;
"+=" return PLUS_ASG;
"-=" return MIN_ASG;
"<<=" return LSHF_ASG;
">>=" return RSHF_ASG;
"&=" return AMP_ASG;
"^=" return HAT_ASG;
"|=" return BAR_ASG;
"," return COMMA;
";" return SEMIC;
"..." return ELLIP;

[_a-zA-Z][_a-zA-Z0-9]* { return IDENT; }

[0][0-7]* { return INTEGER; }
[1-9][0-9]* { return INTEGER; }
[0][xX][0-9a-fA-F]* { return INTEGER; }

[ \t\n]

%%

void copy_lval(boolean clear) {
  if (!yylval) {
    yylval = vector_new(1);
    *(char*)vector_back(yylval)=0;
  }
  if (clear) {
    vector_clear(yylval);
    *(char*)vector_back(yylval)=0;
  }
  vector_pop(yylval);
  vector_copy(yylval, yytext, yyleng);
  *(char*)vector_back(yylval)=0;
}
