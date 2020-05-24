%{
#include "parser.tab.h"
%}

%option noyywrap
%option never-interactive

%%

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

"(" return LPAR;
")" return RPAR;
"[" return LBRK;
"]" return RBRK;
"{" return LBRC;
"}" return RBRC;
"." return DOT;
"->" return ARROW;
"++" return INC;
"--" return DEC;
"+" return PLUS;
"-" return MIN;
"!" return EXCL;
"~" return TILDA;
"*" return STAR;
"&" return AMP;
"/" return SLA;
"%" return PERC;
"<<" return LSHF;
">>" return RSHF;
">" return GT;
"<" return LT;
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
"+=" return PLUS_ASG;
"-=" return MIN_ASG;
"*=" return STAR_ASG;
"/=" return SLA_ASG;
"%=" return PERC_ASG;
"<<=" return LSHF_ASG;
">>=" return RSHF_ASG;
"&=" return AMP_ASG;
"^=" return HAT_ASG;
"|=" return BAR_ASG;
"," return COMMA;

%%
