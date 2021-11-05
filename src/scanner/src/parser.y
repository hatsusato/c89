%code requires {
#include "yyscan_t.h"
}

%define api.pure full
%define api.value.type {YYSCAN_TYPE}
%param {yyscan_t YYSCAN_PARAM}

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

auto: "auto" { $$ = YYSCAN_STR(SYMBOL_AUTO); }
;
break: "break" { $$ = YYSCAN_STR(SYMBOL_BREAK); }
;
case: "case" { $$ = YYSCAN_STR(SYMBOL_CASE); }
;
char: "char" { $$ = YYSCAN_STR(SYMBOL_CHAR); }
;
const: "const" { $$ = YYSCAN_STR(SYMBOL_CONST); }
;
continue: "continue" { $$ = YYSCAN_STR(SYMBOL_CONTINUE); }
;
default: "default" { $$ = YYSCAN_STR(SYMBOL_DEFAULT); }
;
do: "do" { $$ = YYSCAN_STR(SYMBOL_DO); }
;
double: "double" { $$ = YYSCAN_STR(SYMBOL_DOUBLE); }
;
else: "else" { $$ = YYSCAN_STR(SYMBOL_ELSE); }
;
enum: "enum" { $$ = YYSCAN_STR(SYMBOL_ENUM); }
;
extern: "extern" { $$ = YYSCAN_STR(SYMBOL_EXTERN); }
;
float: "float" { $$ = YYSCAN_STR(SYMBOL_FLOAT); }
;
for: "for" { $$ = YYSCAN_STR(SYMBOL_FOR); }
;
goto: "goto" { $$ = YYSCAN_STR(SYMBOL_GOTO); }
;
if: "if" { $$ = YYSCAN_STR(SYMBOL_IF); }
;
int: "int" { $$ = YYSCAN_STR(SYMBOL_INT); }
;
long: "long" { $$ = YYSCAN_STR(SYMBOL_LONG); }
;
register: "register" { $$ = YYSCAN_STR(SYMBOL_REGISTER); }
;
return: "return" { $$ = YYSCAN_STR(SYMBOL_RETURN); }
;
short: "short" { $$ = YYSCAN_STR(SYMBOL_SHORT); }
;
signed: "signed" { $$ = YYSCAN_STR(SYMBOL_SIGNED); }
;
sizeof: "sizeof" { $$ = YYSCAN_STR(SYMBOL_SIZEOF); }
;
static: "static" { $$ = YYSCAN_STR(SYMBOL_STATIC); }
;
struct: "struct" { $$ = YYSCAN_STR(SYMBOL_STRUCT); }
;
switch: "switch" { $$ = YYSCAN_STR(SYMBOL_SWITCH); }
;
typedef: "typedef" { $$ = YYSCAN_STR(SYMBOL_TYPEDEF); }
;
union: "union" { $$ = YYSCAN_STR(SYMBOL_UNION); }
;
unsigned: "unsigned" { $$ = YYSCAN_STR(SYMBOL_UNSIGNED); }
;
void: "void" { $$ = YYSCAN_STR(SYMBOL_VOID); }
;
volatile: "volatile" { $$ = YYSCAN_STR(SYMBOL_VOLATILE); }
;
while: "while" { $$ = YYSCAN_STR(SYMBOL_WHILE); }
;

period: "." { $$ = YYSCAN_STR(SYMBOL_PERIOD); }
;
arrow: "->" { $$ = YYSCAN_STR(SYMBOL_ARROW); }
;
increment: "++" { $$ = YYSCAN_STR(SYMBOL_INCREMENT); }
;
decrement: "--" { $$ = YYSCAN_STR(SYMBOL_DECREMENT); }
;
ampersand: "&" { $$ = YYSCAN_STR(SYMBOL_AMPERSAND); }
;
asterisk: "*" { $$ = YYSCAN_STR(SYMBOL_ASTERISK); }
;
plus: "+" { $$ = YYSCAN_STR(SYMBOL_PLUS); }
;
minus: "-" { $$ = YYSCAN_STR(SYMBOL_MINUS); }
;
tilde: "~" { $$ = YYSCAN_STR(SYMBOL_TILDE); }
;
exclamation: "!" { $$ = YYSCAN_STR(SYMBOL_EXCLAMATION); }
;
slash: "/" { $$ = YYSCAN_STR(SYMBOL_SLASH); }
;
percent: "%" { $$ = YYSCAN_STR(SYMBOL_PERCENT); }
;
left-shift: "<<" { $$ = YYSCAN_STR(SYMBOL_LEFT_SHIFT); }
;
right-shift: ">>" { $$ = YYSCAN_STR(SYMBOL_RIGHT_SHIFT); }
;
less-than: "<" { $$ = YYSCAN_STR(SYMBOL_LESS_THAN); }
;
greater-than: ">" { $$ = YYSCAN_STR(SYMBOL_GREATER_THAN); }
;
less-equal: "<=" { $$ = YYSCAN_STR(SYMBOL_LESS_EQUAL); }
;
greater-equal: ">=" { $$ = YYSCAN_STR(SYMBOL_GREATER_EQUAL); }
;
equal: "==" { $$ = YYSCAN_STR(SYMBOL_EQUAL); }
;
not-equal: "!=" { $$ = YYSCAN_STR(SYMBOL_NOT_EQUAL); }
;
caret: "^" { $$ = YYSCAN_STR(SYMBOL_CARET); }
;
bar: "|" { $$ = YYSCAN_STR(SYMBOL_BAR); }
;
and: "&&" { $$ = YYSCAN_STR(SYMBOL_AND); }
;
or: "||" { $$ = YYSCAN_STR(SYMBOL_OR); }
;
question: "?" { $$ = YYSCAN_STR(SYMBOL_QUESTION); }
;
assign: "=" { $$ = YYSCAN_STR(SYMBOL_ASSIGN); }
;
asterisk-assign: "*=" { $$ = YYSCAN_STR(SYMBOL_ASTERISK_ASSIGN); }
;
slash-assign: "/=" { $$ = YYSCAN_STR(SYMBOL_SLASH_ASSIGN); }
;
percent-assign: "%=" { $$ = YYSCAN_STR(SYMBOL_PERCENT_ASSIGN); }
;
plus-assign: "+=" { $$ = YYSCAN_STR(SYMBOL_PLUS_ASSIGN); }
;
minus-assign: "-=" { $$ = YYSCAN_STR(SYMBOL_MINUS_ASSIGN); }
;
left-shift-assign: "<<=" { $$ = YYSCAN_STR(SYMBOL_LEFT_SHIFT_ASSIGN); }
;
right-shift-assign: ">>=" { $$ = YYSCAN_STR(SYMBOL_RIGHT_SHIFT_ASSIGN); }
;
ampersand-assign: "&=" { $$ = YYSCAN_STR(SYMBOL_AMPERSAND_ASSIGN); }
;
caret-assign: "^=" { $$ = YYSCAN_STR(SYMBOL_CARET_ASSIGN); }
;
bar-assign: "|=" { $$ = YYSCAN_STR(SYMBOL_BAR_ASSIGN); }
;

