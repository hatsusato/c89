%code requires {
#include "yyscan_t.h"
}

%define api.pure full
%define api.value.type {const struct cell *}
%param {yyscan_t yyscan}

%code provides {
#include "lexer.h"
#include "yyscan.h"
}

/* 6.1 Lexical elements */
/* 6.1.1 Keywords */
%token TOKEN_AUTO       "auto"
%token TOKEN_BREAK      "break"
%token TOKEN_CASE       "case"
%token TOKEN_CHAR       "char"
%token TOKEN_CONST      "const"
%token TOKEN_CONTINUE   "continue"
%token TOKEN_DEFAULT    "default"
%token TOKEN_DO         "do"
%token TOKEN_DOUBLE     "double"
%token TOKEN_ELSE       "else"
%token TOKEN_ENUM       "enum"
%token TOKEN_EXTERN     "extern"
%token TOKEN_FLOAT      "float"
%token TOKEN_FOR        "for"
%token TOKEN_GOTO       "goto"
%token TOKEN_IF         "if"
%token TOKEN_INT        "int"
%token TOKEN_LONG       "long"
%token TOKEN_REGISTER   "register"
%token TOKEN_RETURN     "return"
%token TOKEN_SHORT      "short"
%token TOKEN_SIGNED     "signed"
%token TOKEN_SIZEOF     "sizeof"
%token TOKEN_STATIC     "static"
%token TOKEN_STRUCT     "struct"
%token TOKEN_SWITCH     "switch"
%token TOKEN_TYPEDEF    "typedef"
%token TOKEN_UNION      "union"
%token TOKEN_UNSIGNED   "unsigned"
%token TOKEN_VOID       "void"
%token TOKEN_VOLATILE   "volatile"
%token TOKEN_WHILE      "while"
/* 6.1.2 Identifiers */
%token TOKEN_IDENTIFIER
%token TOKEN_TYPEDEF_IDENTIFIER
/* 6.1.3 Constants */
%token TOKEN_FLOATING_CONSTANT
%token TOKEN_INTEGER_CONSTANT
%token TOKEN_CHARACTER_CONSTANT
/* 6.1.4 String literals */
%token TOKEN_STRING_LITERAL
/* 6.1.5 Operators */
%token TOKEN_PERIOD             "."
%token TOKEN_ARROW              "->"
%token TOKEN_INCREMENT          "++"
%token TOKEN_DECREMENT          "--"
%token TOKEN_AMPERSAND          "&"
%token TOKEN_ASTERISK           "*"
%token TOKEN_PLUS               "+"
%token TOKEN_MINUS              "-"
%token TOKEN_TILDE              "~"
%token TOKEN_EXCLAMATION        "!"
%token TOKEN_SLASH              "/"
%token TOKEN_PERCENT            "%"
%token TOKEN_LEFT_SHIFT         "<<"
%token TOKEN_RIGHT_SHIFT        ">>"
%token TOKEN_LESS_THAN          "<"
%token TOKEN_GREATER_THAN       ">"
%token TOKEN_LESS_EQUAL         "<="
%token TOKEN_GREATER_EQUAL      ">="
%token TOKEN_EQUAL              "=="
%token TOKEN_NOT_EQUAL          "!="
%token TOKEN_CARET              "^"
%token TOKEN_BAR                "|"
%token TOKEN_AND                "&&"
%token TOKEN_OR                 "||"
%token TOKEN_QUESTION           "?"
%token TOKEN_ASSIGN             "="
%token TOKEN_ASTERISK_ASSIGN    "*="
%token TOKEN_SLASH_ASSIGN       "/="
%token TOKEN_PERCENT_ASSIGN     "%="
%token TOKEN_PLUS_ASSIGN        "+="
%token TOKEN_MINUS_ASSIGN       "-="
%token TOKEN_LEFT_SHIFT_ASSIGN  "<<="
%token TOKEN_RIGHT_SHIFT_ASSIGN ">>="
%token TOKEN_AMPERSAND_ASSIGN   "&="
%token TOKEN_CARET_ASSIGN       "^="
%token TOKEN_BAR_ASSIGN         "|="
/* 6.1.6 Punctuators */
%token TOKEN_LEFT_BRACKET   "["
%token TOKEN_RIGHT_BRACKET  "]"
%token TOKEN_LEFT_PAREN     "("
%token TOKEN_RIGHT_PAREN    ")"
%token TOKEN_LEFT_BRACE     "{"
%token TOKEN_RIGHT_BRACE    "}"
%token TOKEN_COMMA          ","
%token TOKEN_COLON          ":"
%token TOKEN_SEMICOLON      ";"
%token TOKEN_ELLIPSIS       "..."

