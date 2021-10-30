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

auto: "auto" { $$ = YYSCAN_STR(auto); }
;
break: "break" { $$ = YYSCAN_STR(break); }
;
case: "case" { $$ = YYSCAN_STR(case); }
;
char: "char" { $$ = YYSCAN_STR(char); }
;
const: "const" { $$ = YYSCAN_STR(const); }
;
continue: "continue" { $$ = YYSCAN_STR(continue); }
;
default: "default" { $$ = YYSCAN_STR(default); }
;
do: "do" { $$ = YYSCAN_STR(do); }
;
double: "double" { $$ = YYSCAN_STR(double); }
;
else: "else" { $$ = YYSCAN_STR(else); }
;
enum: "enum" { $$ = YYSCAN_STR(enum); }
;
extern: "extern" { $$ = YYSCAN_STR(extern); }
;
float: "float" { $$ = YYSCAN_STR(float); }
;
for: "for" { $$ = YYSCAN_STR(for); }
;
goto: "goto" { $$ = YYSCAN_STR(goto); }
;
if: "if" { $$ = YYSCAN_STR(if); }
;
int: "int" { $$ = YYSCAN_STR(int); }
;
long: "long" { $$ = YYSCAN_STR(long); }
;
register: "register" { $$ = YYSCAN_STR(register); }
;
return: "return" { $$ = YYSCAN_STR(return); }
;
short: "short" { $$ = YYSCAN_STR(short); }
;
signed: "signed" { $$ = YYSCAN_STR(signed); }
;
sizeof: "sizeof" { $$ = YYSCAN_STR(sizeof); }
;
static: "static" { $$ = YYSCAN_STR(static); }
;
struct: "struct" { $$ = YYSCAN_STR(struct); }
;
switch: "switch" { $$ = YYSCAN_STR(switch); }
;
typedef: "typedef" { $$ = YYSCAN_STR(typedef); }
;
union: "union" { $$ = YYSCAN_STR(union); }
;
unsigned: "unsigned" { $$ = YYSCAN_STR(unsigned); }
;
void: "void" { $$ = YYSCAN_STR(void); }
;
volatile: "volatile" { $$ = YYSCAN_STR(volatile); }
;
while: "while" { $$ = YYSCAN_STR(while); }
;

period: "." { $$ = YYSCAN_STR(period); }
;
arrow: "->" { $$ = YYSCAN_STR(arrow); }
;
increment: "++" { $$ = YYSCAN_STR(increment); }
;
decrement: "--" { $$ = YYSCAN_STR(decrement); }
;
ampersand: "&" { $$ = YYSCAN_STR(ampersand); }
;
asterisk: "*" { $$ = YYSCAN_STR(asterisk); }
;
plus: "+" { $$ = YYSCAN_STR(plus); }
;
minus: "-" { $$ = YYSCAN_STR(minus); }
;
tilde: "~" { $$ = YYSCAN_STR(tilde); }
;
exclamation: "!" { $$ = YYSCAN_STR(exclamation); }
;
slash: "/" { $$ = YYSCAN_STR(slash); }
;
percent: "%" { $$ = YYSCAN_STR(percent); }
;
left-shift: "<<" { $$ = YYSCAN_STR(left-shift); }
;
right-shift: ">>" { $$ = YYSCAN_STR(right-shift); }
;
less-than: "<" { $$ = YYSCAN_STR(less-than); }
;
greater-than: ">" { $$ = YYSCAN_STR(greater-than); }
;
less-equal: "<=" { $$ = YYSCAN_STR(less-equal); }
;
greater-equal: ">=" { $$ = YYSCAN_STR(greater-equal); }
;
equal: "==" { $$ = YYSCAN_STR(equal); }
;
not-equal: "!=" { $$ = YYSCAN_STR(not-equal); }
;
caret: "^" { $$ = YYSCAN_STR(caret); }
;
bar: "|" { $$ = YYSCAN_STR(bar); }
;
and: "&&" { $$ = YYSCAN_STR(and); }
;
or: "||" { $$ = YYSCAN_STR(or); }
;
question: "?" { $$ = YYSCAN_STR(question); }
;
assign: "=" { $$ = YYSCAN_STR(assign); }
;
asterisk-assign: "*=" { $$ = YYSCAN_STR(asterisk-assign); }
;
slash-assign: "/=" { $$ = YYSCAN_STR(slash-assign); }
;
percent-assign: "%=" { $$ = YYSCAN_STR(percent-assign); }
;
plus-assign: "+=" { $$ = YYSCAN_STR(plus-assign); }
;
minus-assign: "-=" { $$ = YYSCAN_STR(minus-assign); }
;
left-shift-assign: "<<=" { $$ = YYSCAN_STR(left-shift-assign); }
;
right-shift-assign: ">>=" { $$ = YYSCAN_STR(right-shift-assign); }
;
ampersand-assign: "&=" { $$ = YYSCAN_STR(ampersand-assign); }
;
caret-assign: "^=" { $$ = YYSCAN_STR(caret-assign); }
;
bar-assign: "|=" { $$ = YYSCAN_STR(bar-assign); }
;

