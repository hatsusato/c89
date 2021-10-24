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

auto: "auto" { $$ = YYSCAN_TOKEN(auto); }
;
break: "break" { $$ = YYSCAN_TOKEN(break); }
;
case: "case" { $$ = YYSCAN_TOKEN(case); }
;
char: "char" { $$ = YYSCAN_TOKEN(char); }
;
const: "const" { $$ = YYSCAN_TOKEN(const); }
;
continue: "continue" { $$ = YYSCAN_TOKEN(continue); }
;
default: "default" { $$ = YYSCAN_TOKEN(default); }
;
do: "do" { $$ = YYSCAN_TOKEN(do); }
;
double: "double" { $$ = YYSCAN_TOKEN(double); }
;
else: "else" { $$ = YYSCAN_TOKEN(else); }
;
enum: "enum" { $$ = YYSCAN_TOKEN(enum); }
;
extern: "extern" { $$ = YYSCAN_TOKEN(extern); }
;
float: "float" { $$ = YYSCAN_TOKEN(float); }
;
for: "for" { $$ = YYSCAN_TOKEN(for); }
;
goto: "goto" { $$ = YYSCAN_TOKEN(goto); }
;
if: "if" { $$ = YYSCAN_TOKEN(if); }
;
int: "int" { $$ = YYSCAN_TOKEN(int); }
;
long: "long" { $$ = YYSCAN_TOKEN(long); }
;
register: "register" { $$ = YYSCAN_TOKEN(register); }
;
return: "return" { $$ = YYSCAN_TOKEN(return); }
;
short: "short" { $$ = YYSCAN_TOKEN(short); }
;
signed: "signed" { $$ = YYSCAN_TOKEN(signed); }
;
sizeof: "sizeof" { $$ = YYSCAN_TOKEN(sizeof); }
;
static: "static" { $$ = YYSCAN_TOKEN(static); }
;
struct: "struct" { $$ = YYSCAN_TOKEN(struct); }
;
switch: "switch" { $$ = YYSCAN_TOKEN(switch); }
;
typedef: "typedef" { $$ = YYSCAN_TOKEN(typedef); }
;
union: "union" { $$ = YYSCAN_TOKEN(union); }
;
unsigned: "unsigned" { $$ = YYSCAN_TOKEN(unsigned); }
;
void: "void" { $$ = YYSCAN_TOKEN(void); }
;
volatile: "volatile" { $$ = YYSCAN_TOKEN(volatile); }
;
while: "while" { $$ = YYSCAN_TOKEN(while); }
;