%nonassoc THEN
%nonassoc "else"

%start top

%%

auto: "auto" { $$ = yyscan_token(yyscan, "auto"); }
;
break: "break" { $$ = yyscan_token(yyscan, "break"); }
;
case: "case" { $$ = yyscan_token(yyscan, "case"); }
;
char: "char" { $$ = yyscan_token(yyscan, "char"); }
;
const: "const" { $$ = yyscan_token(yyscan, "const"); }
;
continue: "continue" { $$ = yyscan_token(yyscan, "continue"); }
;
default: "default" { $$ = yyscan_token(yyscan, "default"); }
;
do: "do" { $$ = yyscan_token(yyscan, "do"); }
;
double: "double" { $$ = yyscan_token(yyscan, "double"); }
;
else: "else" { $$ = yyscan_token(yyscan, "else"); }
;
enum: "enum" { $$ = yyscan_token(yyscan, "enum"); }
;
extern: "extern" { $$ = yyscan_token(yyscan, "extern"); }
;
float: "float" { $$ = yyscan_token(yyscan, "float"); }
;
for: "for" { $$ = yyscan_token(yyscan, "for"); }
;
goto: "goto" { $$ = yyscan_token(yyscan, "goto"); }
;
if: "if" { $$ = yyscan_token(yyscan, "if"); }
;
int: "int" { $$ = yyscan_token(yyscan, "int"); }
;
long: "long" { $$ = yyscan_token(yyscan, "long"); }
;
register: "register" { $$ = yyscan_token(yyscan, "register"); }
;
return: "return" { $$ = yyscan_token(yyscan, "return"); }
;
short: "short" { $$ = yyscan_token(yyscan, "short"); }
;
signed: "signed" { $$ = yyscan_token(yyscan, "signed"); }
;
sizeof: "sizeof" { $$ = yyscan_token(yyscan, "sizeof"); }
;
static: "static" { $$ = yyscan_token(yyscan, "static"); }
;
struct: "struct" { $$ = yyscan_token(yyscan, "struct"); }
;
switch: "switch" { $$ = yyscan_token(yyscan, "switch"); }
;
typedef: "typedef" { $$ = yyscan_token(yyscan, "typedef"); }
;
union: "union" { $$ = yyscan_token(yyscan, "union"); }
;
unsigned: "unsigned" { $$ = yyscan_token(yyscan, "unsigned"); }
;
void: "void" { $$ = yyscan_token(yyscan, "void"); }
;
volatile: "volatile" { $$ = yyscan_token(yyscan, "volatile"); }
;
while: "while" { $$ = yyscan_token(yyscan, "while"); }
;

