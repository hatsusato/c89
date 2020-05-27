%{
#define yyHEADER_H
#include "parser.tab.h"
  void copy_lval(boolean, yyscan_t);
#define COPY_AND_RETURN(t) copy_lval(true, yyscanner); return t
%}

%option noinput
%option nounput
%option bison-bridge
%option reentrant
%option noyywrap
%option never-interactive
%option warn
%option nodefault

%x string

wide-prefix          [L]?
single-quote         [\']
double-quote         [\"]
backslash            [\\]
source-character-set [^\'\"\\\n]

identifier {nondigit}({nondigit}|{digit})*
nondigit   [_a-zA-Z]
digit      [0-9]

floating-constant   ({floating-fractional}|{floating-integer}){floating-suffix}
floating-fractional {fractional-constant}{exponent-part}?
floating-integer    {digit}+{exponent-part}
fractional-constant {digit}+[.]{digit}*|{digit}*[.]{digit}+
exponent-part       [eE]{sign}{digit}+
sign                [+-]?
floating-suffix     [flFL]?

integer-constant     ({decimal-constant}|{octal-constant}|{hexadecimal-constant}){integer-suffix}
decimal-constant     {nonzero-digit}{digit}*
octal-constant       [0]{octal-digit}*
hexadecimal-constant [0][xX]{hexadecimal-digit}+
nonzero-digit        [1-9]
octal-digit          [0-7]
hexadecimal-digit    [0-9a-fA-F]
integer-suffix       {unsigned-suffix}{long-suffix}|{long-suffix}{unsigned-suffix}
unsigned-suffix      [uU]?
long-suffix          [lL]?

character-constant          {wide-prefix}{single-quote}{c-char}+{single-quote}
c-char                      {source-character-set}|{double-quote}|{escape-sequence}
escape-sequence             {simple-escape-sequence}|{octal-escape-sequence}|{hexadecimal-escape-sequence}
simple-escape-sequence      {backslash}[\'\"\?\\abfnrtv]
octal-escape-sequence       {backslash}{octal-digit}{1,3}
hexadecimal-escape-sequence {backslash}[x]{hexadecimal-digit}+

string-literal {wide-prefix}{double-quote}{s-char}*{double-quote}
s-char         {source-character-set}|{single-quote}|{escape-sequence}

%%

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

"["   { COPY_AND_RETURN(LBRK);     }
"]"   { COPY_AND_RETURN(RBRK);     }
"("   { COPY_AND_RETURN(LPAR);     }
")"   { COPY_AND_RETURN(RPAR);     }
"{"   { COPY_AND_RETURN(LBRC);     }
"}"   { COPY_AND_RETURN(RBRC);     }
"."   { COPY_AND_RETURN(DOT);      }
"->"  { COPY_AND_RETURN(ARROW);    }
"++"  { COPY_AND_RETURN(INC);      }
"--"  { COPY_AND_RETURN(DEC);      }
"&"   { COPY_AND_RETURN(AMP);      }
"*"   { COPY_AND_RETURN(STAR);     }
"+"   { COPY_AND_RETURN(PLUS);     }
"-"   { COPY_AND_RETURN(MIN);      }
"~"   { COPY_AND_RETURN(TILDA);    }
"!"   { COPY_AND_RETURN(EXCL);     }
"/"   { COPY_AND_RETURN(SLA);      }
"%"   { COPY_AND_RETURN(PERC);     }
"<<"  { COPY_AND_RETURN(LSHF);     }
">>"  { COPY_AND_RETURN(RSHF);     }
"<"   { COPY_AND_RETURN(LT);       }
">"   { COPY_AND_RETURN(GT);       }
"<="  { COPY_AND_RETURN(LE);       }
">="  { COPY_AND_RETURN(GE);       }
"=="  { COPY_AND_RETURN(EQ);       }
"!="  { COPY_AND_RETURN(NE);       }
"^"   { COPY_AND_RETURN(HAT);      }
"|"   { COPY_AND_RETURN(BAR);      }
"&&"  { COPY_AND_RETURN(AND);      }
"||"  { COPY_AND_RETURN(OR);       }
"?"   { COPY_AND_RETURN(QUEST);    }
":"   { COPY_AND_RETURN(COLON);    }
"="   { COPY_AND_RETURN(ASG);      }
"*="  { COPY_AND_RETURN(STAR_ASG); }
"/="  { COPY_AND_RETURN(SLA_ASG);  }
"%="  { COPY_AND_RETURN(PERC_ASG); }
"+="  { COPY_AND_RETURN(PLUS_ASG); }
"-="  { COPY_AND_RETURN(MIN_ASG);  }
"<<=" { COPY_AND_RETURN(LSHF_ASG); }
">>=" { COPY_AND_RETURN(RSHF_ASG); }
"&="  { COPY_AND_RETURN(AMP_ASG);  }
"^="  { COPY_AND_RETURN(HAT_ASG);  }
"|="  { COPY_AND_RETURN(BAR_ASG);  }
","   { COPY_AND_RETURN(COMMA);    }
";"   { COPY_AND_RETURN(SEMIC);    }
"..." { COPY_AND_RETURN(ELLIP);    }

{identifier}         { COPY_AND_RETURN(IDENT); }
{floating-constant}  { COPY_AND_RETURN(FLOATING); }
{integer-constant}   { COPY_AND_RETURN(INTEGER); }
{character-constant} { COPY_AND_RETURN(CHARACTER); }
{string-literal}     { COPY_AND_RETURN(LITERAL); }

[ \t\n\v\f]
. { COPY_AND_RETURN(UNKNOWN); }

%%

void copy_lval(boolean clear, yyscan_t scanner) {
  YYSTYPE *lval = yyget_lval(scanner);
  if (!*lval) {
    *lval = vector_new(1);
    *(char*)vector_back(*lval) = 0;
  }
  if (clear) {
    vector_clear(*lval);
    *(char*)vector_back(*lval) = 0;
  }
  vector_pop(*lval);
  vector_append(*lval, yyget_text(scanner), yyget_leng(scanner));
  *(char*)vector_back(*lval) = 0;
}
