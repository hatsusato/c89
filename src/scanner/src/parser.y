%code requires {
#include "yyscan_t.h"
}

%define api.pure full
%define api.value.type {const struct cell *}
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

auto: "auto" { $$ = YYSCAN_SYMBOL(auto); }
;
break: "break" { $$ = YYSCAN_SYMBOL(break); }
;
case: "case" { $$ = YYSCAN_SYMBOL(case); }
;
char: "char" { $$ = YYSCAN_SYMBOL(char); }
;
const: "const" { $$ = YYSCAN_SYMBOL(const); }
;
continue: "continue" { $$ = YYSCAN_SYMBOL(continue); }
;
default: "default" { $$ = YYSCAN_SYMBOL(default); }
;
do: "do" { $$ = YYSCAN_SYMBOL(do); }
;
double: "double" { $$ = YYSCAN_SYMBOL(double); }
;
else: "else" { $$ = YYSCAN_SYMBOL(else); }
;
enum: "enum" { $$ = YYSCAN_SYMBOL(enum); }
;
extern: "extern" { $$ = YYSCAN_SYMBOL(extern); }
;
float: "float" { $$ = YYSCAN_SYMBOL(float); }
;
for: "for" { $$ = YYSCAN_SYMBOL(for); }
;
goto: "goto" { $$ = YYSCAN_SYMBOL(goto); }
;
if: "if" { $$ = YYSCAN_SYMBOL(if); }
;
int: "int" { $$ = YYSCAN_SYMBOL(int); }
;
long: "long" { $$ = YYSCAN_SYMBOL(long); }
;
register: "register" { $$ = YYSCAN_SYMBOL(register); }
;
return: "return" { $$ = YYSCAN_SYMBOL(return); }
;
short: "short" { $$ = YYSCAN_SYMBOL(short); }
;
signed: "signed" { $$ = YYSCAN_SYMBOL(signed); }
;
sizeof: "sizeof" { $$ = YYSCAN_SYMBOL(sizeof); }
;
static: "static" { $$ = YYSCAN_SYMBOL(static); }
;
struct: "struct" { $$ = YYSCAN_SYMBOL(struct); }
;
switch: "switch" { $$ = YYSCAN_SYMBOL(switch); }
;
typedef: "typedef" { $$ = YYSCAN_SYMBOL(typedef); }
;
union: "union" { $$ = YYSCAN_SYMBOL(union); }
;
unsigned: "unsigned" { $$ = YYSCAN_SYMBOL(unsigned); }
;
void: "void" { $$ = YYSCAN_SYMBOL(void); }
;
volatile: "volatile" { $$ = YYSCAN_SYMBOL(volatile); }
;
while: "while" { $$ = YYSCAN_SYMBOL(while); }
;

