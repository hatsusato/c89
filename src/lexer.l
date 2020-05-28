%{
#define yyHEADER_H
#include "parser.tab.h"
  int copy_lval(int, yyscan_t);
#define COPY_AND_RETURN(t) return copy_lval(t, yyscanner)
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

space            [ \t\n\v\f]
wide-prefix      [L]?
single-quote     [\']
double-quote     [\"]
backslash        [\\]
question-mark    [\?]
dot              [\.]
char-e           [eE]
char-f           [fF]
char-l           [lL]
char-u           [uU]
char-x           [xX]
lower-x          [x]
zero             [0]
escape-character [abfnrtv]
character-set    [^\'\"\\\n]

identifier {nondigit}({nondigit}|{digit})*
nondigit   [_a-zA-Z]
digit      [0-9]

floating-constant   ({floating-fractional}|{floating-integer}){floating-suffix}?
floating-fractional {fractional-constant}{exponent-part}?
floating-integer    {digit}+{exponent-part}
fractional-constant {digit}+{dot}{digit}*|{digit}*{dot}{digit}+
exponent-part       {char-e}{sign}?{digit}+
sign                [+-]
floating-suffix     {char-f}|{char-l}

integer-constant     ({decimal-constant}|{octal-constant}|{hexadecimal-constant}){integer-suffix}
decimal-constant     {nonzero-digit}{digit}*
octal-constant       {zero}{octal-digit}*
hexadecimal-constant {zero}{char-x}{hexadecimal-digit}+
nonzero-digit        [1-9]
octal-digit          [0-7]
hexadecimal-digit    [0-9a-fA-F]
integer-suffix       {unsigned-suffix}{long-suffix}|{long-suffix}{unsigned-suffix}
unsigned-suffix      {char-u}?
long-suffix          {char-l}?

character-constant          {wide-prefix}{single-quote}{c-char}+{single-quote}
c-char                      {character-set}|{double-quote}|{escape-sequence}
escape-sequence             {simple-escape-sequence}|{octal-escape-sequence}|{hexadecimal-escape-sequence}
simple-escape-sequence      {backslash}({single-quote}|{double-quote}|{question-mark}|{backslash}|{escape-character})
octal-escape-sequence       {backslash}{octal-digit}{1,3}
hexadecimal-escape-sequence {backslash}{lower-x}{hexadecimal-digit}+

string-literal {wide-prefix}{double-quote}{s-char}*{double-quote}
s-char         {character-set}|{single-quote}|{escape-sequence}

%%
{space}

"auto"     { COPY_AND_RETURN(KEYWORD_AUTO);     }
"break"    { COPY_AND_RETURN(KEYWORD_BREAK);    }
"case"     { COPY_AND_RETURN(KEYWORD_CASE);     }
"char"     { COPY_AND_RETURN(KEYWORD_CHAR);     }
"const"    { COPY_AND_RETURN(KEYWORD_CONST);    }
"continue" { COPY_AND_RETURN(KEYWORD_CONTINUE); }
"default"  { COPY_AND_RETURN(KEYWORD_DEFAULT);  }
"do"       { COPY_AND_RETURN(KEYWORD_DO);       }
"double"   { COPY_AND_RETURN(KEYWORD_DOUBLE);   }
"else"     { COPY_AND_RETURN(KEYWORD_ELSE);     }
"enum"     { COPY_AND_RETURN(KEYWORD_ENUM);     }
"extern"   { COPY_AND_RETURN(KEYWORD_EXTERN);   }
"float"    { COPY_AND_RETURN(KEYWORD_FLOAT);    }
"for"      { COPY_AND_RETURN(KEYWORD_FOR);      }
"goto"     { COPY_AND_RETURN(KEYWORD_GOTO);     }
"if"       { COPY_AND_RETURN(KEYWORD_IF);       }
"int"      { COPY_AND_RETURN(KEYWORD_INT);      }
"long"     { COPY_AND_RETURN(KEYWORD_LONG);     }
"register" { COPY_AND_RETURN(KEYWORD_REGISTER); }
"return"   { COPY_AND_RETURN(KEYWORD_RETURN);   }
"signed"   { COPY_AND_RETURN(KEYWORD_SIGNED);   }
"sizeof"   { COPY_AND_RETURN(KEYWORD_SIZEOF);   }
"short"    { COPY_AND_RETURN(KEYWORD_SHORT);    }
"static"   { COPY_AND_RETURN(KEYWORD_STATIC);   }
"struct"   { COPY_AND_RETURN(KEYWORD_STRUCT);   }
"switch"   { COPY_AND_RETURN(KEYWORD_SWITCH);   }
"typedef"  { COPY_AND_RETURN(KEYWORD_TYPEDEF);  }
"union"    { COPY_AND_RETURN(KEYWORD_UNION);    }
"unsigned" { COPY_AND_RETURN(KEYWORD_UNSIGNED); }
"void"     { COPY_AND_RETURN(KEYWORD_VOID);     }
"volatile" { COPY_AND_RETURN(KEYWORD_VOLATILE); }
"while"    { COPY_AND_RETURN(KEYWORD_WHILE);    }

"."   { COPY_AND_RETURN(OPERATOR_PERIOD);             }
"->"  { COPY_AND_RETURN(OPERATOR_ARROW);              }
"++"  { COPY_AND_RETURN(OPERATOR_INCREMENT);          }
"--"  { COPY_AND_RETURN(OPERATOR_DECREMENT);          }
"&"   { COPY_AND_RETURN(OPERATOR_AMPERSAND);          }
"*"   { COPY_AND_RETURN(OPERATOR_ASTERISK);           }
"+"   { COPY_AND_RETURN(OPERATOR_PLUS);               }
"-"   { COPY_AND_RETURN(OPERATOR_MINUS);              }
"~"   { COPY_AND_RETURN(OPERATOR_TILDE);              }
"!"   { COPY_AND_RETURN(OPERATOR_EXCLAMATION);        }
"/"   { COPY_AND_RETURN(OPERATOR_SLASH);              }
"%"   { COPY_AND_RETURN(OPERATOR_PERCENT);            }
"<<"  { COPY_AND_RETURN(OPERATOR_LEFT_SHIFT);         }
">>"  { COPY_AND_RETURN(OPERATOR_RIGHT_SHIFT);        }
"<"   { COPY_AND_RETURN(OPERATOR_LESS_THAN);          }
">"   { COPY_AND_RETURN(OPERATOR_GREATER_THAN);       }
"<="  { COPY_AND_RETURN(OPERATOR_LESS_EQUAL);         }
">="  { COPY_AND_RETURN(OPERATOR_GREATER_EQUAL);      }
"=="  { COPY_AND_RETURN(OPERATOR_EQUAL);              }
"!="  { COPY_AND_RETURN(OPERATOR_NOT_EQUAL);          }
"^"   { COPY_AND_RETURN(OPERATOR_CARET);              }
"|"   { COPY_AND_RETURN(OPERATOR_BAR);                }
"&&"  { COPY_AND_RETURN(OPERATOR_AND);                }
"||"  { COPY_AND_RETURN(OPERATOR_OR);                 }
"?"   { COPY_AND_RETURN(OPERATOR_QUESTION);           }
"="   { COPY_AND_RETURN(OPERATOR_ASSIGN);             }
"*="  { COPY_AND_RETURN(OPERATOR_ASTERISK_ASSIGN);    }
"/="  { COPY_AND_RETURN(OPERATOR_SLASH_ASSIGN);       }
"%="  { COPY_AND_RETURN(OPERATOR_PERCENT_ASSIGN);     }
"+="  { COPY_AND_RETURN(OPERATOR_PLUS_ASSIGN);        }
"-="  { COPY_AND_RETURN(OPERATOR_MINUS_ASSIGN);       }
"<<=" { COPY_AND_RETURN(OPERATOR_LEFT_SHIFT_ASSIGN);  }
">>=" { COPY_AND_RETURN(OPERATOR_RIGHT_SHIFT_ASSIGN); }
"&="  { COPY_AND_RETURN(OPERATOR_AMPERSAND_ASSIGN);   }
"^="  { COPY_AND_RETURN(OPERATOR_CARET_ASSIGN);       }
"|="  { COPY_AND_RETURN(OPERATOR_BAR_ASSIGN);         }

"["   { COPY_AND_RETURN(PUNCTUATOR_LEFT_BRACKET);  }
"]"   { COPY_AND_RETURN(PUNCTUATOR_RIGHT_BRACKET); }
"("   { COPY_AND_RETURN(PUNCTUATOR_LEFT_PAREN);    }
")"   { COPY_AND_RETURN(PUNCTUATOR_RIGHT_PAREN);   }
"{"   { COPY_AND_RETURN(PUNCTUATOR_LEFT_BRACE);    }
"}"   { COPY_AND_RETURN(PUNCTUATOR_RIGHT_BRACE);   }
","   { COPY_AND_RETURN(PUNCTUATOR_COMMA);         }
":"   { COPY_AND_RETURN(PUNCTUATOR_COLON);         }
";"   { COPY_AND_RETURN(PUNCTUATOR_SEMICOLON);     }
"..." { COPY_AND_RETURN(PUNCTUATOR_ELLIPSIS);      }

{identifier}         { COPY_AND_RETURN(TOKEN_IDENTIFIER);         }
{floating-constant}  { COPY_AND_RETURN(TOKEN_FLOATING_CONSTANT);  }
{integer-constant}   { COPY_AND_RETURN(TOKEN_INTEGER_CONSTANT);   }
{character-constant} { COPY_AND_RETURN(TOKEN_CHARACTER_CONSTANT); }
{string-literal}     { COPY_AND_RETURN(TOKEN_STRING_LITERAL);     }

. { COPY_AND_RETURN(TOKEN_UNKNOWN); }

%%

int copy_lval(int token, yyscan_t scanner) {
  *yyget_lval(scanner) = yyget_text(scanner);
  return token;
}
