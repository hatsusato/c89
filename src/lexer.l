%{
#include "parser.tab.h"
    void copy_lval(boolean clear);
#define COPY_AND_RETURN(t) copy_lval(true); return t
%}

%option noyywrap
%option never-interactive

%x string

%%

[\"]               { BEGIN(string); copy_lval(true); }
<string>[^\"\n\\]* { copy_lval(false); }
<string>[\\][^\n]  { copy_lval(false); }
<string>[\"]       { BEGIN(INITIAL); copy_lval(false); return LITERAL; }

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

[_a-zA-Z][_a-zA-Z0-9]* { COPY_AND_RETURN(IDENT); }

[0][0-7]*           { COPY_AND_RETURN(INTEGER); }
[1-9][0-9]*         { COPY_AND_RETURN(INTEGER); }
[0][xX][0-9a-fA-F]* { COPY_AND_RETURN(INTEGER); }

[ \t\n]
. { return UNKNOWN; }

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