period: "." { $$ = YYSCAN_TOKEN(period); }
;
arrow: "->" { $$ = YYSCAN_TOKEN(arrow); }
;
increment: "++" { $$ = YYSCAN_TOKEN(increment); }
;
decrement: "--" { $$ = YYSCAN_TOKEN(decrement); }
;
ampersand: "&" { $$ = YYSCAN_TOKEN(ampersand); }
;
asterisk: "*" { $$ = YYSCAN_TOKEN(asterisk); }
;
plus: "+" { $$ = YYSCAN_TOKEN(plus); }
;
minus: "-" { $$ = YYSCAN_TOKEN(minus); }
;
tilde: "~" { $$ = YYSCAN_TOKEN(tilde); }
;
exclamation: "!" { $$ = YYSCAN_TOKEN(exclamation); }
;
slash: "/" { $$ = YYSCAN_TOKEN(slash); }
;
percent: "%" { $$ = YYSCAN_TOKEN(percent); }
;
left-shift: "<<" { $$ = YYSCAN_TOKEN(left-shift); }
;
right-shift: ">>" { $$ = YYSCAN_TOKEN(right-shift); }
;
less-than: "<" { $$ = YYSCAN_TOKEN(less-than); }
;
greater-than: ">" { $$ = YYSCAN_TOKEN(greater-than); }
;
less-equal: "<=" { $$ = YYSCAN_TOKEN(less-equal); }
;
greater-equal: ">=" { $$ = YYSCAN_TOKEN(greater-equal); }
;
equal: "==" { $$ = YYSCAN_TOKEN(equal); }
;
not-equal: "!=" { $$ = YYSCAN_TOKEN(not-equal); }
;
caret: "^" { $$ = YYSCAN_TOKEN(caret); }
;
bar: "|" { $$ = YYSCAN_TOKEN(bar); }
;
and: "&&" { $$ = YYSCAN_TOKEN(and); }
;
or: "||" { $$ = YYSCAN_TOKEN(or); }
;
question: "?" { $$ = YYSCAN_TOKEN(question); }
;
assign: "=" { $$ = YYSCAN_TOKEN(assign); }
;
asterisk-assign: "*=" { $$ = YYSCAN_TOKEN(asterisk-assign); }
;
slash-assign: "/=" { $$ = YYSCAN_TOKEN(slash-assign); }
;
percent-assign: "%=" { $$ = YYSCAN_TOKEN(percent-assign); }
;
plus-assign: "+=" { $$ = YYSCAN_TOKEN(plus-assign); }
;
minus-assign: "-=" { $$ = YYSCAN_TOKEN(minus-assign); }
;
left-shift-assign: "<<=" { $$ = YYSCAN_TOKEN(left-shift-assign); }
;
right-shift-assign: ">>=" { $$ = YYSCAN_TOKEN(right-shift-assign); }
;
ampersand-assign: "&=" { $$ = YYSCAN_TOKEN(ampersand-assign); }
;
caret-assign: "^=" { $$ = YYSCAN_TOKEN(caret-assign); }
;
bar-assign: "|=" { $$ = YYSCAN_TOKEN(bar-assign); }
;

left-bracket: "[" { $$ = YYSCAN_TOKEN(left-bracket); }
;
right-bracket: "]" { $$ = YYSCAN_TOKEN(right-bracket); }
;
left-paren: "(" { $$ = YYSCAN_TOKEN(left-paren); }
;
right-paren: ")" { $$ = YYSCAN_TOKEN(right-paren); }
;
left-brace: "{" { $$ = YYSCAN_TOKEN(left-brace); }
;
right-brace: "}" { $$ = YYSCAN_TOKEN(right-brace); }
;
comma: "," { $$ = YYSCAN_TOKEN(comma); }
;
colon: ":" { $$ = YYSCAN_TOKEN(colon); }
;
semicolon: ";" { $$ = YYSCAN_TOKEN(semicolon); }
;
ellipsis: "..." { $$ = YYSCAN_TOKEN(ellipsis); }
;

/* 6.1 Lexical elements */
identifier.opt
: %empty {
  $$ = YYSCAN_TOKEN(identifier);
  $$ = yyscan_list(YYSCAN_PARAM, 1, $$);
}
| identifier
;
identifier
: TOKEN_IDENTIFIER {
  $$ = YYSCAN_TOKEN(identifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, YYSCAN_SYMBOL());
}
;
typedef-identifier
: TOKEN_TYPEDEF_IDENTIFIER {
  $$ = YYSCAN_TOKEN(typedef-identifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, YYSCAN_SYMBOL());
}
;
floating-constant
: TOKEN_FLOATING_CONSTANT {
  $$ = YYSCAN_TOKEN(floating-constant);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, YYSCAN_SYMBOL());
}
;
integer-constant
: TOKEN_INTEGER_CONSTANT {
  $$ = YYSCAN_TOKEN(integer-constant);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, YYSCAN_SYMBOL());
}
;
enumeration-constant
: TOKEN_IDENTIFIER {
  $$ = YYSCAN_TOKEN(enumeration-constant);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, YYSCAN_SYMBOL());
}
;
character-constant
: TOKEN_CHARACTER_CONSTANT {
  $$ = YYSCAN_TOKEN(character-constant);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, YYSCAN_SYMBOL());
}
;
string-literal
: TOKEN_STRING_LITERAL {
  $$ = YYSCAN_TOKEN(string-literal);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, YYSCAN_SYMBOL());
}
;

