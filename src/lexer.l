%{
#define yyHEADER_H
#include "parser.tab.h"
#define EMIT_TOKEN(token) do {return token;} while(0)
#include "scanner.h"
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

%%
[#][^\n]*
{space}

"auto"          { EMIT_TOKEN(TOKEN_AUTO);     }
"break"         { EMIT_TOKEN(TOKEN_BREAK);    }
"case"          { EMIT_TOKEN(TOKEN_CASE);     }
"char"          { EMIT_TOKEN(TOKEN_CHAR);     }
"const"         { EMIT_TOKEN(TOKEN_CONST);    }
"continue"      { EMIT_TOKEN(TOKEN_CONTINUE); }
"default"       { EMIT_TOKEN(TOKEN_DEFAULT);  }
"do"            { EMIT_TOKEN(TOKEN_DO);       }
"double"        { EMIT_TOKEN(TOKEN_DOUBLE);   }
"else"          { EMIT_TOKEN(TOKEN_ELSE);     }
"enum"          { EMIT_TOKEN(TOKEN_ENUM);     }
"extern"        { EMIT_TOKEN(TOKEN_EXTERN);   }
"float"         { EMIT_TOKEN(TOKEN_FLOAT);    }
"for"           { EMIT_TOKEN(TOKEN_FOR);      }
"goto"          { EMIT_TOKEN(TOKEN_GOTO);     }
"if"            { EMIT_TOKEN(TOKEN_IF);       }
"int"           { EMIT_TOKEN(TOKEN_INT);      }
"long"          { EMIT_TOKEN(TOKEN_LONG);     }
"register"      { EMIT_TOKEN(TOKEN_REGISTER); }
"return"        { EMIT_TOKEN(TOKEN_RETURN);   }
"signed"        { EMIT_TOKEN(TOKEN_SIGNED);   }
"sizeof"        { EMIT_TOKEN(TOKEN_SIZEOF);   }
"short"         { EMIT_TOKEN(TOKEN_SHORT);    }
"static"        { EMIT_TOKEN(TOKEN_STATIC);   }
"struct"        { EMIT_TOKEN(TOKEN_STRUCT);   }
"switch"        { EMIT_TOKEN(TOKEN_SWITCH);   }
"typedef"       { EMIT_TOKEN(TOKEN_TYPEDEF);  }
"union"         { EMIT_TOKEN(TOKEN_UNION);    }
"unsigned"      { EMIT_TOKEN(TOKEN_UNSIGNED); }
"void"          { EMIT_TOKEN(TOKEN_VOID);     }
"volatile"      { EMIT_TOKEN(TOKEN_VOLATILE); }
"while"         { EMIT_TOKEN(TOKEN_WHILE);    }

"."     { EMIT_TOKEN(TOKEN_PERIOD);             }
"->"    { EMIT_TOKEN(TOKEN_ARROW);              }
"++"    { EMIT_TOKEN(TOKEN_INCREMENT);          }
"--"    { EMIT_TOKEN(TOKEN_DECREMENT);          }
"&"     { EMIT_TOKEN(TOKEN_AMPERSAND);          }
"*"     { EMIT_TOKEN(TOKEN_ASTERISK);           }
"+"     { EMIT_TOKEN(TOKEN_PLUS);               }
"-"     { EMIT_TOKEN(TOKEN_MINUS);              }
"~"     { EMIT_TOKEN(TOKEN_TILDE);              }
"!"     { EMIT_TOKEN(TOKEN_EXCLAMATION);        }
"/"     { EMIT_TOKEN(TOKEN_SLASH);              }
"%"     { EMIT_TOKEN(TOKEN_PERCENT);            }
"<<"    { EMIT_TOKEN(TOKEN_LEFT_SHIFT);         }
">>"    { EMIT_TOKEN(TOKEN_RIGHT_SHIFT);        }
"<"     { EMIT_TOKEN(TOKEN_LESS_THAN);          }
">"     { EMIT_TOKEN(TOKEN_GREATER_THAN);       }
"<="    { EMIT_TOKEN(TOKEN_LESS_EQUAL);         }
">="    { EMIT_TOKEN(TOKEN_GREATER_EQUAL);      }
"=="    { EMIT_TOKEN(TOKEN_EQUAL);              }
"!="    { EMIT_TOKEN(TOKEN_NOT_EQUAL);          }
"^"     { EMIT_TOKEN(TOKEN_CARET);              }
"|"     { EMIT_TOKEN(TOKEN_BAR);                }
"&&"    { EMIT_TOKEN(TOKEN_AND);                }
"||"    { EMIT_TOKEN(TOKEN_OR);                 }
"?"     { EMIT_TOKEN(TOKEN_QUESTION);           }
"="     { EMIT_TOKEN(TOKEN_ASSIGN);             }
"*="    { EMIT_TOKEN(TOKEN_ASTERISK_ASSIGN);    }
"/="    { EMIT_TOKEN(TOKEN_SLASH_ASSIGN);       }
"%="    { EMIT_TOKEN(TOKEN_PERCENT_ASSIGN);     }
"+="    { EMIT_TOKEN(TOKEN_PLUS_ASSIGN);        }
"-="    { EMIT_TOKEN(TOKEN_MINUS_ASSIGN);       }
"<<="   { EMIT_TOKEN(TOKEN_LEFT_SHIFT_ASSIGN);  }
">>="   { EMIT_TOKEN(TOKEN_RIGHT_SHIFT_ASSIGN); }
"&="    { EMIT_TOKEN(TOKEN_AMPERSAND_ASSIGN);   }
"^="    { EMIT_TOKEN(TOKEN_CARET_ASSIGN);       }
"|="    { EMIT_TOKEN(TOKEN_BAR_ASSIGN);         }

"["     { EMIT_TOKEN(TOKEN_LEFT_BRACKET);  }
"]"     { EMIT_TOKEN(TOKEN_RIGHT_BRACKET); }
"("     { EMIT_TOKEN(TOKEN_LEFT_PAREN);    }
")"     { EMIT_TOKEN(TOKEN_RIGHT_PAREN);   }
"{"     { EMIT_TOKEN(TOKEN_LEFT_BRACE);    }
"}"     { EMIT_TOKEN(TOKEN_RIGHT_BRACE);   }
","     { EMIT_TOKEN(TOKEN_COMMA);         }
":"     { EMIT_TOKEN(TOKEN_COLON);         }
";"     { EMIT_TOKEN(TOKEN_SEMICOLON);     }
"..."   { EMIT_TOKEN(TOKEN_ELLIPSIS);      }

{identifier} {
  if (scanner_query(yyscanner, yytext)) {
    EMIT_TOKEN(TOKEN_TYPEDEF_IDENTIFIER);
  } else {
    EMIT_TOKEN(TOKEN_IDENTIFIER);
  }
}
{floating-constant}     { EMIT_TOKEN(TOKEN_FLOATING_CONSTANT);  }
{integer-constant}      { EMIT_TOKEN(TOKEN_INTEGER_CONSTANT);   }
{character-constant}    { EMIT_TOKEN(TOKEN_CHARACTER_CONSTANT); }
{string-literal}        { EMIT_TOKEN(TOKEN_STRING_LITERAL);     }
. { yyerror(yyscanner, "unknown token"); }
%%
