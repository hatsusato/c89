%{
#define yyHEADER_H
#include "parser.tab.h"
#define EMIT_TOKEN(token) do {return token;} while(0)
%}

%option noinput
%option nounput
%option bison-bridge
%option reentrant
%option noyywrap
%option never-interactive
%option nodefault
%option warn
%option extra-type="YYSTYPE"

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
{space}

"auto"          { EMIT_TOKEN(KEYWORD_AUTO);     }
"break"         { EMIT_TOKEN(KEYWORD_BREAK);    }
"case"          { EMIT_TOKEN(KEYWORD_CASE);     }
"char"          { EMIT_TOKEN(KEYWORD_CHAR);     }
"const"         { EMIT_TOKEN(KEYWORD_CONST);    }
"continue"      { EMIT_TOKEN(KEYWORD_CONTINUE); }
"default"       { EMIT_TOKEN(KEYWORD_DEFAULT);  }
"do"            { EMIT_TOKEN(KEYWORD_DO);       }
"double"        { EMIT_TOKEN(KEYWORD_DOUBLE);   }
"else"          { EMIT_TOKEN(KEYWORD_ELSE);     }
"enum"          { EMIT_TOKEN(KEYWORD_ENUM);     }
"extern"        { EMIT_TOKEN(KEYWORD_EXTERN);   }
"float"         { EMIT_TOKEN(KEYWORD_FLOAT);    }
"for"           { EMIT_TOKEN(KEYWORD_FOR);      }
"goto"          { EMIT_TOKEN(KEYWORD_GOTO);     }
"if"            { EMIT_TOKEN(KEYWORD_IF);       }
"int"           { EMIT_TOKEN(KEYWORD_INT);      }
"long"          { EMIT_TOKEN(KEYWORD_LONG);     }
"register"      { EMIT_TOKEN(KEYWORD_REGISTER); }
"return"        { EMIT_TOKEN(KEYWORD_RETURN);   }
"signed"        { EMIT_TOKEN(KEYWORD_SIGNED);   }
"sizeof"        { EMIT_TOKEN(KEYWORD_SIZEOF);   }
"short"         { EMIT_TOKEN(KEYWORD_SHORT);    }
"static"        { EMIT_TOKEN(KEYWORD_STATIC);   }
"struct"        { EMIT_TOKEN(KEYWORD_STRUCT);   }
"switch"        { EMIT_TOKEN(KEYWORD_SWITCH);   }
"typedef"       { EMIT_TOKEN(KEYWORD_TYPEDEF);  }
"union"         { EMIT_TOKEN(KEYWORD_UNION);    }
"unsigned"      { EMIT_TOKEN(KEYWORD_UNSIGNED); }
"void"          { EMIT_TOKEN(KEYWORD_VOID);     }
"volatile"      { EMIT_TOKEN(KEYWORD_VOLATILE); }
"while"         { EMIT_TOKEN(KEYWORD_WHILE);    }

"."     { EMIT_TOKEN(OPERATOR_PERIOD);             }
"->"    { EMIT_TOKEN(OPERATOR_ARROW);              }
"++"    { EMIT_TOKEN(OPERATOR_INCREMENT);          }
"--"    { EMIT_TOKEN(OPERATOR_DECREMENT);          }
"&"     { EMIT_TOKEN(OPERATOR_AMPERSAND);          }
"*"     { EMIT_TOKEN(OPERATOR_ASTERISK);           }
"+"     { EMIT_TOKEN(OPERATOR_PLUS);               }
"-"     { EMIT_TOKEN(OPERATOR_MINUS);              }
"~"     { EMIT_TOKEN(OPERATOR_TILDE);              }
"!"     { EMIT_TOKEN(OPERATOR_EXCLAMATION);        }
"/"     { EMIT_TOKEN(OPERATOR_SLASH);              }
"%"     { EMIT_TOKEN(OPERATOR_PERCENT);            }
"<<"    { EMIT_TOKEN(OPERATOR_LEFT_SHIFT);         }
">>"    { EMIT_TOKEN(OPERATOR_RIGHT_SHIFT);        }
"<"     { EMIT_TOKEN(OPERATOR_LESS_THAN);          }
">"     { EMIT_TOKEN(OPERATOR_GREATER_THAN);       }
"<="    { EMIT_TOKEN(OPERATOR_LESS_EQUAL);         }
">="    { EMIT_TOKEN(OPERATOR_GREATER_EQUAL);      }
"=="    { EMIT_TOKEN(OPERATOR_EQUAL);              }
"!="    { EMIT_TOKEN(OPERATOR_NOT_EQUAL);          }
"^"     { EMIT_TOKEN(OPERATOR_CARET);              }
"|"     { EMIT_TOKEN(OPERATOR_BAR);                }
"&&"    { EMIT_TOKEN(OPERATOR_AND);                }
"||"    { EMIT_TOKEN(OPERATOR_OR);                 }
"?"     { EMIT_TOKEN(OPERATOR_QUESTION);           }
"="     { EMIT_TOKEN(OPERATOR_ASSIGN);             }
"*="    { EMIT_TOKEN(OPERATOR_ASTERISK_ASSIGN);    }
"/="    { EMIT_TOKEN(OPERATOR_SLASH_ASSIGN);       }
"%="    { EMIT_TOKEN(OPERATOR_PERCENT_ASSIGN);     }
"+="    { EMIT_TOKEN(OPERATOR_PLUS_ASSIGN);        }
"-="    { EMIT_TOKEN(OPERATOR_MINUS_ASSIGN);       }
"<<="   { EMIT_TOKEN(OPERATOR_LEFT_SHIFT_ASSIGN);  }
">>="   { EMIT_TOKEN(OPERATOR_RIGHT_SHIFT_ASSIGN); }
"&="    { EMIT_TOKEN(OPERATOR_AMPERSAND_ASSIGN);   }
"^="    { EMIT_TOKEN(OPERATOR_CARET_ASSIGN);       }
"|="    { EMIT_TOKEN(OPERATOR_BAR_ASSIGN);         }

"["     { EMIT_TOKEN(PUNCTUATOR_LEFT_BRACKET);  }
"]"     { EMIT_TOKEN(PUNCTUATOR_RIGHT_BRACKET); }
"("     { EMIT_TOKEN(PUNCTUATOR_LEFT_PAREN);    }
")"     { EMIT_TOKEN(PUNCTUATOR_RIGHT_PAREN);   }
"{"     { EMIT_TOKEN(PUNCTUATOR_LEFT_BRACE);    }
"}"     { EMIT_TOKEN(PUNCTUATOR_RIGHT_BRACE);   }
","     { EMIT_TOKEN(PUNCTUATOR_COMMA);         }
":"     { EMIT_TOKEN(PUNCTUATOR_COLON);         }
";"     { EMIT_TOKEN(PUNCTUATOR_SEMICOLON);     }
"..."   { EMIT_TOKEN(PUNCTUATOR_ELLIPSIS);      }

{identifier}            { EMIT_TOKEN(TOKEN_IDENTIFIER);         }
{floating-constant}     { EMIT_TOKEN(TOKEN_FLOATING_CONSTANT);  }
{integer-constant}      { EMIT_TOKEN(TOKEN_INTEGER_CONSTANT);   }
{character-constant}    { EMIT_TOKEN(TOKEN_CHARACTER_CONSTANT); }
{string-literal}        { EMIT_TOKEN(TOKEN_STRING_LITERAL);     }

%%