period: "." { $$ = YYSCAN_SYMBOL(period); }
;
arrow: "->" { $$ = YYSCAN_SYMBOL(arrow); }
;
increment: "++" { $$ = YYSCAN_SYMBOL(increment); }
;
decrement: "--" { $$ = YYSCAN_SYMBOL(decrement); }
;
ampersand: "&" { $$ = YYSCAN_SYMBOL(ampersand); }
;
asterisk: "*" { $$ = YYSCAN_SYMBOL(asterisk); }
;
plus: "+" { $$ = YYSCAN_SYMBOL(plus); }
;
minus: "-" { $$ = YYSCAN_SYMBOL(minus); }
;
tilde: "~" { $$ = YYSCAN_SYMBOL(tilde); }
;
exclamation: "!" { $$ = YYSCAN_SYMBOL(exclamation); }
;
slash: "/" { $$ = YYSCAN_SYMBOL(slash); }
;
percent: "%" { $$ = YYSCAN_SYMBOL(percent); }
;
left-shift: "<<" { $$ = YYSCAN_SYMBOL(left-shift); }
;
right-shift: ">>" { $$ = YYSCAN_SYMBOL(right-shift); }
;
less-than: "<" { $$ = YYSCAN_SYMBOL(less-than); }
;
greater-than: ">" { $$ = YYSCAN_SYMBOL(greater-than); }
;
less-equal: "<=" { $$ = YYSCAN_SYMBOL(less-equal); }
;
greater-equal: ">=" { $$ = YYSCAN_SYMBOL(greater-equal); }
;
equal: "==" { $$ = YYSCAN_SYMBOL(equal); }
;
not-equal: "!=" { $$ = YYSCAN_SYMBOL(not-equal); }
;
caret: "^" { $$ = YYSCAN_SYMBOL(caret); }
;
bar: "|" { $$ = YYSCAN_SYMBOL(bar); }
;
and: "&&" { $$ = YYSCAN_SYMBOL(and); }
;
or: "||" { $$ = YYSCAN_SYMBOL(or); }
;
question: "?" { $$ = YYSCAN_SYMBOL(question); }
;
assign: "=" { $$ = YYSCAN_SYMBOL(assign); }
;
asterisk-assign: "*=" { $$ = YYSCAN_SYMBOL(asterisk-assign); }
;
slash-assign: "/=" { $$ = YYSCAN_SYMBOL(slash-assign); }
;
percent-assign: "%=" { $$ = YYSCAN_SYMBOL(percent-assign); }
;
plus-assign: "+=" { $$ = YYSCAN_SYMBOL(plus-assign); }
;
minus-assign: "-=" { $$ = YYSCAN_SYMBOL(minus-assign); }
;
left-shift-assign: "<<=" { $$ = YYSCAN_SYMBOL(left-shift-assign); }
;
right-shift-assign: ">>=" { $$ = YYSCAN_SYMBOL(right-shift-assign); }
;
ampersand-assign: "&=" { $$ = YYSCAN_SYMBOL(ampersand-assign); }
;
caret-assign: "^=" { $$ = YYSCAN_SYMBOL(caret-assign); }
;
bar-assign: "|=" { $$ = YYSCAN_SYMBOL(bar-assign); }
;

left-bracket: "[" { $$ = YYSCAN_SYMBOL(left-bracket); }
;
right-bracket: "]" { $$ = YYSCAN_SYMBOL(right-bracket); }
;
left-paren: "(" { $$ = YYSCAN_SYMBOL(left-paren); }
;
right-paren: ")" { $$ = YYSCAN_SYMBOL(right-paren); }
;
left-brace: "{" { $$ = YYSCAN_SYMBOL(left-brace); }
;
right-brace: "}" { $$ = YYSCAN_SYMBOL(right-brace); }
;
comma: "," { $$ = YYSCAN_SYMBOL(comma); }
;
colon: ":" { $$ = YYSCAN_SYMBOL(colon); }
;
semicolon: ";" { $$ = YYSCAN_SYMBOL(semicolon); }
;
ellipsis: "..." { $$ = YYSCAN_SYMBOL(ellipsis); }
;

/* 6.1 Lexical elements */
identifier.opt
: %empty {
  $$ = YYSCAN_SYMBOL(identifier);
  $$ = yyscan_list(YYSCAN_PARAM, 1, $$);
}
| identifier
;
identifier
: TOKEN_IDENTIFIER {
  $$ = YYSCAN_SYMBOL(identifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, YYSCAN_TOKEN());
}
;
typedef-identifier
: TOKEN_TYPEDEF_IDENTIFIER {
  $$ = YYSCAN_SYMBOL(typedef-identifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, YYSCAN_TOKEN());
}
;
floating-constant
: TOKEN_FLOATING_CONSTANT {
  $$ = YYSCAN_SYMBOL(floating-constant);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, YYSCAN_TOKEN());
}
;
integer-constant
: TOKEN_INTEGER_CONSTANT {
  $$ = YYSCAN_SYMBOL(integer-constant);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, YYSCAN_TOKEN());
}
;
enumeration-constant
: TOKEN_IDENTIFIER {
  $$ = YYSCAN_SYMBOL(enumeration-constant);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, YYSCAN_TOKEN());
}
;
character-constant
: TOKEN_CHARACTER_CONSTANT {
  $$ = YYSCAN_SYMBOL(character-constant);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, YYSCAN_TOKEN());
}
;
string-literal
: TOKEN_STRING_LITERAL {
  $$ = YYSCAN_SYMBOL(string-literal);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, YYSCAN_TOKEN());
}
;