left-bracket: "[" { $$ = YYSCAN_STR(left-bracket); }
;
right-bracket: "]" { $$ = YYSCAN_STR(right-bracket); }
;
left-paren: "(" { $$ = YYSCAN_STR(left-paren); }
;
right-paren: ")" { $$ = YYSCAN_STR(right-paren); }
;
left-brace: "{" { $$ = YYSCAN_STR(left-brace); }
;
right-brace: "}" { $$ = YYSCAN_STR(right-brace); }
;
comma: "," { $$ = YYSCAN_STR(comma); }
;
colon: ":" { $$ = YYSCAN_STR(colon); }
;
semicolon: ";" { $$ = YYSCAN_STR(semicolon); }
;
ellipsis: "..." { $$ = YYSCAN_STR(ellipsis); }
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
  YYSCAN_SET($$, identifier, $1);
}
| floating-constant {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, floating-constant, $1);
}
| integer-constant {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, integer-constant, $1);
}
| character-constant {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, character-constant, $1);
}
| string-literal {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, string-literal, $1);
}
| left-paren expression right-paren {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, left-paren, $1);
  YYSCAN_SET($$, expression, $2);
  YYSCAN_SET($$, right-paren, $3);
}
;
postfix-expression
: primary-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, primary-expression, $1);
}
| postfix-expression left-bracket expression right-bracket {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, postfix-expression, $1);
  YYSCAN_SET($$, left-bracket, $2);
  YYSCAN_SET($$, expression, $3);
  YYSCAN_SET($$, right-bracket, $4);
}
| postfix-expression left-paren argument-expression-list.opt right-paren {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, postfix-expression, $1);
  YYSCAN_SET($$, left-paren, $2);
  YYSCAN_SET($$, argument-expression-list, $3);
  YYSCAN_SET($$, right-paren, $4);
}
| postfix-expression period identifier {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, postfix-expression, $1);
  YYSCAN_SET($$, period, $2);
  YYSCAN_SET($$, identifier, $3);
}
| postfix-expression arrow identifier {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, postfix-expression, $1);
  YYSCAN_SET($$, arrow, $2);
  YYSCAN_SET($$, identifier, $3);
}
| postfix-expression increment {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, postfix-expression, $1);
  YYSCAN_SET($$, increment, $2);
}
| postfix-expression decrement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, postfix-expression, $1);
  YYSCAN_SET($$, decrement, $2);
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
  $$ = YYSCAN_PUSH(YYSCAN_ARR(), $1);
}
| argument-expression-list comma assignment-expression {
  $$ = YYSCAN_PUSH($1, $2);
}
;
unary-expression
: postfix-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, postfix-expression, $1);
}
| increment unary-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, increment, $1);
  YYSCAN_SET($$, unary-expression, $2);
}
| decrement unary-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, decrement, $1);
  YYSCAN_SET($$, unary-expression, $2);
}
| unary-operator cast-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, unary-operator, $1);
  YYSCAN_SET($$, cast-expression, $2);
}
| sizeof unary-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, sizeof, $1);
  YYSCAN_SET($$, unary-expression, $2);
}
| sizeof left-paren type-name right-paren {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, sizeof, $1);
  YYSCAN_SET($$, left-paren, $2);
  YYSCAN_SET($$, type-name, $3);
  YYSCAN_SET($$, right-paren, $4);
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
: unary-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, unary-expression, $1);
}
| left-paren type-name right-paren cast-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, left-paren, $1);
  YYSCAN_SET($$, type-name, $2);
  YYSCAN_SET($$, right-paren, $3);
  YYSCAN_SET($$, cast-expression, $4);
}
;
multiplicative-expression
: cast-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, cast-expression, $1);
}
| multiplicative-expression multiplicative-operator cast-expression {
  $$ = YYSCAN_BINOP($1, $2, $3);
}
;
multiplicative-operator
: asterisk
| slash
| percent
;
additive-expression
: multiplicative-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, multiplicative-expression, $1);
}
| additive-expression additive-operator multiplicative-expression {
  $$ = YYSCAN_BINOP($1, $2, $3);
}
;
additive-operator
: plus
| minus
;
shift-expression
: additive-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, additive-expression, $1);
}
| shift-expression shift-operator additive-expression {
  $$ = YYSCAN_BINOP($1, $2, $3);
}
;
shift-operator
: left-shift
| right-shift
;
relational-expression
: shift-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, shift-expression, $1);
}
| relational-expression relational-operator shift-expression {
  $$ = YYSCAN_BINOP($1, $2, $3);
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, relational-expression, $1);
  YYSCAN_SET($$, relational-operator, $2);
  YYSCAN_SET($$, shift-expression, $3);
}
;
relational-operator
: less-than
| greater-than
| less-equal
| greater-equal
;
equality-expression
: relational-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, relational-expression, $1);
}
| equality-expression equality-operator relational-expression {
  $$ = YYSCAN_BINOP($1, $2, $3);
}
;
equality-operator
: equal
| not-equal
;
and-expression
: equality-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, equality-expression, $1);
}
| and-expression ampersand equality-expression {
  $$ = YYSCAN_BINOP($1, $2, $3);
}
;
exclusive-or-expression
: and-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, and-expression, $1);
}
| exclusive-or-expression caret and-expression {
  $$ = YYSCAN_BINOP($1, $2, $3);
}
;
inclusive-or-expression
: exclusive-or-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, exclusive-or-expression, $1);
}
| inclusive-or-expression bar exclusive-or-expression {
  $$ = YYSCAN_BINOP($1, $2, $3);
}
;
logical-and-expression
: inclusive-or-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, inclusive-or-expression, $1);
}
| logical-and-expression and inclusive-or-expression {
  $$ = YYSCAN_BINOP($1, $2, $3);
}
;
logical-or-expression
: logical-and-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, logical-and-expression, $1);
}
| logical-or-expression or logical-and-expression {
  $$ = YYSCAN_BINOP($1, $2, $3);
}
;
conditional-expression
: logical-or-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, logical-or-expression, $1);
}
| logical-or-expression question expression colon conditional-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, logical-or-expression, $1);
  YYSCAN_SET($$, question, $2);
  YYSCAN_SET($$, expression, $3);
  YYSCAN_SET($$, colon, $4);
  YYSCAN_SET($$, conditional-expression, $5);
}
;
assignment-expression
: conditional-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, conditional-expression, $1);
}
| unary-expression assignment-operator assignment-expression {
  $$ = YYSCAN_BINOP($1, $2, $3);
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
: assignment-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, assignment-expression, $1);
}
| expression comma assignment-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, expression, $1);
  YYSCAN_SET($$, comma, $1);
  YYSCAN_SET($$, assignment-expression, $1);
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
: conditional-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, conditional-expression, $1);
}
;