left-bracket: "[" { $$ = YYSCAN_STR(SYMBOL_LEFT_BRACKET); }
;
right-bracket: "]" { $$ = YYSCAN_STR(SYMBOL_RIGHT_BRACKET); }
;
left-paren: "(" { $$ = YYSCAN_STR(SYMBOL_LEFT_PAREN); }
;
right-paren: ")" { $$ = YYSCAN_STR(SYMBOL_RIGHT_PAREN); }
;
left-brace: "{" { $$ = YYSCAN_STR(SYMBOL_LEFT_BRACE); }
;
right-brace: "}" { $$ = YYSCAN_STR(SYMBOL_RIGHT_BRACE); }
;
comma: "," { $$ = YYSCAN_STR(SYMBOL_COMMA); }
;
colon: ":" { $$ = YYSCAN_STR(SYMBOL_COLON); }
;
semicolon: ";" { $$ = YYSCAN_STR(SYMBOL_SEMICOLON); }
;
ellipsis: "..." { $$ = YYSCAN_STR(SYMBOL_ELLIPSIS); }
;

/* 6.1 Lexical elements */
identifier.opt
: %empty {
  $$ = YYSCAN_OBJ();
}
| identifier
;
identifier
: TOKEN_IDENTIFIER {
  $$ = YYSCAN_TOKEN();
}
;
typedef-identifier
: TOKEN_TYPEDEF_IDENTIFIER {
  $$ = YYSCAN_TOKEN();
}
;
floating-constant
: TOKEN_FLOATING_CONSTANT {
  $$ = YYSCAN_TOKEN();
}
;
integer-constant
: TOKEN_INTEGER_CONSTANT {
  $$ = YYSCAN_TOKEN();
}
;
enumeration-constant
: TOKEN_IDENTIFIER {
  $$ = YYSCAN_TOKEN();
}
;
character-constant
: TOKEN_CHARACTER_CONSTANT {
  $$ = YYSCAN_TOKEN();
}
;
string-literal
: TOKEN_STRING_LITERAL {
  $$ = YYSCAN_TOKEN();
}
;

