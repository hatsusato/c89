%{
#include "parser.tab.h"
%}

%option noyywrap
%option never-interactive

%x preprocess
%x comment
%x string

%%

"#" BEGIN(preprocess);
<preprocess>[^\n\\]*
<preprocess>[\\]+[^\\]
<preprocess>[\n] { BEGIN(INITIAL); return PREPROCESS; }

"/*" BEGIN(comment);
<comment>[^*]*
<comment>"*"+[^*/]*
<comment>"*"+"/" { BEGIN(INITIAL); return COMMENT; }

["] BEGIN(string);
<string>[^"\n\\]
<string>[\\][^\n]
<string>["] { BEGIN(INITIAL); return LITERAL; }

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

%%