period: "." { $$ = yyscan_token(yyscan, "period"); }
;
arrow: "->" { $$ = yyscan_token(yyscan, "arrow"); }
;
increment: "++" { $$ = yyscan_token(yyscan, "increment"); }
;
decrement: "--" { $$ = yyscan_token(yyscan, "decrement"); }
;
ampersand: "&" { $$ = yyscan_token(yyscan, "ampersand"); }
;
asterisk: "*" { $$ = yyscan_token(yyscan, "asterisk"); }
;
plus: "+" { $$ = yyscan_token(yyscan, "plus"); }
;
minus: "-" { $$ = yyscan_token(yyscan, "minus"); }
;
tilde: "~" { $$ = yyscan_token(yyscan, "tilde"); }
;
exclamation: "!" { $$ = yyscan_token(yyscan, "exclamation"); }
;
slash: "/" { $$ = yyscan_token(yyscan, "slash"); }
;
percent: "%" { $$ = yyscan_token(yyscan, "percent"); }
;
left-shift: "<<" { $$ = yyscan_token(yyscan, "left-shift"); }
;
right-shift: ">>" { $$ = yyscan_token(yyscan, "right-shift"); }
;
less-than: "<" { $$ = yyscan_token(yyscan, "less-than"); }
;
greater-than: ">" { $$ = yyscan_token(yyscan, "greater-than"); }
;
less-equal: "<=" { $$ = yyscan_token(yyscan, "less-equal"); }
;
greater-equal: ">=" { $$ = yyscan_token(yyscan, "greater-equal"); }
;
equal: "==" { $$ = yyscan_token(yyscan, "equal"); }
;
not-equal: "!=" { $$ = yyscan_token(yyscan, "not-equal"); }
;
caret: "^" { $$ = yyscan_token(yyscan, "caret"); }
;
bar: "|" { $$ = yyscan_token(yyscan, "bar"); }
;
and: "&&" { $$ = yyscan_token(yyscan, "and"); }
;
or: "||" { $$ = yyscan_token(yyscan, "or"); }
;
question: "?" { $$ = yyscan_token(yyscan, "question"); }
;
assign: "=" { $$ = yyscan_token(yyscan, "assign"); }
;
asterisk-assign: "*=" { $$ = yyscan_token(yyscan, "asterisk-assign"); }
;
slash-assign: "/=" { $$ = yyscan_token(yyscan, "slash-assign"); }
;
percent-assign: "%=" { $$ = yyscan_token(yyscan, "percent-assign"); }
;
plus-assign: "+=" { $$ = yyscan_token(yyscan, "plus-assign"); }
;
minus-assign: "-=" { $$ = yyscan_token(yyscan, "minus-assign"); }
;
left-shift-assign: "<<=" { $$ = yyscan_token(yyscan, "left-shift-assign"); }
;
right-shift-assign: ">>=" { $$ = yyscan_token(yyscan, "right-shift-assign"); }
;
ampersand-assign: "&=" { $$ = yyscan_token(yyscan, "ampersand-assign"); }
;
caret-assign: "^=" { $$ = yyscan_token(yyscan, "caret-assign"); }
;
bar-assign: "|=" { $$ = yyscan_token(yyscan, "bar-assign"); }
;

left-bracket: "[" { $$ = yyscan_token(yyscan, "left-bracket"); }
;
right-bracket: "]" { $$ = yyscan_token(yyscan, "right-bracket"); }
;
left-paren: "(" { $$ = yyscan_token(yyscan, "left-paren"); }
;
right-paren: ")" { $$ = yyscan_token(yyscan, "right-paren"); }
;
left-brace: "{" { $$ = yyscan_token(yyscan, "left-brace"); }
;
right-brace: "}" { $$ = yyscan_token(yyscan, "right-brace"); }
;
comma: "," { $$ = yyscan_token(yyscan, "comma"); }
;
colon: ":" { $$ = yyscan_token(yyscan, "colon"); }
;
semicolon: ";" { $$ = yyscan_token(yyscan, "semicolon"); }
;
ellipsis: "..." { $$ = yyscan_token(yyscan, "ellipsis"); }
;

/* 6.1 Lexical elements */
identifier.opt
: %empty { $$ = yyscan_nil(); }
| identifier
;
identifier
: TOKEN_IDENTIFIER {}
;
typedef-identifier
: TOKEN_TYPEDEF_IDENTIFIER {}
;
floating-constant
: TOKEN_FLOATING_CONSTANT {}
;
integer-constant
: TOKEN_INTEGER_CONSTANT {}
;
enumeration-constant
: TOKEN_IDENTIFIER {}
;
character-constant
: TOKEN_CHARACTER_CONSTANT {}
;
string-literal
: TOKEN_STRING_LITERAL {}
;
string-constant
: string-literal {}
| string-constant string-literal {}
;