/* 6.3 Expressions */
primary-expression
: identifier {
  $$ = YYSCAN_TOKEN(primary-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| floating-constant {
  $$ = YYSCAN_TOKEN(primary-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| integer-constant {
  $$ = YYSCAN_TOKEN(primary-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| character-constant {
  $$ = YYSCAN_TOKEN(primary-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| string-literal {
  $$ = YYSCAN_TOKEN(primary-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| left-paren expression right-paren {
  $$ = YYSCAN_TOKEN(primary-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
postfix-expression
: primary-expression
| postfix-expression left-bracket expression right-bracket {
  $$ = YYSCAN_TOKEN(postfix-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 5, $$, $1, $2, $3, $4);
}
| postfix-expression left-paren argument-expression-list.opt right-paren {
  $$ = YYSCAN_TOKEN(postfix-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 5, $$, $1, $2, $3, $4);
}
| postfix-expression period identifier {
  $$ = YYSCAN_TOKEN(postfix-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
| postfix-expression arrow identifier {
  $$ = YYSCAN_TOKEN(postfix-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
| postfix-expression increment {
  $$ = YYSCAN_TOKEN(postfix-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
| postfix-expression decrement {
  $$ = YYSCAN_TOKEN(postfix-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
;
argument-expression-list.opt
: %empty {
  $$ = YYSCAN_TOKEN(argument-expression-list);
  $$ = yyscan_list(YYSCAN_PARAM, 1, $$);
}
| argument-expression-list
;
argument-expression-list
: assignment-expression {
  $$ = YYSCAN_TOKEN(argument-expression-list);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| argument-expression-list comma assignment-expression {
  $$ = yyscan_push(YYSCAN_PARAM, $1, $3);
}
;
unary-expression
: postfix-expression
| increment unary-expression {
  $$ = YYSCAN_TOKEN(unary-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
| decrement unary-expression {
  $$ = YYSCAN_TOKEN(unary-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
| unary-operator cast-expression {
  $$ = YYSCAN_TOKEN(unary-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
| sizeof unary-expression {
  $$ = YYSCAN_TOKEN(unary-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
| sizeof left-paren type-name right-paren {
  $$ = YYSCAN_TOKEN(unary-expression);
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
  $$ = YYSCAN_TOKEN(cast-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 5, $$, $1, $2, $3, $4);
}
;
multiplicative-expression
: cast-expression
| multiplicative-expression multiplicative-operator cast-expression {
  $$ = YYSCAN_TOKEN(multiplicative-expression);
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
  $$ = YYSCAN_TOKEN(additive-expression);
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
  $$ = YYSCAN_TOKEN(shift-expression);
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
  $$ = YYSCAN_TOKEN(relational-expression);
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
  $$ = YYSCAN_TOKEN(equality-expression);
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
  $$ = YYSCAN_TOKEN(and-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
exclusive-or-expression
: and-expression
| exclusive-or-expression caret and-expression {
  $$ = YYSCAN_TOKEN(exclusive-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
inclusive-or-expression
: exclusive-or-expression
| inclusive-or-expression bar exclusive-or-expression {
  $$ = YYSCAN_TOKEN(inclusive-or-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
logical-and-expression
: inclusive-or-expression
| logical-and-expression and inclusive-or-expression {
  $$ = YYSCAN_TOKEN(logical-and-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
logical-or-expression
: logical-and-expression
| logical-or-expression or logical-and-expression {
  $$ = YYSCAN_TOKEN(logical-or-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
conditional-expression
: logical-or-expression
| logical-or-expression question expression colon conditional-expression {
  $$ = YYSCAN_TOKEN(conditional-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 6, $$, $1, $2, $3, $4, $5);
}
;
assignment-expression
: conditional-expression
| unary-expression assignment-operator assignment-expression {
  $$ = YYSCAN_TOKEN(assignment-expression);
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
  $$ = YYSCAN_TOKEN(expression);
  $$ = yyscan_list(YYSCAN_PARAM, 1, $$);
}
| expression
;
expression
: assignment-expression {
  $$ = YYSCAN_TOKEN(expression);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| expression comma assignment-expression {
  $$ = yyscan_push(YYSCAN_PARAM, $1, $3);
}
;

/* 6.4 Constant expressions */
constant-expression.opt
: %empty {
  $$ = YYSCAN_TOKEN(constant-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 1, $$);
}
| constant-expression
;
constant-expression
: conditional-expression {
  $$ = YYSCAN_TOKEN(constant-expression);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
;

/* 6.5 Declarations */
declaration
: declaration-specifiers init-declarator-list.opt semicolon {
  $$ = YYSCAN_TOKEN(declaration);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
declaration-specifiers
: declaration-specifier {
  $$ = YYSCAN_TOKEN(declaration-specifiers);
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
  $$ = YYSCAN_TOKEN(init-declarator-list);
  $$ = yyscan_list(YYSCAN_PARAM, 1, $$);
}
| init-declarator-list
;
init-declarator-list
: init-declarator {
  $$ = YYSCAN_TOKEN(init-declarator-list);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| init-declarator-list comma init-declarator {
  $$ = yyscan_push(YYSCAN_PARAM, $1, $3);
}
;
init-declarator
: declarator {
  $$ = YYSCAN_TOKEN(init-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| declarator assign initializer {
  $$ = YYSCAN_TOKEN(init-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
storage-class-specifier
: typedef {
  $$ = YYSCAN_TOKEN(storage-class-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| extern {
  $$ = YYSCAN_TOKEN(storage-class-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| static {
  $$ = YYSCAN_TOKEN(storage-class-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| auto {
  $$ = YYSCAN_TOKEN(storage-class-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| register {
  $$ = YYSCAN_TOKEN(storage-class-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
;
type-specifier
: void {
  $$ = YYSCAN_TOKEN(type-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| char {
  $$ = YYSCAN_TOKEN(type-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| short {
  $$ = YYSCAN_TOKEN(type-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| int {
  $$ = YYSCAN_TOKEN(type-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| long {
  $$ = YYSCAN_TOKEN(type-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| float {
  $$ = YYSCAN_TOKEN(type-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| double {
  $$ = YYSCAN_TOKEN(type-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| signed {
  $$ = YYSCAN_TOKEN(type-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| unsigned {
  $$ = YYSCAN_TOKEN(type-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| struct-or-union-specifier {
  $$ = YYSCAN_TOKEN(type-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| enum-specifier {
  $$ = YYSCAN_TOKEN(type-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| typedef-name {
  $$ = YYSCAN_TOKEN(type-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
;
struct-or-union-specifier
: struct-or-union identifier.opt left-brace struct-declaration-list right-brace {
  $$ = YYSCAN_TOKEN(struct-or-union-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 6, $$, $1, $2, $3, $4, $5);
}
| struct-or-union identifier {
  $$ = YYSCAN_TOKEN(struct-or-union-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
;
struct-or-union
: struct {
  $$ = YYSCAN_TOKEN(struct-or-union);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| union {
  $$ = YYSCAN_TOKEN(struct-or-union);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
;
struct-declaration-list
: struct-declaration {
  $$ = YYSCAN_TOKEN(struct-declaration-list);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| struct-declaration-list struct-declaration {
  $$ = yyscan_push(YYSCAN_PARAM, $1, $2);
}
;
struct-declaration
: specifier-qualifier-list struct-declarator-list semicolon {
  $$ = YYSCAN_TOKEN(struct-declaration);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
specifier-qualifier-list
: specifier-qualifier {
  $$ = YYSCAN_TOKEN(specifier-qualifier-list);
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
  $$ = YYSCAN_TOKEN(struct-declarator-list);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| struct-declarator-list comma struct-declarator {
  $$ = yyscan_push(YYSCAN_PARAM, $1, $3);
}
;
struct-declarator
: declarator {
  $$ = YYSCAN_TOKEN(struct-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| declarator.opt colon constant-expression {
  $$ = YYSCAN_TOKEN(struct-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
enum-specifier
: enum identifier.opt left-brace enumerator-list right-brace {
  $$ = YYSCAN_TOKEN(enum-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 6, $$, $1, $2, $3, $4, $5);
}
| enum identifier {
  $$ = YYSCAN_TOKEN(enum-specifier);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
;
enumerator-list
: enumerator {
  $$ = YYSCAN_TOKEN(enumerator-list);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| enumerator-list comma enumerator {
  $$ = yyscan_push(YYSCAN_PARAM, $1, $3);
}
;
enumerator
: enumeration-constant {
  $$ = YYSCAN_TOKEN(enumerator);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| enumeration-constant assign constant-expression {
  $$ = YYSCAN_TOKEN(enumerator);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
type-qualifier
: const {
  $$ = YYSCAN_TOKEN(type-qualifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| volatile {
  $$ = YYSCAN_TOKEN(type-qualifier);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
;
declarator.opt
: %empty {
  $$ = YYSCAN_TOKEN(declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 1, $$);
}
| declarator
;
declarator
: direct-declarator {
  $$ = YYSCAN_TOKEN(declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| pointer direct-declarator {
  $$ = YYSCAN_TOKEN(declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
;
direct-declarator
: identifier {
  $$ = YYSCAN_TOKEN(direct-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| left-paren declarator right-paren {
  $$ = YYSCAN_TOKEN(direct-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
| direct-declarator left-bracket constant-expression.opt right-bracket {
  $$ = YYSCAN_TOKEN(direct-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 5, $$, $1, $2, $3, $4);
}
| direct-declarator left-paren parameter-type-list right-paren {
  $$ = YYSCAN_TOKEN(direct-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 5, $$, $1, $2, $3, $4);
}
| direct-declarator left-paren identifier-list.opt right-paren {
  $$ = YYSCAN_TOKEN(direct-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 5, $$, $1, $2, $3, $4);
}
;
pointer
: asterisk type-qualifier-list.opt {
  $$ = YYSCAN_TOKEN(pointer);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
| pointer asterisk type-qualifier-list.opt {
  $$ = YYSCAN_TOKEN(pointer);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
type-qualifier-list.opt
: %empty {
  $$ = YYSCAN_TOKEN(type-qualifier-list);
  $$ = yyscan_list(YYSCAN_PARAM, 1, $$);
}
| type-qualifier-list
;
type-qualifier-list
: type-qualifier {
  $$ = YYSCAN_TOKEN(type-qualifier-list);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| type-qualifier-list type-qualifier {
  $$ = yyscan_push(YYSCAN_PARAM, $1, $2);
}
;
parameter-type-list.opt
: %empty {
  $$ = YYSCAN_TOKEN(parameter-type-list);
  $$ = yyscan_list(YYSCAN_PARAM, 1, $$);
}
| parameter-type-list
;
parameter-type-list
: parameter-list {
  $$ = YYSCAN_TOKEN(parameter-type-list);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| parameter-list comma ellipsis {
  $$ = YYSCAN_TOKEN(parameter-type-list);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
parameter-list
: parameter-declaration {
  $$ = YYSCAN_TOKEN(parameter-list);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| parameter-list comma parameter-declaration {
  $$ = yyscan_push(YYSCAN_PARAM, $1, $3);
}
;
parameter-declaration
: declaration-specifiers declarator {
  $$ = YYSCAN_TOKEN(parameter-declaration);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
| declaration-specifiers abstract-declarator.opt {
  $$ = YYSCAN_TOKEN(parameter-declaration);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
;
identifier-list.opt
: %empty {
  $$ = YYSCAN_TOKEN(identifier-list);
  $$ = yyscan_list(YYSCAN_PARAM, 1, $$);
}
| identifier-list
;
identifier-list
: identifier {
  $$ = YYSCAN_TOKEN(identifier-list);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| identifier-list comma identifier {
  $$ = yyscan_push(YYSCAN_PARAM, $1, $3);
}
;
type-name
: specifier-qualifier-list abstract-declarator.opt {
  $$ = YYSCAN_TOKEN(type-name);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
;
abstract-declarator.opt
: %empty {
  $$ = YYSCAN_TOKEN(abstract-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 1, $$);
}
| abstract-declarator
;
abstract-declarator
: pointer {
  $$ = YYSCAN_TOKEN(abstract-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| direct-abstract-declarator {
  $$ = YYSCAN_TOKEN(abstract-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| pointer direct-abstract-declarator {
  $$ = YYSCAN_TOKEN(abstract-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
;
direct-abstract-declarator
: left-paren abstract-declarator right-paren {
  $$ = YYSCAN_TOKEN(direct-abstract-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
| left-bracket constant-expression.opt right-bracket {
  $$ = YYSCAN_TOKEN(direct-abstract-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
| direct-abstract-declarator left-bracket constant-expression.opt right-bracket {
  $$ = YYSCAN_TOKEN(direct-abstract-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 5, $$, $1, $2, $3, $4);
}
| left-paren parameter-type-list.opt right-paren {
  $$ = YYSCAN_TOKEN(direct-abstract-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
| direct-abstract-declarator left-paren parameter-type-list.opt right-paren {
  $$ = YYSCAN_TOKEN(direct-abstract-declarator);
  $$ = yyscan_list(YYSCAN_PARAM, 5, $$, $1, $2, $3, $4);
}
;
typedef-name
: typedef-identifier {
  $$ = YYSCAN_TOKEN(typedef-name);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
;
initializer
: assignment-expression {
  $$ = YYSCAN_TOKEN(initializer);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| left-brace initializer-list right-brace {
  $$ = YYSCAN_TOKEN(initializer);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
| left-brace initializer-list comma right-brace {
  $$ = YYSCAN_TOKEN(initializer);
  $$ = yyscan_list(YYSCAN_PARAM, 5, $$, $1, $2, $3, $4);
}
;
initializer-list
: initializer {
  $$ = YYSCAN_TOKEN(initializer-list);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| initializer-list comma initializer {
  $$ = yyscan_push(YYSCAN_PARAM, $1, $3);
}
;

/* 6.6 Statements */
statement
: labeled-statement {
  $$ = YYSCAN_TOKEN(statement);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| compound-statement {
  $$ = YYSCAN_TOKEN(statement);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| expression-statement {
  $$ = YYSCAN_TOKEN(statement);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| selection-statement {
  $$ = YYSCAN_TOKEN(statement);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| iteration-statement {
  $$ = YYSCAN_TOKEN(statement);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| jump-statement {
  $$ = YYSCAN_TOKEN(statement);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
;
labeled-statement
: identifier colon statement {
  $$ = YYSCAN_TOKEN(labeled-statement);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
| case constant-expression colon statement {
  $$ = YYSCAN_TOKEN(labeled-statement);
  $$ = yyscan_list(YYSCAN_PARAM, 5, $$, $1, $2, $3, $4);
}
| default colon statement {
  $$ = YYSCAN_TOKEN(labeled-statement);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;
compound-statement
: left-brace declaration-list.opt statement-list.opt right-brace {
  $$ = YYSCAN_TOKEN(compound-statement);
  $$ = yyscan_list(YYSCAN_PARAM, 5, $$, $1, $2, $3, $4);
}
;
declaration-list.opt
: %empty {
  $$ = YYSCAN_TOKEN(declaration-list);
  $$ = yyscan_list(YYSCAN_PARAM, 1, $$);
}
| declaration-list
;
declaration-list
: declaration {
  $$ = YYSCAN_TOKEN(declaration-list);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| declaration-list declaration {
  $$ = yyscan_push(YYSCAN_PARAM, $1, $2);
}
;
statement-list.opt
: %empty {
  $$ = YYSCAN_TOKEN(statement-list);
  $$ = yyscan_list(YYSCAN_PARAM, 1, $$);
}
| statement-list
;
statement-list
: statement {
  $$ = YYSCAN_TOKEN(statement-list);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| statement-list statement {
  $$ = yyscan_push(YYSCAN_PARAM, $1, $2);
}
;
expression-statement
: expression.opt semicolon {
  $$ = YYSCAN_TOKEN(expression-statement);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
;
selection-statement
: if left-paren expression right-paren statement %prec THEN {
  $$ = YYSCAN_TOKEN(selection-statement);
  $$ = yyscan_list(YYSCAN_PARAM, 6, $$, $1, $2, $3, $4, $5);
}
| if left-paren expression right-paren statement else statement {
  $$ = YYSCAN_TOKEN(selection-statement);
  $$ = yyscan_list(YYSCAN_PARAM, 8, $$, $1, $2, $3, $4, $5, $6, $7);
}
| switch left-paren expression right-paren statement {
  $$ = YYSCAN_TOKEN(selection-statement);
  $$ = yyscan_list(YYSCAN_PARAM, 6, $$, $1, $2, $3, $4, $5);
}
;
iteration-statement
: while left-paren expression right-paren statement {
  $$ = YYSCAN_TOKEN(iteration-statement);
  $$ = yyscan_list(YYSCAN_PARAM, 6, $$, $1, $2, $3, $4, $5);
}
| do statement while left-paren expression right-paren semicolon {
  $$ = YYSCAN_TOKEN(iteration-statement);
  $$ = yyscan_list(YYSCAN_PARAM, 8, $$, $1, $2, $3, $4, $5, $6, $7);
}
| for left-paren expression.opt semicolon expression.opt semicolon expression.opt right-paren statement {
  $$ = YYSCAN_TOKEN(iteration-statement);
  $$ = yyscan_list(YYSCAN_PARAM, 10, $$, $1, $2, $3, $4, $5, $6, $7, $8, $9);
}
;
jump-statement
: goto identifier semicolon {
  $$ = YYSCAN_TOKEN(jump-statement);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
| continue semicolon {
  $$ = YYSCAN_TOKEN(jump-statement);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
| break semicolon {
  $$ = YYSCAN_TOKEN(jump-statement);
  $$ = yyscan_list(YYSCAN_PARAM, 3, $$, $1, $2);
}
| return expression.opt semicolon {
  $$ = YYSCAN_TOKEN(jump-statement);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
;

/* 6.7 External definitions */
top
: translation-unit { yyscan_set_ast(YYSCAN_PARAM, $1); }
;
translation-unit
: external-declaration {
  $$ = YYSCAN_TOKEN(translation-unit);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
| translation-unit external-declaration {
  $$ = yyscan_push(YYSCAN_PARAM, $1, $2);
}
;
external-declaration
: function-definition
| declaration {
  $$ = YYSCAN_TOKEN(external-declaration);
  $$ = yyscan_list(YYSCAN_PARAM, 2, $$, $1);
}
;
function-definition
: declarator declaration-list.opt compound-statement {
  $$ = YYSCAN_TOKEN(function-definition);
  $$ = yyscan_list(YYSCAN_PARAM, 4, $$, $1, $2, $3);
}
| declaration-specifiers declarator declaration-list.opt compound-statement {
  $$ = YYSCAN_TOKEN(function-definition);
  $$ = yyscan_list(YYSCAN_PARAM, 5, $$, $1, $2, $3, $4);
}
;

%%
