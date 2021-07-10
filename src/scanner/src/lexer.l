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

%%