/* 6.3 Expressions */
primary-expression
: identifier {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_IDENTIFIER, $1);
}
| floating-constant {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_FLOATING_CONSTANT, $1);
}
| integer-constant {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_INTEGER_CONSTANT, $1);
}
| character-constant {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_CHARACTER_CONSTANT, $1);
}
| string-literal {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_STRING_LITERAL, $1);
}
| left-paren expression right-paren {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_LEFT_PAREN, $1);
  YYSCAN_SET($$, SYMBOL_EXPRESSION, $2);
  YYSCAN_SET($$, SYMBOL_RIGHT_PAREN, $3);
  $$ = YYSCAN_TAG(SYMBOL_PRIMARY_EXPRESSION, $$);
}
;
postfix-expression
: primary-expression
| postfix-expression left-bracket expression right-bracket {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_POSTFIX_EXPRESSION, $1);
  YYSCAN_SET($$, SYMBOL_LEFT_BRACKET, $2);
  YYSCAN_SET($$, SYMBOL_EXPRESSION, $3);
  YYSCAN_SET($$, SYMBOL_RIGHT_BRACKET, $4);
  $$ = YYSCAN_TAG(SYMBOL_POSTFIX_EXPRESSION, $$);
}
| postfix-expression left-paren argument-expression-list.opt right-paren {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_POSTFIX_EXPRESSION, $1);
  YYSCAN_SET($$, SYMBOL_LEFT_PAREN, $2);
  YYSCAN_SET($$, SYMBOL_ARGUMENT_EXPRESSION_LIST, $3);
  YYSCAN_SET($$, SYMBOL_RIGHT_PAREN, $4);
  $$ = YYSCAN_TAG(SYMBOL_POSTFIX_EXPRESSION, $$);
}
| postfix-expression period identifier {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_POSTFIX_EXPRESSION, $1);
  YYSCAN_SET($$, SYMBOL_PERIOD, $2);
  YYSCAN_SET($$, SYMBOL_IDENTIFIER, $3);
  $$ = YYSCAN_TAG(SYMBOL_POSTFIX_EXPRESSION, $$);
}
| postfix-expression arrow identifier {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_POSTFIX_EXPRESSION, $1);
  YYSCAN_SET($$, SYMBOL_ARROW, $2);
  YYSCAN_SET($$, SYMBOL_IDENTIFIER, $3);
  $$ = YYSCAN_TAG(SYMBOL_POSTFIX_EXPRESSION, $$);
}
| postfix-expression increment {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_POSTFIX_EXPRESSION, $1);
  YYSCAN_SET($$, SYMBOL_INCREMENT, $2);
  $$ = YYSCAN_TAG(SYMBOL_POSTFIX_EXPRESSION, $$);
}
| postfix-expression decrement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_POSTFIX_EXPRESSION, $1);
  YYSCAN_SET($$, SYMBOL_DECREMENT, $2);
  $$ = YYSCAN_TAG(SYMBOL_POSTFIX_EXPRESSION, $$);
}
;
argument-expression-list.opt
: %empty {
  $$ = YYSCAN_ARR();
}
| argument-expression-list
;
argument-expression-list
: assignment-expression {
  $1 = YYSCAN_TAG(SYMBOL_EXPRESSION, $1);
  $$ = YYSCAN_PUSH(YYSCAN_ARR(), $1);
}
| argument-expression-list comma assignment-expression {
  $3 = YYSCAN_TAG(SYMBOL_EXPRESSION, $3);
  $$ = YYSCAN_PUSH($1, $3);
}
;
unary-expression
: postfix-expression
| increment unary-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_INCREMENT, $1);
  YYSCAN_SET($$, SYMBOL_UNARY_EXPRESSION, $2);
  $$ = YYSCAN_TAG(SYMBOL_UNARY_EXPRESSION, $$);
}
| decrement unary-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_DECREMENT, $1);
  YYSCAN_SET($$, SYMBOL_UNARY_EXPRESSION, $2);
  $$ = YYSCAN_TAG(SYMBOL_UNARY_EXPRESSION, $$);
}
| unary-operator cast-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_UNARY_OPERATOR, $1);
  YYSCAN_SET($$, SYMBOL_CAST_EXPRESSION, $2);
  $$ = YYSCAN_TAG(SYMBOL_UNARY_EXPRESSION, $$);
}
| sizeof unary-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_SIZEOF, $1);
  YYSCAN_SET($$, SYMBOL_UNARY_EXPRESSION, $2);
  $$ = YYSCAN_TAG(SYMBOL_UNARY_EXPRESSION, $$);
}
| sizeof left-paren type-name right-paren {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_SIZEOF, $1);
  YYSCAN_SET($$, SYMBOL_LEFT_PAREN, $2);
  YYSCAN_SET($$, SYMBOL_TYPE_NAME, $3);
  YYSCAN_SET($$, SYMBOL_RIGHT_PAREN, $4);
  $$ = YYSCAN_TAG(SYMBOL_UNARY_EXPRESSION, $$);
}
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
| left-paren type-name right-paren cast-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_LEFT_PAREN, $1);
  YYSCAN_SET($$, SYMBOL_TYPE_NAME, $2);
  YYSCAN_SET($$, SYMBOL_RIGHT_PAREN, $3);
  YYSCAN_SET($$, SYMBOL_CAST_EXPRESSION, $4);
  $$ = YYSCAN_TAG(SYMBOL_CAST_EXPRESSION, $$);
}
;
multiplicative-expression
: cast-expression
| multiplicative-expression multiplicative-operator cast-expression {
  $$ = YYSCAN_BINOP($1, $2, $3);
  $$ = YYSCAN_TAG(SYMBOL_MULTIPLICATIVE_EXPRESSION, $$);
}
;
multiplicative-operator
: asterisk
| slash
| percent
;
additive-expression
: multiplicative-expression
| additive-expression additive-operator multiplicative-expression {
  $$ = YYSCAN_BINOP($1, $2, $3);
  $$ = YYSCAN_TAG(SYMBOL_ADDITIVE_EXPRESSION, $$);
}
;
additive-operator
: plus
| minus
;
shift-expression
: additive-expression
| shift-expression shift-operator additive-expression {
  $$ = YYSCAN_BINOP($1, $2, $3);
  $$ = YYSCAN_TAG(SYMBOL_SHIFT_EXPRESSION, $$);
}
;
shift-operator
: left-shift
| right-shift
;
relational-expression
: shift-expression
| relational-expression relational-operator shift-expression {
  $$ = YYSCAN_BINOP($1, $2, $3);
  $$ = YYSCAN_TAG(SYMBOL_RELATIONAL_EXPRESSION, $$);
}
;
relational-operator
: less-than
| greater-than
| less-equal
| greater-equal
;
equality-expression
: relational-expression
| equality-expression equality-operator relational-expression {
  $$ = YYSCAN_BINOP($1, $2, $3);
  $$ = YYSCAN_TAG(SYMBOL_EQUALITY_EXPRESSION, $$);
}
;
equality-operator
: equal
| not-equal
;
and-expression
: equality-expression
| and-expression ampersand equality-expression {
  $$ = YYSCAN_BINOP($1, $2, $3);
  $$ = YYSCAN_TAG(SYMBOL_AND_EXPRESSION, $$);
}
;
exclusive-or-expression
: and-expression
| exclusive-or-expression caret and-expression {
  $$ = YYSCAN_BINOP($1, $2, $3);
  $$ = YYSCAN_TAG(SYMBOL_EXCLUSIVE_OR_EXPRESSION, $$);
}
;
inclusive-or-expression
: exclusive-or-expression
| inclusive-or-expression bar exclusive-or-expression {
  $$ = YYSCAN_BINOP($1, $2, $3);
  $$ = YYSCAN_TAG(SYMBOL_INCLUSIVE_OR_EXPRESSION, $$);
}
;
logical-and-expression
: inclusive-or-expression
| logical-and-expression and inclusive-or-expression {
  $$ = YYSCAN_BINOP($1, $2, $3);
  $$ = YYSCAN_TAG(SYMBOL_LOGICAL_AND_EXPRESSION, $$);
}
;
logical-or-expression
: logical-and-expression
| logical-or-expression or logical-and-expression {
  $$ = YYSCAN_BINOP($1, $2, $3);
  $$ = YYSCAN_TAG(SYMBOL_LOGICAL_OR_EXPRESSION, $$);
}
;
conditional-expression
: logical-or-expression
| logical-or-expression question expression colon conditional-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_LOGICAL_OR_EXPRESSION, $1);
  YYSCAN_SET($$, SYMBOL_QUESTION, $2);
  YYSCAN_SET($$, SYMBOL_EXPRESSION, $3);
  YYSCAN_SET($$, SYMBOL_COLON, $4);
  YYSCAN_SET($$, SYMBOL_CONDITIONAL_EXPRESSION, $5);
  $$ = YYSCAN_TAG(SYMBOL_CONDITIONAL_EXPRESSION, $$);
}
;
assignment-expression
: conditional-expression
| unary-expression assignment-operator assignment-expression {
  $$ = YYSCAN_BINOP($1, $2, $3);
  $$ = YYSCAN_TAG(SYMBOL_ASSIGNMENT_EXPRESSION, $$);
}
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
: %empty {
  $$ = YYSCAN_OBJ();
}
| expression
;
expression
: assignment-expression
| expression comma assignment-expression {
  $$ = YYSCAN_BINOP($1, $2, $3);
}
;

