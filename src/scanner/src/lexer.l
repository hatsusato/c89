%{
#define yyHEADER_H
#include "parser.tab.h"
%}

%option noinput
%option nounput
%option bison-bridge
%option reentrant
%option noyywrap
%option never-interactive
%option nodefault
%option warn
%option extra-type="void *"

space                   [ \t\n\v\f]
wide-prefix             [L]?
single-quote            [\']
double-quote            [\"]
backslash               [\\]
question-mark           [\?]
period                  [\.]
char-e                  [eE]
char-f                  [fF]
char-l                  [lL]
char-u                  [uU]
char-x                  [xX]
lower-x                 [x]
zero                    [0]
escape-character        [abfnrtv]
character-set           [^\'\"\\\n]

identifier              {nondigit}({nondigit}|{digit})*
nondigit                [_a-zA-Z]
digit                   [0-9]

floating-constant       ({floating-fractional}|{floating-integer}){floating-suffix}
floating-fractional     {fractional-constant}{exponent-part}?
floating-integer        {digit}+{exponent-part}
fractional-constant     {digit}+{period}{digit}*|{digit}*{period}{digit}+
exponent-part           {char-e}{sign}?{digit}+
sign                    [+-]
floating-suffix         {char-f}?|{char-l}?

integer-constant        ({decimal-constant}|{octal-constant}|{hexadecimal-constant}){integer-suffix}
decimal-constant        {nonzero-digit}{digit}*
octal-constant          {zero}{octal-digit}*
hexadecimal-constant    {zero}{char-x}{hexadecimal-digit}+
nonzero-digit           [1-9]
octal-digit             [0-7]
hexadecimal-digit       [0-9a-fA-F]
integer-suffix          {unsigned-suffix}{long-suffix}|{long-suffix}{unsigned-suffix}
unsigned-suffix         {char-u}?
long-suffix             {char-l}?

character-constant      {wide-prefix}{single-quote}{c-char}+{single-quote}
c-char                  {character-set}|{double-quote}|{escape-sequence}
escape-sequence         {simple-escape}|{octal-escape}|{hexadecimal-escape}
simple-escape           {backslash}({single-quote}|{double-quote}|{question-mark}|{backslash}|{escape-character})
octal-escape            {backslash}{octal-digit}{1,3}
hexadecimal-escape      {backslash}{lower-x}{hexadecimal-digit}+

string-literal          {wide-prefix}{double-quote}{s-char}*{double-quote}
s-char                  {character-set}|{single-quote}|{escape-sequence}

directive               [#][^\n]*

%%

"auto"      { return TOKEN_AUTO;     }
"break"     { return TOKEN_BREAK;    }
"case"      { return TOKEN_CASE;     }
"char"      { return TOKEN_CHAR;     }
"const"     { return TOKEN_CONST;    }
"continue"  { return TOKEN_CONTINUE; }
"default"   { return TOKEN_DEFAULT;  }
"do"        { return TOKEN_DO;       }
"double"    { return TOKEN_DOUBLE;   }
"else"      { return TOKEN_ELSE;     }
"enum"      { return TOKEN_ENUM;     }
"extern"    { return TOKEN_EXTERN;   }
"float"     { return TOKEN_FLOAT;    }
"for"       { return TOKEN_FOR;      }
"goto"      { return TOKEN_GOTO;     }
"if"        { return TOKEN_IF;       }
"int"       { return TOKEN_INT;      }
"long"      { return TOKEN_LONG;     }
"register"  { return TOKEN_REGISTER; }
"return"    { return TOKEN_RETURN;   }
"signed"    { return TOKEN_SIGNED;   }
"sizeof"    { return TOKEN_SIZEOF;   }
"short"     { return TOKEN_SHORT;    }
"static"    { return TOKEN_STATIC;   }
"struct"    { return TOKEN_STRUCT;   }
"switch"    { return TOKEN_SWITCH;   }
"typedef"   { return TOKEN_TYPEDEF;  }
"union"     { return TOKEN_UNION;    }
"unsigned"  { return TOKEN_UNSIGNED; }
"void"      { return TOKEN_VOID;     }
"volatile"  { return TOKEN_VOLATILE; }
"while"     { return TOKEN_WHILE;    }

"."     { return TOKEN_PERIOD;             }
"->"    { return TOKEN_ARROW;              }
"++"    { return TOKEN_INCREMENT;          }
"--"    { return TOKEN_DECREMENT;          }
"&"     { return TOKEN_AMPERSAND;          }
"*"     { return TOKEN_ASTERISK;           }
"+"     { return TOKEN_PLUS;               }
"-"     { return TOKEN_MINUS;              }
"~"     { return TOKEN_TILDE;              }
"!"     { return TOKEN_EXCLAMATION;        }
"/"     { return TOKEN_SLASH;              }
"%"     { return TOKEN_PERCENT;            }
"<<"    { return TOKEN_LEFT_SHIFT;         }
">>"    { return TOKEN_RIGHT_SHIFT;        }
"<"     { return TOKEN_LESS_THAN;          }
">"     { return TOKEN_GREATER_THAN;       }
"<="    { return TOKEN_LESS_EQUAL;         }
">="    { return TOKEN_GREATER_EQUAL;      }
"=="    { return TOKEN_EQUAL;              }
"!="    { return TOKEN_NOT_EQUAL;          }
"^"     { return TOKEN_CARET;              }
"|"     { return TOKEN_BAR;                }
"&&"    { return TOKEN_AND;                }
"||"    { return TOKEN_OR;                 }
"?"     { return TOKEN_QUESTION;           }
"="     { return TOKEN_ASSIGN;             }
"*="    { return TOKEN_ASTERISK_ASSIGN;    }
"/="    { return TOKEN_SLASH_ASSIGN;       }
"%="    { return TOKEN_PERCENT_ASSIGN;     }
"+="    { return TOKEN_PLUS_ASSIGN;        }
"-="    { return TOKEN_MINUS_ASSIGN;       }
"<<="   { return TOKEN_LEFT_SHIFT_ASSIGN;  }
">>="   { return TOKEN_RIGHT_SHIFT_ASSIGN; }
"&="    { return TOKEN_AMPERSAND_ASSIGN;   }
"^="    { return TOKEN_CARET_ASSIGN;       }
"|="    { return TOKEN_BAR_ASSIGN;         }

"["     { return TOKEN_LEFT_BRACKET;  }
"]"     { return TOKEN_RIGHT_BRACKET; }
"("     { return TOKEN_LEFT_PAREN;    }
")"     { return TOKEN_RIGHT_PAREN;   }
"{"     { return TOKEN_LEFT_BRACE;    }
"}"     { return TOKEN_RIGHT_BRACE;   }
","     { return TOKEN_COMMA;         }
":"     { return TOKEN_COLON;         }
";"     { return TOKEN_SEMICOLON;     }
"..."   { return TOKEN_ELLIPSIS;      }

%%