/* 6.3 Expressions */
primary-expression
: identifier {
  $$ = YYSCAN_SYMBOL(primary-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| floating-constant {
  $$ = YYSCAN_SYMBOL(primary-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| integer-constant {
  $$ = YYSCAN_SYMBOL(primary-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| character-constant {
  $$ = YYSCAN_SYMBOL(primary-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| string-literal {
  $$ = YYSCAN_SYMBOL(primary-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| left-paren expression right-paren {
  $$ = YYSCAN_SYMBOL(primary-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
postfix-expression
: primary-expression
| postfix-expression left-bracket expression right-bracket {
  $$ = YYSCAN_SYMBOL(postfix-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 5, $$, $1, $2, $3, $4);
}
| postfix-expression left-paren argument-expression-list.opt right-paren {
  $$ = YYSCAN_SYMBOL(postfix-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 5, $$, $1, $2, $3, $4);
}
| postfix-expression period identifier {
  $$ = YYSCAN_SYMBOL(postfix-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
| postfix-expression arrow identifier {
  $$ = YYSCAN_SYMBOL(postfix-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
| postfix-expression increment {
  $$ = YYSCAN_SYMBOL(postfix-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
| postfix-expression decrement {
  $$ = YYSCAN_SYMBOL(postfix-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
;
argument-expression-list.opt
: %empty {
  $$ = YYSCAN_SYMBOL(argument-expression-list);
  $$ = yyscan_list(YYSCAN_PARAM, 1, $$);
}
| argument-expression-list
;
argument-expression-list
: assignment-expression {
  $$ = YYSCAN_SYMBOL(argument-expression-list);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| argument-expression-list comma assignment-expression {
  $$ = yyscan_push(YYSCAN_PARAM, $1, $3);
}
;
unary-expression
: postfix-expression
| increment unary-expression {
  $$ = YYSCAN_SYMBOL(unary-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
| decrement unary-expression {
  $$ = YYSCAN_SYMBOL(unary-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
| unary-operator cast-expression {
  $$ = YYSCAN_SYMBOL(unary-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
| sizeof unary-expression {
  $$ = YYSCAN_SYMBOL(unary-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
| sizeof left-paren type-name right-paren {
  $$ = YYSCAN_SYMBOL(unary-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 5, $$, $1, $2, $3, $4);
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
  $$ = YYSCAN_SYMBOL(cast-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 5, $$, $1, $2, $3, $4);
}
;
multiplicative-expression
: cast-expression
| multiplicative-expression multiplicative-operator cast-expression {
  $$ = YYSCAN_SYMBOL(multiplicative-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
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
  $$ = YYSCAN_SYMBOL(additive-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
additive-operator
: plus
| minus
;
shift-expression
: additive-expression
| shift-expression shift-operator additive-expression {
  $$ = YYSCAN_SYMBOL(shift-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
shift-operator
: left-shift
| right-shift
;
relational-expression
: shift-expression
| relational-expression relational-operator shift-expression {
  $$ = YYSCAN_SYMBOL(relational-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
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
  $$ = YYSCAN_SYMBOL(equality-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
equality-operator
: equal
| not-equal
;
and-expression
: equality-expression
| and-expression ampersand equality-expression {
  $$ = YYSCAN_SYMBOL(and-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
exclusive-or-expression
: and-expression
| exclusive-or-expression caret and-expression {
  $$ = YYSCAN_SYMBOL(exclusive-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
inclusive-or-expression
: exclusive-or-expression
| inclusive-or-expression bar exclusive-or-expression {
  $$ = YYSCAN_SYMBOL(inclusive-or-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
logical-and-expression
: inclusive-or-expression
| logical-and-expression and inclusive-or-expression {
  $$ = YYSCAN_SYMBOL(logical-and-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
logical-or-expression
: logical-and-expression
| logical-or-expression or logical-and-expression {
  $$ = YYSCAN_SYMBOL(logical-or-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
conditional-expression
: logical-or-expression
| logical-or-expression question expression colon conditional-expression {
  $$ = YYSCAN_SYMBOL(conditional-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 6, $$, $1, $2, $3, $4, $5);
}
;
assignment-expression
: conditional-expression
| unary-expression assignment-operator assignment-expression {
  $$ = YYSCAN_SYMBOL(assignment-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
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
  $$ = YYSCAN_SYMBOL(expression);
  $$ = yyscan_list(YYSCAN_PARAM, 1, $$);
}
| expression
;
expression
: assignment-expression {
  $$ = YYSCAN_SYMBOL(expression);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| expression comma assignment-expression {
  $$ = yyscan_push(YYSCAN_PARAM, $1, $3);
}
;

/* 6.4 Constant expressions */
constant-expression.opt
: %empty {
  $$ = YYSCAN_SYMBOL(constant-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 1, $$);
}
| constant-expression
;
constant-expression
: conditional-expression {
  $$ = YYSCAN_SYMBOL(constant-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
;

/* 6.5 Declarations */
declaration
: declaration-specifiers init-declarator-list.opt semicolon {
  $$ = YYSCAN_SYMBOL(declaration);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
declaration-specifiers
: declaration-specifier {
  $$ = YYSCAN_SYMBOL(declaration-specifiers);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| declaration-specifiers declaration-specifier {
  $$ = yyscan_push(YYSCAN_PARAM, $1, $2);
}
;
declaration-specifier
: storage-class-specifier
| type-specifier
| type-qualifier
;
init-declarator-list.opt
: %empty {
  $$ = YYSCAN_SYMBOL(init-declarator-list);
  $$ = yyscan_list(YYSCAN_PARAM, 1, $$);
}
| init-declarator-list
;
init-declarator-list
: init-declarator {
  $$ = YYSCAN_SYMBOL(init-declarator-list);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| init-declarator-list comma init-declarator {
  $$ = yyscan_push(YYSCAN_PARAM, $1, $3);
}
;
init-declarator
: declarator {
  $$ = YYSCAN_SYMBOL(init-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| declarator assign initializer {
  $$ = YYSCAN_SYMBOL(init-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
storage-class-specifier
: typedef {
  $$ = YYSCAN_SYMBOL(storage-class-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| extern {
  $$ = YYSCAN_SYMBOL(storage-class-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| static {
  $$ = YYSCAN_SYMBOL(storage-class-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| auto {
  $$ = YYSCAN_SYMBOL(storage-class-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| register {
  $$ = YYSCAN_SYMBOL(storage-class-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
;
type-specifier
: void {
  $$ = YYSCAN_SYMBOL(type-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| char {
  $$ = YYSCAN_SYMBOL(type-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| short {
  $$ = YYSCAN_SYMBOL(type-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| int {
  $$ = YYSCAN_SYMBOL(type-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| long {
  $$ = YYSCAN_SYMBOL(type-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| float {
  $$ = YYSCAN_SYMBOL(type-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| double {
  $$ = YYSCAN_SYMBOL(type-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| signed {
  $$ = YYSCAN_SYMBOL(type-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| unsigned {
  $$ = YYSCAN_SYMBOL(type-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| struct-or-union-specifier {
  $$ = YYSCAN_SYMBOL(type-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| enum-specifier {
  $$ = YYSCAN_SYMBOL(type-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| typedef-name {
  $$ = YYSCAN_SYMBOL(type-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
;
struct-or-union-specifier
: struct-or-union identifier.opt left-brace struct-declaration-list right-brace {
  $$ = YYSCAN_SYMBOL(struct-or-union-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 6, $$, $1, $2, $3, $4, $5);
}
| struct-or-union identifier {
  $$ = YYSCAN_SYMBOL(struct-or-union-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
;
struct-or-union
: struct {
  $$ = YYSCAN_SYMBOL(struct-or-union);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| union {
  $$ = YYSCAN_SYMBOL(struct-or-union);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
;
struct-declaration-list
: struct-declaration {
  $$ = YYSCAN_SYMBOL(struct-declaration-list);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| struct-declaration-list struct-declaration {
  $$ = yyscan_push(YYSCAN_PARAM, $1, $2);
}
;
struct-declaration
: specifier-qualifier-list struct-declarator-list semicolon {
  $$ = YYSCAN_SYMBOL(struct-declaration);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
specifier-qualifier-list
: specifier-qualifier {
  $$ = YYSCAN_SYMBOL(specifier-qualifier-list);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| specifier-qualifier-list specifier-qualifier {
  $$ = yyscan_push(YYSCAN_PARAM, $1, $2);
}
;
specifier-qualifier
: type-specifier
| type-qualifier
;
struct-declarator-list
: struct-declarator {
  $$ = YYSCAN_SYMBOL(struct-declarator-list);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| struct-declarator-list comma struct-declarator {
  $$ = yyscan_push(YYSCAN_PARAM, $1, $3);
}
;
struct-declarator
: declarator {
  $$ = YYSCAN_SYMBOL(struct-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| declarator.opt colon constant-expression {
  $$ = YYSCAN_SYMBOL(struct-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
enum-specifier
: enum identifier.opt left-brace enumerator-list right-brace {
  $$ = YYSCAN_SYMBOL(enum-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 6, $$, $1, $2, $3, $4, $5);
}
| enum identifier {
  $$ = YYSCAN_SYMBOL(enum-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
;
enumerator-list
: enumerator {
  $$ = YYSCAN_SYMBOL(enumerator-list);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| enumerator-list comma enumerator {
  $$ = yyscan_push(YYSCAN_PARAM, $1, $3);
}
;
enumerator
: enumeration-constant {
  $$ = YYSCAN_SYMBOL(enumerator);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| enumeration-constant assign constant-expression {
  $$ = YYSCAN_SYMBOL(enumerator);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
type-qualifier
: const {
  $$ = YYSCAN_SYMBOL(type-qualifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| volatile {
  $$ = YYSCAN_SYMBOL(type-qualifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
;
declarator.opt
: %empty {
  $$ = YYSCAN_SYMBOL(declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 1, $$);
}
| declarator
;
declarator
: direct-declarator {
  $$ = YYSCAN_SYMBOL(declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| pointer direct-declarator {
  $$ = YYSCAN_SYMBOL(declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
;
direct-declarator
: identifier {
  $$ = YYSCAN_SYMBOL(direct-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| left-paren declarator right-paren {
  $$ = YYSCAN_SYMBOL(direct-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
| direct-declarator left-bracket constant-expression.opt right-bracket {
  $$ = YYSCAN_SYMBOL(direct-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 5, $$, $1, $2, $3, $4);
}
| direct-declarator left-paren parameter-type-list right-paren {
  $$ = YYSCAN_SYMBOL(direct-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 5, $$, $1, $2, $3, $4);
}
| direct-declarator left-paren identifier-list.opt right-paren {
  $$ = YYSCAN_SYMBOL(direct-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 5, $$, $1, $2, $3, $4);
}
;
pointer
: asterisk type-qualifier-list.opt {
  $$ = YYSCAN_SYMBOL(pointer);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
| pointer asterisk type-qualifier-list.opt {
  $$ = YYSCAN_SYMBOL(pointer);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
type-qualifier-list.opt
: %empty {
  $$ = YYSCAN_SYMBOL(type-qualifier-list);
  $$ = yyscan_list(YYSCAN_PARAM, 1, $$);
}
| type-qualifier-list
;
type-qualifier-list
: type-qualifier {
  $$ = YYSCAN_SYMBOL(type-qualifier-list);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| type-qualifier-list type-qualifier {
  $$ = yyscan_push(YYSCAN_PARAM, $1, $2);
}
;
parameter-type-list.opt
: %empty {
  $$ = YYSCAN_SYMBOL(parameter-type-list);
  $$ = yyscan_list(YYSCAN_PARAM, 1, $$);
}
| parameter-type-list
;
parameter-type-list
: parameter-list {
  $$ = YYSCAN_SYMBOL(parameter-type-list);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| parameter-list comma ellipsis {
  $$ = YYSCAN_SYMBOL(parameter-type-list);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
parameter-list
: parameter-declaration {
  $$ = YYSCAN_SYMBOL(parameter-list);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| parameter-list comma parameter-declaration {
  $$ = yyscan_push(YYSCAN_PARAM, $1, $3);
}
;
parameter-declaration
: declaration-specifiers declarator {
  $$ = YYSCAN_SYMBOL(parameter-declaration);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
| declaration-specifiers abstract-declarator.opt {
  $$ = YYSCAN_SYMBOL(parameter-declaration);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
;
identifier-list.opt
: %empty {
  $$ = YYSCAN_SYMBOL(identifier-list);
  $$ = yyscan_list(YYSCAN_PARAM, 1, $$);
}
| identifier-list
;
identifier-list
: identifier {
  $$ = YYSCAN_SYMBOL(identifier-list);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| identifier-list comma identifier {
  $$ = yyscan_push(YYSCAN_PARAM, $1, $3);
}
;
type-name
: specifier-qualifier-list abstract-declarator.opt {
  $$ = YYSCAN_SYMBOL(type-name);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
;
abstract-declarator.opt
: %empty {
  $$ = YYSCAN_SYMBOL(abstract-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 1, $$);
}
| abstract-declarator
;
abstract-declarator
: pointer {
  $$ = YYSCAN_SYMBOL(abstract-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| direct-abstract-declarator {
  $$ = YYSCAN_SYMBOL(abstract-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| pointer direct-abstract-declarator {
  $$ = YYSCAN_SYMBOL(abstract-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
;
direct-abstract-declarator
: left-paren abstract-declarator right-paren {
  $$ = YYSCAN_SYMBOL(direct-abstract-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
| left-bracket constant-expression.opt right-bracket {
  $$ = YYSCAN_SYMBOL(direct-abstract-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
| direct-abstract-declarator left-bracket constant-expression.opt right-bracket {
  $$ = YYSCAN_SYMBOL(direct-abstract-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 5, $$, $1, $2, $3, $4);
}
| left-paren parameter-type-list.opt right-paren {
  $$ = YYSCAN_SYMBOL(direct-abstract-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
| direct-abstract-declarator left-paren parameter-type-list.opt right-paren {
  $$ = YYSCAN_SYMBOL(direct-abstract-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 5, $$, $1, $2, $3, $4);
}
;
typedef-name
: typedef-identifier {
  $$ = YYSCAN_SYMBOL(typedef-name);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
;
initializer
: assignment-expression {
  $$ = YYSCAN_SYMBOL(initializer);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| left-brace initializer-list right-brace {
  $$ = YYSCAN_SYMBOL(initializer);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
| left-brace initializer-list comma right-brace {
  $$ = YYSCAN_SYMBOL(initializer);
  $$ = yyscan_list(YYSCAN_PARAM, 5, $$, $1, $2, $3, $4);
}
;
initializer-list
: initializer {
  $$ = YYSCAN_SYMBOL(initializer-list);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| initializer-list comma initializer {
  $$ = yyscan_push(YYSCAN_PARAM, $1, $3);
}
;

/* 6.6 Statements */
statement
: labeled-statement {
  $$ = YYSCAN_SYMBOL(statement);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| compound-statement {
  $$ = YYSCAN_SYMBOL(statement);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| expression-statement {
  $$ = YYSCAN_SYMBOL(statement);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| selection-statement {
  $$ = YYSCAN_SYMBOL(statement);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| iteration-statement {
  $$ = YYSCAN_SYMBOL(statement);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| jump-statement {
  $$ = YYSCAN_SYMBOL(statement);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
;
labeled-statement
: identifier colon statement {
  $$ = YYSCAN_SYMBOL(labeled-statement);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
| case constant-expression colon statement {
  $$ = YYSCAN_SYMBOL(labeled-statement);
  $$ = yyscan_list(YYSCAN_PARAM, 5, $$, $1, $2, $3, $4);
}
| default colon statement {
  $$ = YYSCAN_SYMBOL(labeled-statement);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
compound-statement
: left-brace declaration-list.opt statement-list.opt right-brace {
  $$ = YYSCAN_SYMBOL(compound-statement);
  $$ = yyscan_list(YYSCAN_PARAM, 5, $$, $1, $2, $3, $4);
}
;
declaration-list.opt
: %empty {
  $$ = YYSCAN_SYMBOL(declaration-list);
  $$ = yyscan_list(YYSCAN_PARAM, 1, $$);
}
| declaration-list
;
declaration-list
: declaration {
  $$ = YYSCAN_SYMBOL(declaration-list);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| declaration-list declaration {
  $$ = yyscan_push(YYSCAN_PARAM, $1, $2);
}
;
statement-list.opt
: %empty {
  $$ = YYSCAN_SYMBOL(statement-list);
  $$ = yyscan_list(YYSCAN_PARAM, 1, $$);
}
| statement-list
;
statement-list
: statement {
  $$ = YYSCAN_SYMBOL(statement-list);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| statement-list statement {
  $$ = yyscan_push(YYSCAN_PARAM, $1, $2);
}
;
expression-statement
: expression.opt semicolon {
  $$ = YYSCAN_SYMBOL(expression-statement);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
;
selection-statement
: if left-paren expression right-paren statement %prec THEN {
  $$ = YYSCAN_SYMBOL(selection-statement);
  $$ = yyscan_list(YYSCAN_PARAM, 6, $$, $1, $2, $3, $4, $5);
}
| if left-paren expression right-paren statement else statement {
  $$ = YYSCAN_SYMBOL(selection-statement);
  $$ = yyscan_list(YYSCAN_PARAM, 8, $$, $1, $2, $3, $4, $5, $6, $7);
}
| switch left-paren expression right-paren statement {
  $$ = YYSCAN_SYMBOL(selection-statement);
  $$ = yyscan_list(YYSCAN_PARAM, 6, $$, $1, $2, $3, $4, $5);
}
;
iteration-statement
: while left-paren expression right-paren statement {
  $$ = YYSCAN_SYMBOL(iteration-statement);
  $$ = yyscan_list(YYSCAN_PARAM, 6, $$, $1, $2, $3, $4, $5);
}
| do statement while left-paren expression right-paren semicolon {
  $$ = YYSCAN_SYMBOL(iteration-statement);
  $$ = yyscan_list(YYSCAN_PARAM, 8, $$, $1, $2, $3, $4, $5, $6, $7);
}
| for left-paren expression.opt semicolon expression.opt semicolon expression.opt right-paren statement {
  $$ = YYSCAN_SYMBOL(iteration-statement);
  $$ = yyscan_list(YYSCAN_PARAM, 10, $$, $1, $2, $3, $4, $5, $6, $7, $8, $9);
}
;
jump-statement
: goto identifier semicolon {
  $$ = YYSCAN_SYMBOL(jump-statement);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
| continue semicolon {
  $$ = YYSCAN_SYMBOL(jump-statement);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
| break semicolon {
  $$ = YYSCAN_SYMBOL(jump-statement);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
| return expression.opt semicolon {
  $$ = YYSCAN_SYMBOL(jump-statement);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;

/* 6.7 External definitions */
top
: translation-unit { yyscan_set_ast(YYSCAN_PARAM, $1); }
;
translation-unit
: external-declaration {
  $$ = YYSCAN_SYMBOL(translation-unit);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| translation-unit external-declaration {
  $$ = yyscan_push(YYSCAN_PARAM, $1, $2);
}
;
external-declaration
: function-definition
| declaration {
  yyscan_register_typedef(YYSCAN_PARAM, $1);
  $$ = YYSCAN_SYMBOL(external-declaration);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
;
function-definition
: declarator declaration-list.opt compound-statement {
  $$ = YYSCAN_SYMBOL(function-definition);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
| declaration-specifiers declarator declaration-list.opt compound-statement {
  $$ = YYSCAN_SYMBOL(function-definition);
  $$ = yyscan_list(YYSCAN_PARAM, 5, $$, $1, $2, $3, $4);
}
;

%%
