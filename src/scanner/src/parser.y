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
: %empty { $$ = yyscan_nil(); }
| identifier
;
identifier
: TOKEN_IDENTIFIER {
  $$ = YYSCAN_TAG(identifier);
  $$ = YYSCAN_PUSH_SYMBOL($$);
}
;
typedef-identifier
: TOKEN_TYPEDEF_IDENTIFIER {
  $$ = YYSCAN_TAG(typedef-identifier);
  $$ = YYSCAN_PUSH_SYMBOL($$);
}
;
floating-constant
: TOKEN_FLOATING_CONSTANT {
  $$ = YYSCAN_TAG(floating-constant);
  $$ = YYSCAN_PUSH_SYMBOL($$);
}
;
integer-constant
: TOKEN_INTEGER_CONSTANT {
  $$ = YYSCAN_TAG(integer-constant);
  $$ = YYSCAN_PUSH_SYMBOL($$);
}
;
enumeration-constant
: TOKEN_IDENTIFIER {
  $$ = YYSCAN_TAG(enumeration-constant);
  $$ = YYSCAN_PUSH_SYMBOL($$);
}
;
character-constant
: TOKEN_CHARACTER_CONSTANT {
  $$ = YYSCAN_TAG(character-constant);
  $$ = YYSCAN_PUSH_SYMBOL($$);
}
;
string-literal
: TOKEN_STRING_LITERAL {
  $$ = YYSCAN_TAG(string-literal);
  $$ = YYSCAN_PUSH_SYMBOL($$);
}
;
string-constant
: string-literal {
  $$ = YYSCAN_TAG(string-constant);
  $$ = YYSCAN_PUSH($$, $1);
}
| string-constant string-literal {
  $$ = YYSCAN_PUSH($1, $2);
}
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