/* 6.4 Constant expressions */
constant-expression.opt
: %empty {
  $$ = YYSCAN_OBJ();
}
| constant-expression
;
constant-expression
: conditional-expression
;

/* 6.5 Declarations */
declaration
: declaration-specifiers init-declarator-list.opt semicolon {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_DECLARATION_SPECIFIERS, $1);
  YYSCAN_SET($$, SYMBOL_INIT_DECLARATOR_LIST, $2);
  YYSCAN_SET($$, SYMBOL_SEMICOLON, $3);
}
;
declaration-specifiers
: declaration-specifier {
  $$ = YYSCAN_PUSH(YYSCAN_ARR(), $1);
}
| declaration-specifiers declaration-specifier {
  $$ = YYSCAN_PUSH($1, $2);
}
;
declaration-specifier
: storage-class-specifier {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_STORAGE_CLASS_SPECIFIER, $1);
}
| type-specifier {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_TYPE_SPECIFIER, $1);
}
| type-qualifier {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_TYPE_QUALIFIER, $1);
}
;
init-declarator-list.opt
: %empty {
  $$ = YYSCAN_ARR();
}
| init-declarator-list
;
init-declarator-list
: init-declarator {
  $1 = YYSCAN_TAG(SYMBOL_INIT_DECLARATOR, $1);
  $$ = YYSCAN_PUSH(YYSCAN_ARR(), $1);
}
| init-declarator-list comma init-declarator {
  $3 = YYSCAN_TAG(SYMBOL_INIT_DECLARATOR, $3);
  $$ = YYSCAN_PUSH($1, $3);
}
;
init-declarator
: declarator {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_DECLARATOR, $1);
}
| declarator assign initializer {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_DECLARATOR, $1);
  YYSCAN_SET($$, SYMBOL_ASSIGN, $2);
  YYSCAN_SET($$, SYMBOL_INITIALIZER, $3);
}
;
storage-class-specifier
: typedef {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_TYPEDEF, $1);
}
| extern {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_EXTERN, $1);
}
| static {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_STATIC, $1);
}
| auto {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_AUTO, $1);
}
| register {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_REGISTER, $1);
}
;
type-specifier
: void {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_VOID, $1);
}
| char {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_CHAR, $1);
}
| short {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_SHORT, $1);
}
| int {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_INT, $1);
}
| long {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_LONG, $1);
}
| float {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_FLOAT, $1);
}
| double {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_DOUBLE, $1);
}
| signed {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_SIGNED, $1);
}
| unsigned {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_UNSIGNED, $1);
}
| struct-or-union-specifier {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_STRUCT_OR_UNION_SPECIFIER, $1);
}
| enum-specifier {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_ENUM_SPECIFIER, $1);
}
| typedef-name {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_TYPEDEF_NAME, $1);
}
;
struct-or-union-specifier
: struct-or-union identifier.opt left-brace struct-declaration-list right-brace {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_STRUCT_OR_UNION, $1);
  YYSCAN_SET($$, SYMBOL_IDENTIFIER, $2);
  YYSCAN_SET($$, SYMBOL_LEFT_BRACE, $3);
  YYSCAN_SET($$, SYMBOL_STRUCT_DECLARATION_LIST, $4);
  YYSCAN_SET($$, SYMBOL_RIGHT_BRACE, $5);
}
| struct-or-union identifier {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_STRUCT_OR_UNION, $1);
  YYSCAN_SET($$, SYMBOL_IDENTIFIER, $2);
}
;
struct-or-union
: struct {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_STRUCT, $1);
}
| union {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_UNION, $1);
}
;
struct-declaration-list
: struct-declaration {
  $1 = YYSCAN_TAG(SYMBOL_STRUCT_DECLARATION, $1);
  $$ = YYSCAN_PUSH(YYSCAN_ARR(), $1);
}
| struct-declaration-list struct-declaration {
  $2 = YYSCAN_TAG(SYMBOL_STRUCT_DECLARATION, $2);
  $$ = YYSCAN_PUSH($1, $2);
}
;
struct-declaration
: specifier-qualifier-list struct-declarator-list semicolon {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_SPECIFIER_QUALIFIER_LIST, $1);
  YYSCAN_SET($$, SYMBOL_STRUCT_DECLARATOR_LIST, $2);
  YYSCAN_SET($$, SYMBOL_SEMICOLON, $3);
}
;
specifier-qualifier-list
: specifier-qualifier {
  $1 = YYSCAN_TAG(SYMBOL_SPECIFIER_QUALIFIER, $1);
  $$ = YYSCAN_PUSH(YYSCAN_ARR(), $1);
}
| specifier-qualifier-list specifier-qualifier {
  $2 = YYSCAN_TAG(SYMBOL_SPECIFIER_QUALIFIER, $2);
  $$ = YYSCAN_PUSH($1, $2);
}
;
specifier-qualifier
: type-specifier {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_TYPE_SPECIFIER, $1);
}
| type-qualifier {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_TYPE_QUALIFIER, $1);
}
;
struct-declarator-list
: struct-declarator {
  $1 = YYSCAN_TAG(SYMBOL_STRUCT_DECLARATOR, $1);
  $$ = YYSCAN_PUSH(YYSCAN_ARR(), $1);
}
| struct-declarator-list comma struct-declarator {
  $3 = YYSCAN_TAG(SYMBOL_STRUCT_DECLARATOR, $3);
  $$ = YYSCAN_PUSH($1, $3);
}
;
struct-declarator
: declarator {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_DECLARATOR, $1);
}
| declarator.opt colon constant-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_DECLARATOR, $1);
  YYSCAN_SET($$, SYMBOL_COLON, $2);
  YYSCAN_SET($$, SYMBOL_CONSTANT_EXPRESSION, $3);
}
;
enum-specifier
: enum identifier.opt left-brace enumerator-list right-brace {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_ENUM, $1);
  YYSCAN_SET($$, SYMBOL_IDENTIFIER, $2);
  YYSCAN_SET($$, SYMBOL_LEFT_BRACE, $3);
  YYSCAN_SET($$, SYMBOL_ENUMERATOR_LIST, $4);
  YYSCAN_SET($$, SYMBOL_RIGHT_BRACE, $5);
}
| enum identifier {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_ENUM, $1);
  YYSCAN_SET($$, SYMBOL_IDENTIFIER, $2);
}
;
enumerator-list
: enumerator {
  $1 = YYSCAN_TAG(SYMBOL_ENUMERATOR, $1);
  $$ = YYSCAN_PUSH(YYSCAN_ARR(), $1);
}
| enumerator-list comma enumerator {
  $3 = YYSCAN_TAG(SYMBOL_ENUMERATOR, $3);
  $$ = YYSCAN_PUSH($1, $3);
}
;
enumerator
: enumeration-constant {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_ENUMERATION_CONSTANT, $1);
}
| enumeration-constant assign constant-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_ENUMERATION_CONSTANT, $1);
  YYSCAN_SET($$, SYMBOL_ASSIGN, $2);
  YYSCAN_SET($$, SYMBOL_CONSTANT_EXPRESSION, $3);
}
;
type-qualifier
: const {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_CONST, $1);
}
| volatile {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_VOLATILE, $1);
}
;
declarator.opt
: %empty {
  $$ = YYSCAN_OBJ();
}
| declarator
;
declarator
: direct-declarator {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_DIRECT_DECLARATOR, $1);
}
| pointer direct-declarator {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_POINTER, $1);
  YYSCAN_SET($$, SYMBOL_DIRECT_DECLARATOR, $2);
}
;
direct-declarator
: identifier {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_IDENTIFIER, $1);
}
| left-paren declarator right-paren {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_LEFT_PAREN, $1);
  YYSCAN_SET($$, SYMBOL_DECLARATOR, $2);
  YYSCAN_SET($$, SYMBOL_RIGHT_PAREN, $3);
}
| direct-declarator left-bracket constant-expression.opt right-bracket {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_DIRECT_DECLARATOR, $1);
  YYSCAN_SET($$, SYMBOL_LEFT_BRACKET, $2);
  YYSCAN_SET($$, SYMBOL_CONSTANT_EXPRESSION, $3);
  YYSCAN_SET($$, SYMBOL_RIGHT_BRACKET, $4);
}
| direct-declarator left-paren parameter-type-list right-paren {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_DIRECT_DECLARATOR, $1);
  YYSCAN_SET($$, SYMBOL_LEFT_PAREN, $2);
  YYSCAN_SET($$, SYMBOL_PARAMETER_TYPE_LIST, $3);
  YYSCAN_SET($$, SYMBOL_RIGHT_PAREN, $4);
}
| direct-declarator left-paren identifier-list.opt right-paren {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_DIRECT_DECLARATOR, $1);
  YYSCAN_SET($$, SYMBOL_LEFT_PAREN, $2);
  YYSCAN_SET($$, SYMBOL_IDENTIFIER_LIST, $3);
  YYSCAN_SET($$, SYMBOL_RIGHT_PAREN, $4);
}
;
pointer
: asterisk type-qualifier-list.opt {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_ASTERISK, $1);
  YYSCAN_SET($$, SYMBOL_TYPE_QUALIFIER_LIST, $2);
}
| pointer asterisk type-qualifier-list.opt {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_POINTER, $1);
  YYSCAN_SET($$, SYMBOL_ASTERISK, $2);
  YYSCAN_SET($$, SYMBOL_TYPE_QUALIFIER_LIST, $3);
}
;
type-qualifier-list.opt
: %empty {
  $$ = YYSCAN_ARR();
}
| type-qualifier-list
;
type-qualifier-list
: type-qualifier {
  $1 = YYSCAN_TAG(SYMBOL_TYPE_QUALIFIER, $1);
  $$ = YYSCAN_PUSH(YYSCAN_ARR(), $1);
}
| type-qualifier-list type-qualifier {
  $2 = YYSCAN_TAG(SYMBOL_TYPE_QUALIFIER, $2);
  $$ = YYSCAN_PUSH($1, $2);
}
;
parameter-type-list.opt
: %empty {
  $$ = YYSCAN_OBJ();
}
| parameter-type-list
;
parameter-type-list
: parameter-list {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_PARAMETER_LIST, $1);
}
| parameter-list comma ellipsis {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_PARAMETER_LIST, $1);
  YYSCAN_SET($$, SYMBOL_COMMA, $2);
  YYSCAN_SET($$, SYMBOL_ELLIPSIS, $3);
}
;
parameter-list
: parameter-declaration {
  $1 = YYSCAN_TAG(SYMBOL_PARAMETER_DECLARATION, $1);
  $$ = YYSCAN_PUSH(YYSCAN_ARR(), $1);
}
| parameter-list comma parameter-declaration {
  $3 = YYSCAN_TAG(SYMBOL_PARAMETER_DECLARATION, $3);
  $$ = YYSCAN_PUSH($1, $3);
}
;
parameter-declaration
: declaration-specifiers declarator {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_DECLARATION_SPECIFIERS, $1);
  YYSCAN_SET($$, SYMBOL_DECLARATOR, $2);
}
| declaration-specifiers abstract-declarator.opt {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_DECLARATION_SPECIFIERS, $1);
  YYSCAN_SET($$, SYMBOL_ABSTRACT_DECLARATOR, $2);
}
;
identifier-list.opt
: %empty {
  $$ = YYSCAN_ARR();
}
| identifier-list
;
identifier-list
: identifier {
  $1 = YYSCAN_TAG(SYMBOL_IDENTIFIER, $1);
  $$ = YYSCAN_PUSH(YYSCAN_ARR(), $1);
}
| identifier-list comma identifier {
  $3 = YYSCAN_TAG(SYMBOL_IDENTIFIER, $3);
  $$ = YYSCAN_PUSH($1, $3);
}
;
type-name
: specifier-qualifier-list abstract-declarator.opt {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_SPECIFIER_QUALIFIER_LIST, $1);
  YYSCAN_SET($$, SYMBOL_ABSTRACT_DECLARATOR, $2);
}
;
abstract-declarator.opt
: %empty {
  $$ = YYSCAN_OBJ();
}
| abstract-declarator
;
abstract-declarator
: pointer {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_POINTER, $1);
}
| direct-abstract-declarator {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_DIRECT_ABSTRACT_DECLARATOR, $1);
}
| pointer direct-abstract-declarator {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_POINTER, $1);
  YYSCAN_SET($$, SYMBOL_DIRECT_ABSTRACT_DECLARATOR, $2);
}
;
direct-abstract-declarator
: left-paren abstract-declarator right-paren {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_LEFT_PAREN, $1);
  YYSCAN_SET($$, SYMBOL_ABSTRACT_DECLARATOR, $2);
  YYSCAN_SET($$, SYMBOL_RIGHT_PAREN, $3);
}
| left-bracket constant-expression.opt right-bracket {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_LEFT_BRACKET, $1);
  YYSCAN_SET($$, SYMBOL_CONSTANT_EXPRESSION, $2);
  YYSCAN_SET($$, SYMBOL_RIGHT_BRACKET, $3);
}
| direct-abstract-declarator left-bracket constant-expression.opt right-bracket {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_DIRECT_ABSTRACT_DECLARATOR, $1);
  YYSCAN_SET($$, SYMBOL_LEFT_BRACKET, $2);
  YYSCAN_SET($$, SYMBOL_CONSTANT_EXPRESSION, $3);
  YYSCAN_SET($$, SYMBOL_RIGHT_BRACKET, $4);
}
| left-paren parameter-type-list.opt right-paren {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_LEFT_PAREN, $1);
  YYSCAN_SET($$, SYMBOL_PARAMETER_TYPE_LIST, $2);
  YYSCAN_SET($$, SYMBOL_RIGHT_PAREN, $3);
}
| direct-abstract-declarator left-paren parameter-type-list.opt right-paren {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_DIRECT_ABSTRACT_DECLARATOR, $1);
  YYSCAN_SET($$, SYMBOL_LEFT_PAREN, $2);
  YYSCAN_SET($$, SYMBOL_PARAMETER_TYPE_LIST, $3);
  YYSCAN_SET($$, SYMBOL_RIGHT_PAREN, $4);
}
;
typedef-name
: typedef-identifier {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_TYPEDEF_IDENTIFIER, $1);
}
;
initializer
: assignment-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_EXPRESSION, $1);
}
| left-brace initializer-list right-brace {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_LEFT_BRACE, $1);
  YYSCAN_SET($$, SYMBOL_INITIALIZER_LIST, $2);
  YYSCAN_SET($$, SYMBOL_RIGHT_BRACE, $3);
}
| left-brace initializer-list comma right-brace {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_LEFT_BRACE, $1);
  YYSCAN_SET($$, SYMBOL_INITIALIZER_LIST, $2);
  YYSCAN_SET($$, SYMBOL_COMMA, $3);
  YYSCAN_SET($$, SYMBOL_RIGHT_BRACE, $4);
}
;
initializer-list
: initializer {
  $1 = YYSCAN_TAG(SYMBOL_INITIALIZER, $1);
  $$ = YYSCAN_PUSH(YYSCAN_ARR(), $1);
}
| initializer-list comma initializer {
  $3 = YYSCAN_TAG(SYMBOL_INITIALIZER, $3);
  $$ = YYSCAN_PUSH($1, $3);
}
;

