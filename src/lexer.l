%{
#include "parser.tab.h"
    void copy_lval(boolean clear);
#define COPY_AND_RETURN(t) copy_lval(true); return t
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

"auto"     { COPY_AND_RETURN(AUTO);     }
"break"    { COPY_AND_RETURN(BREAK);    }
"case"     { COPY_AND_RETURN(CASE);     }
"char"     { COPY_AND_RETURN(CHAR);     }
"const"    { COPY_AND_RETURN(CONST);    }
"continue" { COPY_AND_RETURN(CONTINUE); }
"default"  { COPY_AND_RETURN(DEFAULT);  }
"do"       { COPY_AND_RETURN(DO);       }
"double"   { COPY_AND_RETURN(DOUBLE);   }
"else"     { COPY_AND_RETURN(ELSE);     }
"enum"     { COPY_AND_RETURN(ENUM);     }
"extern"   { COPY_AND_RETURN(EXTERN);   }
"float"    { COPY_AND_RETURN(FLOAT);    }
"for"      { COPY_AND_RETURN(FOR);      }
"goto"     { COPY_AND_RETURN(GOTO);     }
"if"       { COPY_AND_RETURN(IF);       }
"int"      { COPY_AND_RETURN(INT);      }
"long"     { COPY_AND_RETURN(LONG);     }
"register" { COPY_AND_RETURN(REGISTER); }
"return"   { COPY_AND_RETURN(RETURN);   }
"signed"   { COPY_AND_RETURN(SIGNED);   }
"sizeof"   { COPY_AND_RETURN(SIZEOF);   }
"short"    { COPY_AND_RETURN(SHORT);    }
"static"   { COPY_AND_RETURN(STATIC);   }
"struct"   { COPY_AND_RETURN(STRUCT);   }
"switch"   { COPY_AND_RETURN(SWITCH);   }
"typedef"  { COPY_AND_RETURN(TYPEDEF);  }
"union"    { COPY_AND_RETURN(UNION);    }
"unsigned" { COPY_AND_RETURN(UNSIGNED); }
"void"     { COPY_AND_RETURN(VOID);     }
"volatile" { COPY_AND_RETURN(VOLATILE); }
"while"    { COPY_AND_RETURN(WHILE);    }

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