/* 6.3 Expressions */
primary-expression
: identifier
| floating-constant
| integer-constant
| character-constant
| string-constant
| left-paren expression right-paren {}
;
postfix-expression
: primary-expression
| postfix-expression postfix-expression.suffix {}
;
postfix-expression.suffix
: left-bracket expression right-bracket {}
| left-paren argument-expression-list.opt right-paren {}
| period identifier {}
| arrow identifier {}
| increment {}
| decrement {}
;
argument-expression-list.opt
: %empty { $$ = yyscan_nil(); }
| argument-expression-list
;
argument-expression-list
: assignment-expression {}
| argument-expression-list comma assignment-expression {}
;
unary-expression
: postfix-expression
| increment unary-expression {}
| decrement unary-expression {}
| unary-operator cast-expression {}
| sizeof unary-expression {}
| sizeof left-paren type-name right-paren {}
;
unary-operator
: ampersand
| asterisk
| plus
| minus
| tilde
| exclamation
;
cast-expression
: unary-expression
| left-paren type-name right-paren cast-expression {}
;
multiplicative-expression
: cast-expression
| multiplicative-expression multiplicative-operator cast-expression {}
;
multiplicative-operator
: asterisk
| slash
| percent
;
additive-expression
: multiplicative-expression
| additive-expression additive-operator multiplicative-expression {}
;
additive-operator
: plus
| minus
;
shift-expression
: additive-expression
| shift-expression shift-operator additive-expression {}
;
shift-operator
: left-shift
| right-shift
;
relational-expression
: shift-expression
| relational-expression relational-operator shift-expression {}
;
relational-operator
: less-than
| greater-than
| less-equal
| greater-equal
;
equality-expression
: relational-expression
| equality-expression equality-operator relational-expression {}
;
equality-operator
: equal
| not-equal
;
and-expression
: equality-expression
| and-expression ampersand equality-expression {}
;
exclusive-or-expression
: and-expression
| exclusive-or-expression caret and-expression {}
;
inclusive-or-expression
: exclusive-or-expression
| inclusive-or-expression bar exclusive-or-expression {}
;
logical-and-expression
: inclusive-or-expression
| logical-and-expression and inclusive-or-expression {}
;
logical-or-expression
: logical-and-expression
| logical-or-expression or logical-and-expression {}
;
conditional-expression
: logical-or-expression
| logical-or-expression question expression colon conditional-expression {}
;
assignment-expression
: conditional-expression
| unary-expression assignment-operator assignment-expression {}
;
assignment-operator
: assign
| asterisk-assign
| slash-assign
| percent-assign
| plus-assign
| minus-assign
| left-shift-assign
| right-shift-assign
| ampersand-assign
| caret-assign
| bar-assign
;
expression.opt
: %empty { $$ = yyscan_nil(); }
| expression
;
expression
: assignment-expression
| expression comma assignment-expression {}
;

/* 6.4 Constant expressions */
constant-expression.opt
: %empty { $$ = yyscan_nil(); }
| constant-expression
;
constant-expression
: conditional-expression {}
;