/* 6.6 Statements */
statement
: labeled-statement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_LABELED_STATEMENT, $1);
}
| compound-statement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_COMPOUND_STATEMENT, $1);
}
| expression-statement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_EXPRESSION_STATEMENT, $1);
}
| selection-statement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_SELECTION_STATEMENT, $1);
}
| iteration-statement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_ITERATION_STATEMENT, $1);
}
| jump-statement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_JUMP_STATEMENT, $1);
}
;
labeled-statement
: identifier colon statement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_IDENTIFIER, $1);
  YYSCAN_SET($$, SYMBOL_COLON, $2);
  YYSCAN_SET($$, SYMBOL_STATEMENT, $3);
}
| case constant-expression colon statement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_CASE, $1);
  YYSCAN_SET($$, SYMBOL_CONSTANT_EXPRESSION, $2);
  YYSCAN_SET($$, SYMBOL_COLON, $3);
  YYSCAN_SET($$, SYMBOL_STATEMENT, $4);
}
| default colon statement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_DEFAULT, $1);
  YYSCAN_SET($$, SYMBOL_COLON, $2);
  YYSCAN_SET($$, SYMBOL_STATEMENT, $3);
}
;
compound-statement
: left-brace declaration-list.opt statement-list.opt right-brace {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_LEFT_BRACE, $1);
  YYSCAN_SET($$, SYMBOL_DECLARATION_LIST, $2);
  YYSCAN_SET($$, SYMBOL_STATEMENT_LIST, $3);
  YYSCAN_SET($$, SYMBOL_RIGHT_BRACE, $4);
}
;
declaration-list.opt
: %empty {
  $$ = YYSCAN_ARR();
}
| declaration-list
;
declaration-list
: declaration {
  $1 = YYSCAN_TAG(SYMBOL_DECLARATION, $1);
  $$ = YYSCAN_PUSH(YYSCAN_ARR(), $1);
}
| declaration-list declaration {
  $2 = YYSCAN_TAG(SYMBOL_DECLARATION, $2);
  $$ = YYSCAN_PUSH($1, $2);
}
;
statement-list.opt
: %empty {
  $$ = YYSCAN_ARR();
}
| statement-list
;
statement-list
: statement {
  $1 = YYSCAN_TAG(SYMBOL_STATEMENT, $1);
  $$ = YYSCAN_PUSH(YYSCAN_ARR(), $1);
}
| statement-list statement {
  $2 = YYSCAN_TAG(SYMBOL_STATEMENT, $2);
  $$ = YYSCAN_PUSH($1, $2);
}
;
expression-statement
: expression.opt semicolon {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_EXPRESSION, $1);
  YYSCAN_SET($$, SYMBOL_SEMICOLON, $2);
}
;
selection-statement
: if left-paren expression right-paren statement %prec THEN {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_IF, $1);
  YYSCAN_SET($$, SYMBOL_LEFT_PAREN, $2);
  YYSCAN_SET($$, SYMBOL_EXPRESSION, $3);
  YYSCAN_SET($$, SYMBOL_RIGHT_PAREN, $4);
  YYSCAN_SET($$, SYMBOL_STATEMENT, $5);
}
| if left-paren expression right-paren statement else statement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_IF, $1);
  YYSCAN_SET($$, SYMBOL_LEFT_PAREN, $2);
  YYSCAN_SET($$, SYMBOL_EXPRESSION, $3);
  YYSCAN_SET($$, SYMBOL_RIGHT_PAREN, $4);
  YYSCAN_SET($$, SYMBOL_STATEMENT, $5);
  YYSCAN_SET($$, SYMBOL_ELSE, $6);
  YYSCAN_SET($$, SYMBOL_STATEMENT, $7);
}
| switch left-paren expression right-paren statement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_SWITCH, $1);
  YYSCAN_SET($$, SYMBOL_LEFT_PAREN, $2);
  YYSCAN_SET($$, SYMBOL_EXPRESSION, $3);
  YYSCAN_SET($$, SYMBOL_RIGHT_PAREN, $4);
  YYSCAN_SET($$, SYMBOL_STATEMENT, $5);
}
;
iteration-statement
: while left-paren expression right-paren statement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_WHILE, $1);
  YYSCAN_SET($$, SYMBOL_LEFT_PAREN, $2);
  YYSCAN_SET($$, SYMBOL_EXPRESSION, $3);
  YYSCAN_SET($$, SYMBOL_RIGHT_PAREN, $4);
  YYSCAN_SET($$, SYMBOL_STATEMENT, $5);
}
| do statement while left-paren expression right-paren semicolon {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_DO, $1);
  YYSCAN_SET($$, SYMBOL_STATEMENT, $2);
  YYSCAN_SET($$, SYMBOL_WHILE, $3);
  YYSCAN_SET($$, SYMBOL_LEFT_PAREN, $4);
  YYSCAN_SET($$, SYMBOL_EXPRESSION, $5);
  YYSCAN_SET($$, SYMBOL_RIGHT_PAREN, $6);
  YYSCAN_SET($$, SYMBOL_SEMICOLON, $7);
}
| for left-paren expression.opt semicolon expression.opt semicolon expression.opt right-paren statement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_FOR, $1);
  YYSCAN_SET($$, SYMBOL_LEFT_PAREN, $2);
  YYSCAN_SET($$, SYMBOL_EXPRESSION, $3);
  YYSCAN_SET($$, SYMBOL_SEMICOLON, $4);
  YYSCAN_SET($$, SYMBOL_EXPRESSION, $5);
  YYSCAN_SET($$, SYMBOL_SEMICOLON, $6);
  YYSCAN_SET($$, SYMBOL_EXPRESSION, $7);
  YYSCAN_SET($$, SYMBOL_RIGHT_PAREN, $8);
  YYSCAN_SET($$, SYMBOL_STATEMENT, $9);
}
;
jump-statement
: goto identifier semicolon {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_GOTO, $1);
  YYSCAN_SET($$, SYMBOL_IDENTIFIER, $2);
  YYSCAN_SET($$, SYMBOL_SEMICOLON, $3);
}
| continue semicolon {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_CONTINUE, $1);
  YYSCAN_SET($$, SYMBOL_SEMICOLON, $2);
}
| break semicolon {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_BREAK, $1);
  YYSCAN_SET($$, SYMBOL_SEMICOLON, $2);
}
| return expression.opt semicolon {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_RETURN, $1);
  YYSCAN_SET($$, SYMBOL_EXPRESSION, $2);
  YYSCAN_SET($$, SYMBOL_SEMICOLON, $3);
}
;