/* 6.5 Declarations */
declaration
: declaration-specifiers init-declarator-list.opt semicolon {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, declaration-specifiers, $1);
  YYSCAN_SET($$, init-declarator-list, $2);
  YYSCAN_SET($$, semicolon, $3);
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
  YYSCAN_SET($$, storage-class-specifier, $1);
}
| type-specifier {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, type-specifier, $1);
}
| type-qualifier {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, type-qualifier, $1);
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
  $$ = YYSCAN_PUSH(YYSCAN_ARR(), $1);
}
| init-declarator-list comma init-declarator {
  $$ = YYSCAN_PUSH($1, $3);
}
;
init-declarator
: declarator {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, declarator, $1);
}
| declarator assign initializer {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, declarator, $1);
  YYSCAN_SET($$, assign, $2);
  YYSCAN_SET($$, initializer, $3);
}
;
storage-class-specifier
: typedef {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, typedef, $1);
}
| extern {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, extern, $1);
}
| static {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, static, $1);
}
| auto {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, auto, $1);
}
| register {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, register, $1);
}
;
type-specifier
: void {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, void, $1);
}
| char {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, char, $1);
}
| short {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, short, $1);
}
| int {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, int, $1);
}
| long {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, long, $1);
}
| float {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, float, $1);
}
| double {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, double, $1);
}
| signed {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, signed, $1);
}
| unsigned {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, unsigned, $1);
}
| struct-or-union-specifier {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, struct-or-union-specifier, $1);
}
| enum-specifier {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, enum-specifier, $1);
}
| typedef-name {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, typedef-name, $1);
}
;
struct-or-union-specifier
: struct-or-union identifier.opt left-brace struct-declaration-list right-brace {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, struct-or-union, $1);
  YYSCAN_SET($$, identifier, $2);
  YYSCAN_SET($$, left-brace, $3);
  YYSCAN_SET($$, struct-declaration-list, $4);
  YYSCAN_SET($$, right-brace, $5);
}
| struct-or-union identifier {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, struct-or-union, $1);
  YYSCAN_SET($$, identifier, $2);
}
;
struct-or-union
: struct {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, struct, $1);
}
| union {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, union, $1);
}
;
struct-declaration-list
: struct-declaration {
  $$ = YYSCAN_PUSH(YYSCAN_ARR(), $1);
}
| struct-declaration-list struct-declaration {
  $$ = YYSCAN_PUSH($1, $2);
}
;
struct-declaration
: specifier-qualifier-list struct-declarator-list semicolon {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, specifier-qualifier-list, $1);
  YYSCAN_SET($$, struct-declarator-list, $2);
  YYSCAN_SET($$, semicolon, $3);
}
;
specifier-qualifier-list
: specifier-qualifier {
  $$ = YYSCAN_PUSH(YYSCAN_ARR(), $1);
}
| specifier-qualifier-list specifier-qualifier {
  $$ = YYSCAN_PUSH($1, $2);
}
;
specifier-qualifier
: type-specifier {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, type-specifier, $1);
}
| type-qualifier {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, type-qualifier, $1);
}
;
struct-declarator-list
: struct-declarator {
  $$ = YYSCAN_PUSH(YYSCAN_ARR(), $1);
}
| struct-declarator-list comma struct-declarator {
  $$ = YYSCAN_PUSH($1, $3);
}
;
struct-declarator
: declarator {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, declarator, $1);
}
| declarator.opt colon constant-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, declarator, $1);
  YYSCAN_SET($$, colon, $2);
  YYSCAN_SET($$, constant-expression, $3);
}
;
enum-specifier
: enum identifier.opt left-brace enumerator-list right-brace {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, enum, $1);
  YYSCAN_SET($$, identifier, $2);
  YYSCAN_SET($$, left-brace, $3);
  YYSCAN_SET($$, enumerator-list, $4);
  YYSCAN_SET($$, right-brace, $5);
}
| enum identifier {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, enum, $1);
  YYSCAN_SET($$, identifier, $2);
}
;
enumerator-list
: enumerator {
  $$ = YYSCAN_PUSH(YYSCAN_ARR(), $1);
}
| enumerator-list comma enumerator {
  $$ = YYSCAN_PUSH($1, $3);
}
;
enumerator
: enumeration-constant {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, enumeration-constant, $1);
}
| enumeration-constant assign constant-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, enumeration-constant, $1);
  YYSCAN_SET($$, assign, $2);
  YYSCAN_SET($$, constant-expression, $3);
}
;
type-qualifier
: const {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, const, $1);
}
| volatile {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, volatile, $1);
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
  YYSCAN_SET($$, direct-declarator, $1);
}
| pointer direct-declarator {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, pointer, $1);
  YYSCAN_SET($$, direct-declarator, $2);
}
;
direct-declarator
: identifier {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, identifier, $1);
}
| left-paren declarator right-paren {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, left-paren, $1);
  YYSCAN_SET($$, declarator, $2);
  YYSCAN_SET($$, right-paren, $3);
}
| direct-declarator left-bracket constant-expression.opt right-bracket {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, direct-declarator, $1);
  YYSCAN_SET($$, left-bracket, $2);
  YYSCAN_SET($$, constant-expression, $3);
  YYSCAN_SET($$, right-bracket, $4);
}
| direct-declarator left-paren parameter-type-list right-paren {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, direct-declarator, $1);
  YYSCAN_SET($$, left-paren, $2);
  YYSCAN_SET($$, parameter-type-list, $3);
  YYSCAN_SET($$, right-paren, $4);
}
| direct-declarator left-paren identifier-list.opt right-paren {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, direct-declarator, $1);
  YYSCAN_SET($$, left-paren, $2);
  YYSCAN_SET($$, identifier-list, $3);
  YYSCAN_SET($$, right-paren, $4);
}
;
pointer
: asterisk type-qualifier-list.opt {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, asterisk, $1);
  YYSCAN_SET($$, type-qualifier-list, $2);
}
| pointer asterisk type-qualifier-list.opt {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, pointer, $1);
  YYSCAN_SET($$, asterisk, $2);
  YYSCAN_SET($$, type-qualifier-list, $3);
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
  $$ = YYSCAN_PUSH(YYSCAN_ARR(), $1);
}
| type-qualifier-list type-qualifier {
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
  YYSCAN_SET($$, parameter-list, $1);
}
| parameter-list comma ellipsis {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, parameter-list, $1);
  YYSCAN_SET($$, comma, $2);
  YYSCAN_SET($$, ellipsis, $3);
}
;
parameter-list
: parameter-declaration {
  $$ = YYSCAN_PUSH(YYSCAN_ARR(), $1);
}
| parameter-list comma parameter-declaration {
  $$ = YYSCAN_PUSH($1, $3);
}
;
parameter-declaration
: declaration-specifiers declarator {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, declaration-specifiers, $1);
  YYSCAN_SET($$, declarator, $2);
}
| declaration-specifiers abstract-declarator.opt {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, declaration-specifiers, $1);
  YYSCAN_SET($$, abstract-declarator, $2);
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
  $$ = YYSCAN_PUSH(YYSCAN_ARR(), $1);
}
| identifier-list comma identifier {
  $$ = YYSCAN_PUSH($1, $3);
}
;
type-name
: specifier-qualifier-list abstract-declarator.opt {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, specifier-qualifier-list, $1);
  YYSCAN_SET($$, abstract-declarator, $2);
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
  YYSCAN_SET($$, pointer, $1);
}
| direct-abstract-declarator {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, direct-abstract-declarator, $1);
}
| pointer direct-abstract-declarator {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, pointer, $1);
  YYSCAN_SET($$, direct-abstract-declarator, $2);
}
;
direct-abstract-declarator
: left-paren abstract-declarator right-paren {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, left-paren, $1);
  YYSCAN_SET($$, abstract-declarator, $2);
  YYSCAN_SET($$, right-paren, $3);
}
| left-bracket constant-expression.opt right-bracket {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, left-bracket, $1);
  YYSCAN_SET($$, constant-expression, $2);
  YYSCAN_SET($$, right-bracket, $3);
}
| direct-abstract-declarator left-bracket constant-expression.opt right-bracket {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, direct-abstract-declarator, $1);
  YYSCAN_SET($$, left-bracket, $2);
  YYSCAN_SET($$, constant-expression, $3);
  YYSCAN_SET($$, right-bracket, $4);
}
| left-paren parameter-type-list.opt right-paren {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, left-paren, $1);
  YYSCAN_SET($$, parameter-type-list, $2);
  YYSCAN_SET($$, right-paren, $3);
}
| direct-abstract-declarator left-paren parameter-type-list.opt right-paren {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, direct-abstract-declarator, $1);
  YYSCAN_SET($$, left-paren, $2);
  YYSCAN_SET($$, parameter-type-list, $3);
  YYSCAN_SET($$, right-paren, $4);
}
;
typedef-name
: typedef-identifier {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, typedef-identifier, $1);
}
;
initializer
: assignment-expression {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, assignment-expression, $1);
}
| left-brace initializer-list right-brace {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, left-brace, $1);
  YYSCAN_SET($$, initializer-list, $2);
  YYSCAN_SET($$, right-brace, $3);
}
| left-brace initializer-list comma right-brace {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, left-brace, $1);
  YYSCAN_SET($$, initializer-list, $2);
  YYSCAN_SET($$, comma, $3);
  YYSCAN_SET($$, right-brace, $4);
}
;
initializer-list
: initializer {
  $$ = YYSCAN_PUSH(YYSCAN_ARR(), $1);
}
| initializer-list comma initializer {
  $$ = YYSCAN_PUSH($1, $3);
}
;

