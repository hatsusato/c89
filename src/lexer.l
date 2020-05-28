%{
#define yyHEADER_H
#include "parser.tab.h"
  int copy_lval(int, yyscan_t);
%}

%option noinput
%option nounput
%option bison-bridge
%option reentrant
%option noyywrap
%option never-interactive
%option warn

space            [ \t\n\v\f]
wide-prefix      [L]?
single-quote     [\']
double-quote     [\"]
backslash        [\\]
question-mark    [\?]
period           [\.]
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

floating-constant   ({floating-fractional}|{floating-integer}){floating-suffix}
floating-fractional {fractional-constant}{exponent-part}?
floating-integer    {digit}+{exponent-part}
fractional-constant {digit}+{period}{digit}*|{digit}*{period}{digit}+
exponent-part       {char-e}{sign}?{digit}+
sign                [+-]
floating-suffix     {char-f}?|{char-l}?

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

character-constant {wide-prefix}{single-quote}{c-char}+{single-quote}
c-char             {character-set}|{double-quote}|{escape-sequence}
escape-sequence    {simple-escape}|{octal-escape}|{hexadecimal-escape}
simple-escape      {backslash}({single-quote}|{double-quote}|{question-mark}|{backslash}|{escape-character})
octal-escape       {backslash}{octal-digit}{1,3}
hexadecimal-escape {backslash}{lower-x}{hexadecimal-digit}+

string-literal {wide-prefix}{double-quote}{s-char}*{double-quote}
s-char         {character-set}|{single-quote}|{escape-sequence}

%%
{space}

"auto"     { return copy_lval(KEYWORD_AUTO, yyscanner);     }
"break"    { return copy_lval(KEYWORD_BREAK, yyscanner);    }
"case"     { return copy_lval(KEYWORD_CASE, yyscanner);     }
"char"     { return copy_lval(KEYWORD_CHAR, yyscanner);     }
"const"    { return copy_lval(KEYWORD_CONST, yyscanner);    }
"continue" { return copy_lval(KEYWORD_CONTINUE, yyscanner); }
"default"  { return copy_lval(KEYWORD_DEFAULT, yyscanner);  }
"do"       { return copy_lval(KEYWORD_DO, yyscanner);       }
"double"   { return copy_lval(KEYWORD_DOUBLE, yyscanner);   }
"else"     { return copy_lval(KEYWORD_ELSE, yyscanner);     }
"enum"     { return copy_lval(KEYWORD_ENUM, yyscanner);     }
"extern"   { return copy_lval(KEYWORD_EXTERN, yyscanner);   }
"float"    { return copy_lval(KEYWORD_FLOAT, yyscanner);    }
"for"      { return copy_lval(KEYWORD_FOR, yyscanner);      }
"goto"     { return copy_lval(KEYWORD_GOTO, yyscanner);     }
"if"       { return copy_lval(KEYWORD_IF, yyscanner);       }
"int"      { return copy_lval(KEYWORD_INT, yyscanner);      }
"long"     { return copy_lval(KEYWORD_LONG, yyscanner);     }
"register" { return copy_lval(KEYWORD_REGISTER, yyscanner); }
"return"   { return copy_lval(KEYWORD_RETURN, yyscanner);   }
"signed"   { return copy_lval(KEYWORD_SIGNED, yyscanner);   }
"sizeof"   { return copy_lval(KEYWORD_SIZEOF, yyscanner);   }
"short"    { return copy_lval(KEYWORD_SHORT, yyscanner);    }
"static"   { return copy_lval(KEYWORD_STATIC, yyscanner);   }
"struct"   { return copy_lval(KEYWORD_STRUCT, yyscanner);   }
"switch"   { return copy_lval(KEYWORD_SWITCH, yyscanner);   }
"typedef"  { return copy_lval(KEYWORD_TYPEDEF, yyscanner);  }
"union"    { return copy_lval(KEYWORD_UNION, yyscanner);    }
"unsigned" { return copy_lval(KEYWORD_UNSIGNED, yyscanner); }
"void"     { return copy_lval(KEYWORD_VOID, yyscanner);     }
"volatile" { return copy_lval(KEYWORD_VOLATILE, yyscanner); }
"while"    { return copy_lval(KEYWORD_WHILE, yyscanner);    }

"."   { return copy_lval(OPERATOR_PERIOD, yyscanner);             }
"->"  { return copy_lval(OPERATOR_ARROW, yyscanner);              }
"++"  { return copy_lval(OPERATOR_INCREMENT, yyscanner);          }
"--"  { return copy_lval(OPERATOR_DECREMENT, yyscanner);          }
"&"   { return copy_lval(OPERATOR_AMPERSAND, yyscanner);          }
"*"   { return copy_lval(OPERATOR_ASTERISK, yyscanner);           }
"+"   { return copy_lval(OPERATOR_PLUS, yyscanner);               }
"-"   { return copy_lval(OPERATOR_MINUS, yyscanner);              }
"~"   { return copy_lval(OPERATOR_TILDE, yyscanner);              }
"!"   { return copy_lval(OPERATOR_EXCLAMATION, yyscanner);        }
"/"   { return copy_lval(OPERATOR_SLASH, yyscanner);              }
"%"   { return copy_lval(OPERATOR_PERCENT, yyscanner);            }
"<<"  { return copy_lval(OPERATOR_LEFT_SHIFT, yyscanner);         }
">>"  { return copy_lval(OPERATOR_RIGHT_SHIFT, yyscanner);        }
"<"   { return copy_lval(OPERATOR_LESS_THAN, yyscanner);          }
">"   { return copy_lval(OPERATOR_GREATER_THAN, yyscanner);       }
"<="  { return copy_lval(OPERATOR_LESS_EQUAL, yyscanner);         }
">="  { return copy_lval(OPERATOR_GREATER_EQUAL, yyscanner);      }
"=="  { return copy_lval(OPERATOR_EQUAL, yyscanner);              }
"!="  { return copy_lval(OPERATOR_NOT_EQUAL, yyscanner);          }
"^"   { return copy_lval(OPERATOR_CARET, yyscanner);              }
"|"   { return copy_lval(OPERATOR_BAR, yyscanner);                }
"&&"  { return copy_lval(OPERATOR_AND, yyscanner);                }
"||"  { return copy_lval(OPERATOR_OR, yyscanner);                 }
"?"   { return copy_lval(OPERATOR_QUESTION, yyscanner);           }
"="   { return copy_lval(OPERATOR_ASSIGN, yyscanner);             }
"*="  { return copy_lval(OPERATOR_ASTERISK_ASSIGN, yyscanner);    }
"/="  { return copy_lval(OPERATOR_SLASH_ASSIGN, yyscanner);       }
"%="  { return copy_lval(OPERATOR_PERCENT_ASSIGN, yyscanner);     }
"+="  { return copy_lval(OPERATOR_PLUS_ASSIGN, yyscanner);        }
"-="  { return copy_lval(OPERATOR_MINUS_ASSIGN, yyscanner);       }
"<<=" { return copy_lval(OPERATOR_LEFT_SHIFT_ASSIGN, yyscanner);  }
">>=" { return copy_lval(OPERATOR_RIGHT_SHIFT_ASSIGN, yyscanner); }
"&="  { return copy_lval(OPERATOR_AMPERSAND_ASSIGN, yyscanner);   }
"^="  { return copy_lval(OPERATOR_CARET_ASSIGN, yyscanner);       }
"|="  { return copy_lval(OPERATOR_BAR_ASSIGN, yyscanner);         }

"["   { return copy_lval(PUNCTUATOR_LEFT_BRACKET, yyscanner);  }
"]"   { return copy_lval(PUNCTUATOR_RIGHT_BRACKET, yyscanner); }
"("   { return copy_lval(PUNCTUATOR_LEFT_PAREN, yyscanner);    }
")"   { return copy_lval(PUNCTUATOR_RIGHT_PAREN, yyscanner);   }
"{"   { return copy_lval(PUNCTUATOR_LEFT_BRACE, yyscanner);    }
"}"   { return copy_lval(PUNCTUATOR_RIGHT_BRACE, yyscanner);   }
","   { return copy_lval(PUNCTUATOR_COMMA, yyscanner);         }
":"   { return copy_lval(PUNCTUATOR_COLON, yyscanner);         }
";"   { return copy_lval(PUNCTUATOR_SEMICOLON, yyscanner);     }
"..." { return copy_lval(PUNCTUATOR_ELLIPSIS, yyscanner);      }

{identifier}         { return copy_lval(TOKEN_IDENTIFIER, yyscanner);         }
{floating-constant}  { return copy_lval(TOKEN_FLOATING_CONSTANT, yyscanner);  }
{integer-constant}   { return copy_lval(TOKEN_INTEGER_CONSTANT, yyscanner);   }
{character-constant} { return copy_lval(TOKEN_CHARACTER_CONSTANT, yyscanner); }
{string-literal}     { return copy_lval(TOKEN_STRING_LITERAL, yyscanner);     }
. { return copy_lval(TOKEN_UNKNOWN, yyscanner); }

%%

int copy_lval(int token, yyscan_t scanner) {
  *yyget_lval(scanner) = yyget_text(scanner);
  return token;
}