/* 6.7 External definitions */
top
: translation-unit {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_TRANSLATION_UNIT, $1);
  YYSCAN_SET_TOP($$);
}
;
translation-unit
: external-declaration {
  $1 = YYSCAN_TAG(SYMBOL_EXTERNAL_DECLARATION, $1);
  $$ = YYSCAN_PUSH(YYSCAN_ARR(), $1);
}
| translation-unit external-declaration {
  $2 = YYSCAN_TAG(SYMBOL_EXTERNAL_DECLARATION, $2);
  $$ = YYSCAN_PUSH($1, $2);
}
;
external-declaration
: function-definition {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_FUNCTION_DEFINITION, $1);
}
| declaration {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_DECLARATION, $1);
  YYSCAN_REGISTER($1);
}
;
function-definition
: declarator declaration-list.opt compound-statement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_DECLARATOR, $1);
  YYSCAN_SET($$, SYMBOL_DECLARATION_LIST, $2);
  YYSCAN_SET($$, SYMBOL_COMPOUND_STATEMENT, $3);
}
| declaration-specifiers declarator declaration-list.opt compound-statement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, SYMBOL_DECLARATION_SPECIFIERS, $1);
  YYSCAN_SET($$, SYMBOL_DECLARATOR, $2);
  YYSCAN_SET($$, SYMBOL_DECLARATION_LIST, $3);
  YYSCAN_SET($$, SYMBOL_COMPOUND_STATEMENT, $4);
}
;

%%