/* 6.6 Statements */
statement
: labeled-statement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, labeled-statement, $1);
}
| compound-statement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, compound-statement, $1);
}
| expression-statement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, expression-statement, $1);
}
| selection-statement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, selection-statement, $1);
}
| iteration-statement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, iteration-statement, $1);
}
| jump-statement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, jump-statement, $1);
}
;
labeled-statement
: identifier colon statement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, identifier, $1);
  YYSCAN_SET($$, colon, $2);
  YYSCAN_SET($$, statement, $3);
}
| case constant-expression colon statement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, case, $1);
  YYSCAN_SET($$, constant-expression, $2);
  YYSCAN_SET($$, colon, $3);
  YYSCAN_SET($$, statement, $4);
}
| default colon statement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, default, $1);
  YYSCAN_SET($$, colon, $2);
  YYSCAN_SET($$, statement, $3);
}
;
compound-statement
: left-brace declaration-list.opt statement-list.opt right-brace {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, left-brace, $1);
  YYSCAN_SET($$, declaration-list, $2);
  YYSCAN_SET($$, statement-list, $3);
  YYSCAN_SET($$, right-brace, $4);
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
  $$ = YYSCAN_PUSH(YYSCAN_ARR(), $1);
}
| declaration-list declaration {
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
  $$ = YYSCAN_PUSH(YYSCAN_ARR(), $1);
}
| statement-list statement {
  $$ = YYSCAN_PUSH($1, $2);
}
;
expression-statement
: expression.opt semicolon {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, expression, $1);
  YYSCAN_SET($$, semicolon, $2);
}
;
selection-statement
: if left-paren expression right-paren statement %prec THEN {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, if, $1);
  YYSCAN_SET($$, left-paren, $2);
  YYSCAN_SET($$, expression, $3);
  YYSCAN_SET($$, right-paren, $4);
  YYSCAN_SET($$, statement, $5);
}
| if left-paren expression right-paren statement else statement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, if, $1);
  YYSCAN_SET($$, left-paren, $2);
  YYSCAN_SET($$, expression, $3);
  YYSCAN_SET($$, right-paren, $4);
  YYSCAN_SET($$, statement, $5);
  YYSCAN_SET($$, else, $6);
  YYSCAN_SET($$, statement, $7);
}
| switch left-paren expression right-paren statement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, switch, $1);
  YYSCAN_SET($$, left-paren, $2);
  YYSCAN_SET($$, expression, $3);
  YYSCAN_SET($$, right-paren, $4);
  YYSCAN_SET($$, statement, $5);
}
;
iteration-statement
: while left-paren expression right-paren statement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, while, $1);
  YYSCAN_SET($$, left-paren, $2);
  YYSCAN_SET($$, expression, $3);
  YYSCAN_SET($$, right-paren, $4);
  YYSCAN_SET($$, statement, $5);
}
| do statement while left-paren expression right-paren semicolon {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, do, $1);
  YYSCAN_SET($$, statement, $2);
  YYSCAN_SET($$, while, $3);
  YYSCAN_SET($$, left-paren, $4);
  YYSCAN_SET($$, expression, $5);
  YYSCAN_SET($$, right-paren, $6);
  YYSCAN_SET($$, semicolon, $7);
}
| for left-paren expression.opt semicolon expression.opt semicolon expression.opt right-paren statement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, for, $1);
  YYSCAN_SET($$, left-paren, $2);
  YYSCAN_SET($$, expression, $3);
  YYSCAN_SET($$, semicolon, $4);
  YYSCAN_SET($$, expression, $5);
  YYSCAN_SET($$, semicolon, $6);
  YYSCAN_SET($$, expression, $7);
  YYSCAN_SET($$, right-paren, $8);
  YYSCAN_SET($$, statement, $9);
}
;
jump-statement
: goto identifier semicolon {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, goto, $1);
  YYSCAN_SET($$, identifier, $2);
  YYSCAN_SET($$, semicolon, $3);
}
| continue semicolon {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, continue, $1);
  YYSCAN_SET($$, semicolon, $2);
}
| break semicolon {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, break, $1);
  YYSCAN_SET($$, semicolon, $2);
}
| return expression.opt semicolon {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, return, $1);
  YYSCAN_SET($$, expression, $2);
  YYSCAN_SET($$, semicolon, $3);
}
;

/* 6.7 External definitions */
top
: translation-unit {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, translation-unit, $1);
  YYSCAN_SET_TOP($$);
}
;
translation-unit
: external-declaration {
  $$ = YYSCAN_PUSH(YYSCAN_ARR(), $1);
}
| translation-unit external-declaration {
  $$ = YYSCAN_PUSH($1, $2);
}
;
external-declaration
: function-definition {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, function-definition, $1);
}
| declaration {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, declaration, $1);
  /* yyscan_register_typedef(YYSCAN_PARAM, $1); */
}
;
function-definition
: declarator declaration-list.opt compound-statement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, declarator, $1);
  YYSCAN_SET($$, declaration-list, $2);
  YYSCAN_SET($$, compound-statement, $3);
}
| declaration-specifiers declarator declaration-list.opt compound-statement {
  $$ = YYSCAN_OBJ();
  YYSCAN_SET($$, declaration-specifiers, $1);
  YYSCAN_SET($$, declarator, $2);
  YYSCAN_SET($$, declaration-list, $3);
  YYSCAN_SET($$, compound-statement, $4);
}
;

%%