/* 6.5 Declarations */
declaration
: declaration-specifiers init-declarator-list.opt semicolon {}
;
declaration-specifiers
: declaration-specifier {}
| declaration-specifiers declaration-specifier {}
;
declaration-specifier
: storage-class-specifier
| type-specifier
| type-qualifier
;
init-declarator-list.opt
: %empty { $$ = yyscan_nil(); }
| init-declarator-list
;
init-declarator-list
: init-declarator {}
| init-declarator-list comma init-declarator {}
;
init-declarator
: declarator {}
| declarator assign initializer {}
;
storage-class-specifier
: typedef
| extern
| static
| auto
| register
;
type-specifier
: void
| char
| short
| int
| long
| float
| double
| signed
| unsigned
| struct-or-union-specifier
| enum-specifier
| typedef-name
;
struct-or-union-specifier
: struct-or-union identifier.opt left-brace struct-declaration-list right-brace {}
| struct-or-union identifier {}
;
struct-or-union
: struct
| union
;
struct-declaration-list
: struct-declaration {}
| struct-declaration-list struct-declaration {}
;
struct-declaration
: specifier-qualifier-list struct-declarator-list semicolon {}
;
specifier-qualifier-list
: specifier-qualifier {}
| specifier-qualifier-list specifier-qualifier {}
;
specifier-qualifier
: type-specifier
| type-qualifier
;
struct-declarator-list
: struct-declarator {}
| struct-declarator-list comma struct-declarator {}
;
struct-declarator
: declarator {}
| declarator.opt colon constant-expression {}
;
enum-specifier
: enum identifier.opt left-brace enumerator-list right-brace {}
| enum identifier {}
;
enumerator-list
: enumerator {}
| enumerator-list comma enumerator {}
;
enumerator
: enumeration-constant {}
| enumeration-constant assign constant-expression {}
;
type-qualifier
: const
| volatile
;
declarator.opt
: %empty { $$ = yyscan_nil(); }
| declarator
;
declarator
: direct-declarator {}
| pointer direct-declarator {}
;
direct-declarator
: identifier {}
| left-paren declarator right-paren {}
| direct-declarator direct-declarator.suffix {}
;
direct-declarator.suffix
: left-bracket constant-expression.opt right-bracket {}
| left-paren parameter-type-list.opt right-paren {}
| left-paren identifier-list right-paren {}
;
pointer
: asterisk type-qualifier-list.opt {}
| pointer asterisk type-qualifier-list.opt {}
;
type-qualifier-list.opt
: %empty { $$ = yyscan_nil(); }
| type-qualifier-list
;
type-qualifier-list
: type-qualifier {}
| type-qualifier-list type-qualifier {}
;
parameter-type-list.opt
: %empty { $$ = yyscan_nil(); }
| parameter-type-list
;
parameter-type-list
: parameter-list
| parameter-list comma ellipsis {}
;
parameter-list
: parameter-declaration {}
| parameter-list comma parameter-declaration {}
;
parameter-declaration
: declaration-specifiers declarator {}
| declaration-specifiers abstract-declarator.opt {}
;
identifier-list
: identifier {}
| identifier-list comma identifier {}
;
type-name
: specifier-qualifier-list abstract-declarator.opt {}
;
abstract-declarator.opt
: %empty { $$ = yyscan_nil(); }
| abstract-declarator
;
abstract-declarator
: pointer {}
| direct-abstract-declarator {}
| pointer direct-abstract-declarator {}
;
direct-abstract-declarator
: left-paren abstract-declarator right-paren {}
| direct-abstract-declarator.suffix
| direct-abstract-declarator direct-abstract-declarator.suffix {}
;
direct-abstract-declarator.suffix
: left-bracket constant-expression.opt right-bracket {}
| left-paren parameter-type-list.opt right-paren {}
;
typedef-name
: typedef-identifier {}
;
initializer
: assignment-expression
| left-brace initializer-list right-brace {}
| left-brace initializer-list comma right-brace {}
;
initializer-list
: initializer {}
| initializer-list comma initializer {}
;

/* 6.6 Statements */
statement
: labeled-statement
| compound-statement
| expression-statement
| selection-statement
| iteration-statement
| jump-statement
;
labeled-statement
: identifier colon statement {}
| case constant-expression colon statement {}
| default colon statement {}
;
compound-statement
: left-brace declaration-list.opt statement-list.opt right-brace {}
;
declaration-list.opt
: %empty { $$ = yyscan_nil(); }
| declaration-list
;
declaration-list
: declaration {}
| declaration-list declaration {}
;
statement-list.opt
: %empty { $$ = yyscan_nil(); }
| statement-list
;
statement-list
: statement {}
| statement-list statement {}
;
expression-statement
: expression.opt semicolon {}
;
selection-statement
: if left-paren expression right-paren statement %prec THEN {}
| if left-paren expression right-paren statement else statement {}
| switch left-paren expression right-paren statement {}
;
iteration-statement
: while left-paren expression right-paren statement {}
| do statement while left-paren expression right-paren semicolon {}
| for left-paren expression.opt semicolon expression.opt semicolon expression.opt right-paren statement {}
;
jump-statement
: goto identifier semicolon {}
| continue semicolon {}
| break semicolon {}
| return expression.opt semicolon {}
;

/* 6.7 External definitions */
top
: translation-unit {}
;
translation-unit
: external-declaration {}
| translation-unit external-declaration {}
;
external-declaration
: function-definition
| declaration {}
;
function-definition
: declarator declaration-list.opt compound-statement {}
| declaration-specifiers declarator declaration-list.opt compound-statement {}
;

%%
