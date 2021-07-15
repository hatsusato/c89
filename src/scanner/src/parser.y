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
  $$ = YYSCAN_TAG(identifier);
}
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

/* 6.3 Expressions */
primary-expression
: identifier {
  $$ = YYSCAN_TAG(primary-expression);
  $$ = YYSCAN_PUSH($$, $1);
}
| floating-constant {
  $$ = YYSCAN_TAG(primary-expression);
  $$ = YYSCAN_PUSH($$, $1);
}
| integer-constant {
  $$ = YYSCAN_TAG(primary-expression);
  $$ = YYSCAN_PUSH($$, $1);
}
| character-constant {
  $$ = YYSCAN_TAG(primary-expression);
  $$ = YYSCAN_PUSH($$, $1);
}
| string-literal {
  $$ = YYSCAN_TAG(primary-expression);
  $$ = YYSCAN_PUSH($$, $1);
}
| left-paren expression right-paren {
  $$ = YYSCAN_TAG(primary-expression);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
}
;
postfix-expression
: primary-expression
| postfix-expression left-bracket expression right-bracket {
  $$ = YYSCAN_TAG(postfix-expression);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
  $$ = YYSCAN_PUSH($$, $4);
}
| postfix-expression left-paren argument-expression-list.opt right-paren {
  $$ = YYSCAN_TAG(postfix-expression);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
  $$ = YYSCAN_PUSH($$, $4);
}
| postfix-expression period identifier {
  $$ = YYSCAN_TAG(postfix-expression);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
}
| postfix-expression arrow identifier {
  $$ = YYSCAN_TAG(postfix-expression);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
}
| postfix-expression increment {
  $$ = YYSCAN_TAG(postfix-expression);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
}
| postfix-expression decrement {
  $$ = YYSCAN_TAG(postfix-expression);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
}
;
argument-expression-list.opt
: %empty {
  $$ = YYSCAN_TAG(argument-expression-list);
}
| argument-expression-list
;
argument-expression-list
: assignment-expression {
  $$ = YYSCAN_TAG(argument-expression-list);
  $$ = YYSCAN_PUSH($$, $1);
}
| argument-expression-list comma assignment-expression {
  $$ = YYSCAN_PUSH($1, $3);
}
;
unary-expression
: postfix-expression
| increment unary-expression {
  $$ = YYSCAN_TAG(unary-expression);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
}
| decrement unary-expression {
  $$ = YYSCAN_TAG(unary-expression);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
}
| unary-operator cast-expression {
  $$ = YYSCAN_TAG(unary-expression);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
}
| sizeof unary-expression {
  $$ = YYSCAN_TAG(unary-expression);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
}
| sizeof left-paren type-name right-paren {
  $$ = YYSCAN_TAG(unary-expression);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
  $$ = YYSCAN_PUSH($$, $4);
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
  $$ = YYSCAN_TAG(cast-expression);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
  $$ = YYSCAN_PUSH($$, $4);
}
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
: declaration-specifiers init-declarator-list.opt semicolon {
  $$ = YYSCAN_TAG(declaration);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
}
;
declaration-specifiers
: declaration-specifier {
  $$ = YYSCAN_TAG(declaration-specifiers);
  $$ = YYSCAN_PUSH($$, $1);
}
| declaration-specifiers declaration-specifier {
  $$ = YYSCAN_PUSH($1, $2);
}
;
declaration-specifier
: storage-class-specifier
| type-specifier
| type-qualifier
;
init-declarator-list.opt
: %empty {
  $$ = YYSCAN_TAG(init-declarator-list);
}
| init-declarator-list
;
init-declarator-list
: init-declarator {
  $$ = YYSCAN_TAG(init-declarator-list);
  $$ = YYSCAN_PUSH($$, $1);
}
| init-declarator-list comma init-declarator {
  $$ = YYSCAN_PUSH($1, $3);
}
;
init-declarator
: declarator {
  $$ = YYSCAN_TAG(init-declarator);
  $$ = YYSCAN_PUSH($$, $1);
}
| declarator assign initializer {
  $$ = YYSCAN_TAG(init-declarator);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
}
;
storage-class-specifier
: typedef {
  $$ = YYSCAN_TAG(storage-class-specifier);
  $$ = YYSCAN_PUSH($$, $1);
}
| extern {
  $$ = YYSCAN_TAG(storage-class-specifier);
  $$ = YYSCAN_PUSH($$, $1);
}
| static {
  $$ = YYSCAN_TAG(storage-class-specifier);
  $$ = YYSCAN_PUSH($$, $1);
}
| auto {
  $$ = YYSCAN_TAG(storage-class-specifier);
  $$ = YYSCAN_PUSH($$, $1);
}
| register {
  $$ = YYSCAN_TAG(storage-class-specifier);
  $$ = YYSCAN_PUSH($$, $1);
}
;
type-specifier
: void {
  $$ = YYSCAN_TAG(type-specifier);
  $$ = YYSCAN_PUSH($$, $1);
}
| char {
  $$ = YYSCAN_TAG(type-specifier);
  $$ = YYSCAN_PUSH($$, $1);
}
| short {
  $$ = YYSCAN_TAG(type-specifier);
  $$ = YYSCAN_PUSH($$, $1);
}
| int {
  $$ = YYSCAN_TAG(type-specifier);
  $$ = YYSCAN_PUSH($$, $1);
}
| long {
  $$ = YYSCAN_TAG(type-specifier);
  $$ = YYSCAN_PUSH($$, $1);
}
| float {
  $$ = YYSCAN_TAG(type-specifier);
  $$ = YYSCAN_PUSH($$, $1);
}
| double {
  $$ = YYSCAN_TAG(type-specifier);
  $$ = YYSCAN_PUSH($$, $1);
}
| signed {
  $$ = YYSCAN_TAG(type-specifier);
  $$ = YYSCAN_PUSH($$, $1);
}
| unsigned {
  $$ = YYSCAN_TAG(type-specifier);
  $$ = YYSCAN_PUSH($$, $1);
}
| struct-or-union-specifier {
  $$ = YYSCAN_TAG(type-specifier);
  $$ = YYSCAN_PUSH($$, $1);
}
| enum-specifier {
  $$ = YYSCAN_TAG(type-specifier);
  $$ = YYSCAN_PUSH($$, $1);
}
| typedef-name {
  $$ = YYSCAN_TAG(type-specifier);
  $$ = YYSCAN_PUSH($$, $1);
}
;
struct-or-union-specifier
: struct-or-union identifier.opt left-brace struct-declaration-list right-brace {
  $$ = YYSCAN_TAG(struct-or-union-specifier);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
  $$ = YYSCAN_PUSH($$, $4);
  $$ = YYSCAN_PUSH($$, $5);
}
| struct-or-union identifier {
  $$ = YYSCAN_TAG(struct-or-union-specifier);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
}
;
struct-or-union
: struct {
  $$ = YYSCAN_TAG(struct-or-union);
  $$ = YYSCAN_PUSH($$, $1);
}
| union {
  $$ = YYSCAN_TAG(struct-or-union);
  $$ = YYSCAN_PUSH($$, $1);
}
;
struct-declaration-list
: struct-declaration {
  $$ = YYSCAN_TAG(struct-declaration-list);
  $$ = YYSCAN_PUSH($$, $1);
}
| struct-declaration-list struct-declaration {
  $$ = YYSCAN_PUSH($1, $2);
}
;
struct-declaration
: specifier-qualifier-list struct-declarator-list semicolon {
  $$ = YYSCAN_TAG(struct-declaration);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
}
;
specifier-qualifier-list
: specifier-qualifier {
  $$ = YYSCAN_TAG(specifier-qualifier-list);
  $$ = YYSCAN_PUSH($$, $1);
}
| specifier-qualifier-list specifier-qualifier {
  $$ = YYSCAN_PUSH($1, $2);
}
;
specifier-qualifier
: type-specifier
| type-qualifier
;
struct-declarator-list
: struct-declarator {
  $$ = YYSCAN_TAG(struct-declarator-list);
  $$ = YYSCAN_PUSH($$, $1);
}
| struct-declarator-list comma struct-declarator {
  $$ = YYSCAN_PUSH($1, $3);
}
;
struct-declarator
: declarator {
  $$ = YYSCAN_TAG(struct-declarator);
  $$ = YYSCAN_PUSH($$, $1);
}
| declarator.opt colon constant-expression {
  $$ = YYSCAN_TAG(struct-declarator);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
}
;
enum-specifier
: enum identifier.opt left-brace enumerator-list right-brace {
  $$ = YYSCAN_TAG(enum-specifier);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
  $$ = YYSCAN_PUSH($$, $4);
  $$ = YYSCAN_PUSH($$, $5);
}
| enum identifier {
  $$ = YYSCAN_TAG(enum-specifier);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
}
;
enumerator-list
: enumerator {
  $$ = YYSCAN_TAG(enumerator-list);
  $$ = YYSCAN_PUSH($$, $1);
}
| enumerator-list comma enumerator {
  $$ = YYSCAN_PUSH($1, $3);
}
;
enumerator
: enumeration-constant {
  $$ = YYSCAN_TAG(enumerator);
  $$ = YYSCAN_PUSH($$, $1);
}
| enumeration-constant assign constant-expression {
  $$ = YYSCAN_TAG(enumerator);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
}
;
type-qualifier
: const {
  $$ = YYSCAN_TAG(type-qualifier);
  $$ = YYSCAN_PUSH($$, $1);
}
| volatile {
  $$ = YYSCAN_TAG(type-qualifier);
  $$ = YYSCAN_PUSH($$, $1);
}
;
declarator.opt
: %empty {
  $$ = YYSCAN_TAG(declarator);
}
| declarator
;
declarator
: direct-declarator {
  $$ = YYSCAN_TAG(declarator);
  $$ = YYSCAN_PUSH($$, $1);
}
| pointer direct-declarator {
  $$ = YYSCAN_TAG(declarator);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
}
;
direct-declarator
: identifier {
  $$ = YYSCAN_TAG(direct-declarator);
  $$ = YYSCAN_PUSH($$, $1);
}
| left-paren declarator right-paren {
  $$ = YYSCAN_TAG(direct-declarator);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
}
| direct-declarator left-bracket constant-expression.opt right-bracket {
  $$ = YYSCAN_TAG(direct-declarator);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
  $$ = YYSCAN_PUSH($$, $4);
}
| direct-declarator left-paren parameter-type-list right-paren {
  $$ = YYSCAN_TAG(direct-declarator);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
  $$ = YYSCAN_PUSH($$, $4);
}
| direct-declarator left-paren identifier-list.opt right-paren {
  $$ = YYSCAN_TAG(direct-declarator);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
  $$ = YYSCAN_PUSH($$, $4);
}
;
pointer
: asterisk type-qualifier-list.opt {
  $$ = YYSCAN_TAG(pointer);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
}
| pointer asterisk type-qualifier-list.opt {
  $$ = YYSCAN_TAG(pointer);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
}
;
type-qualifier-list.opt
: %empty {
  $$ = YYSCAN_TAG(type-qualifier-list);
}
| type-qualifier-list
;
type-qualifier-list
: type-qualifier {
  $$ = YYSCAN_TAG(type-qualifier-list);
  $$ = YYSCAN_PUSH($$, $1);
}
| type-qualifier-list type-qualifier {
  $$ = YYSCAN_PUSH($1, $2);
}
;
parameter-type-list.opt
: %empty {
  $$ = YYSCAN_TAG(parameter-type-list);
}
| parameter-type-list
;
parameter-type-list
: parameter-list {
  $$ = YYSCAN_TAG(parameter-type-list);
  $$ = YYSCAN_PUSH($$, $1);
}
| parameter-list comma ellipsis {
  $$ = YYSCAN_TAG(parameter-type-list);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $3);
}
;
parameter-list
: parameter-declaration {
  $$ = YYSCAN_TAG(parameter-list);
  $$ = YYSCAN_PUSH($$, $1);
}
| parameter-list comma parameter-declaration {
  $$ = YYSCAN_PUSH($1, $3);
}
;
parameter-declaration
: declaration-specifiers declarator {
  $$ = YYSCAN_TAG(parameter-declaration);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
}
| declaration-specifiers abstract-declarator.opt {
  $$ = YYSCAN_TAG(parameter-declaration);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
}
;
identifier-list.opt
: %empty {
  $$ = YYSCAN_TAG(identifier-list);
}
| identifier-list
;
identifier-list
: identifier {
  $$ = YYSCAN_TAG(identifier-list);
  $$ = YYSCAN_PUSH($$, $1);
}
| identifier-list comma identifier {
  $$ = YYSCAN_PUSH($1, $3);
}
;
type-name
: specifier-qualifier-list abstract-declarator.opt {
  $$ = YYSCAN_TAG(type-name);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
}
;
abstract-declarator.opt
: %empty {
  $$ = YYSCAN_TAG(abstract-declarator);
}
| abstract-declarator
;
abstract-declarator
: pointer {
  $$ = YYSCAN_TAG(abstract-declarator);
  $$ = YYSCAN_PUSH($$, $1);
}
| direct-abstract-declarator {
  $$ = YYSCAN_TAG(abstract-declarator);
  $$ = YYSCAN_PUSH($$, $1);
}
| pointer direct-abstract-declarator {
  $$ = YYSCAN_TAG(abstract-declarator);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
}
;
direct-abstract-declarator
: left-paren abstract-declarator right-paren {
  $$ = YYSCAN_TAG(direct-abstract-declarator);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
}
| left-bracket constant-expression.opt right-bracket {
  $$ = YYSCAN_TAG(direct-abstract-declarator);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
}
| direct-abstract-declarator left-bracket constant-expression.opt right-bracket {
  $$ = YYSCAN_TAG(direct-abstract-declarator);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
  $$ = YYSCAN_PUSH($$, $4);
}
| left-paren parameter-type-list.opt right-paren {
  $$ = YYSCAN_TAG(direct-abstract-declarator);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
}
| direct-abstract-declarator left-paren parameter-type-list.opt right-paren {
  $$ = YYSCAN_TAG(direct-abstract-declarator);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
  $$ = YYSCAN_PUSH($$, $4);
}
;
typedef-name
: typedef-identifier {
  $$ = YYSCAN_TAG(typedef-name);
  $$ = YYSCAN_PUSH($$, $1);
}
;
initializer
: assignment-expression {
  $$ = YYSCAN_TAG(initializer);
  $$ = YYSCAN_PUSH($$, $1);
}
| left-brace initializer-list right-brace {
  $$ = YYSCAN_TAG(initializer);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
}
| left-brace initializer-list comma right-brace {
  $$ = YYSCAN_TAG(initializer);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $4);
}
;
initializer-list
: initializer {
  $$ = YYSCAN_TAG(initializer-list);
  $$ = YYSCAN_PUSH($$, $1);
}
| initializer-list comma initializer {
  $$ = YYSCAN_PUSH($1, $3);
}
;

/* 6.6 Statements */
statement
: labeled-statement {
  $$ = YYSCAN_TAG(statement);
  $$ = YYSCAN_PUSH($$, $1);
}
| compound-statement {
  $$ = YYSCAN_TAG(statement);
  $$ = YYSCAN_PUSH($$, $1);
}
| expression-statement {
  $$ = YYSCAN_TAG(statement);
  $$ = YYSCAN_PUSH($$, $1);
}
| selection-statement {
  $$ = YYSCAN_TAG(statement);
  $$ = YYSCAN_PUSH($$, $1);
}
| iteration-statement {
  $$ = YYSCAN_TAG(statement);
  $$ = YYSCAN_PUSH($$, $1);
}
| jump-statement {
  $$ = YYSCAN_TAG(statement);
  $$ = YYSCAN_PUSH($$, $1);
}
;
labeled-statement
: identifier colon statement {
  $$ = YYSCAN_TAG(labeled-statement);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
}
| case constant-expression colon statement {
  $$ = YYSCAN_TAG(labeled-statement);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
  $$ = YYSCAN_PUSH($$, $4);
}
| default colon statement {
  $$ = YYSCAN_TAG(labeled-statement);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
}
;
compound-statement
: left-brace declaration-list.opt statement-list.opt right-brace {
  $$ = YYSCAN_TAG(compound-statement);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
  $$ = YYSCAN_PUSH($$, $4);
}
;
declaration-list.opt
: %empty {
  $$ = YYSCAN_TAG(declaration-list);
}
| declaration-list
;
declaration-list
: declaration {
  $$ = YYSCAN_TAG(declaration-list);
  $$ = YYSCAN_PUSH($$, $1);
}
| declaration-list declaration {
  $$ = YYSCAN_PUSH($1, $2);
}
;
statement-list.opt
: %empty {
  $$ = YYSCAN_TAG(statement-list);
}
| statement-list
;
statement-list
: statement {
  $$ = YYSCAN_TAG(statement-list);
  $$ = YYSCAN_PUSH($$, $1);
}
| statement-list statement {
  $$ = YYSCAN_PUSH($1, $2);
}
;
expression-statement
: expression.opt semicolon {
  $$ = YYSCAN_TAG(expression-statement);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
}
;
selection-statement
: if left-paren expression right-paren statement %prec THEN {
  $$ = YYSCAN_TAG(selection-statement);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
  $$ = YYSCAN_PUSH($$, $4);
  $$ = YYSCAN_PUSH($$, $5);
}
| if left-paren expression right-paren statement else statement {
  $$ = YYSCAN_TAG(selection-statement);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
  $$ = YYSCAN_PUSH($$, $4);
  $$ = YYSCAN_PUSH($$, $5);
  $$ = YYSCAN_PUSH($$, $6);
  $$ = YYSCAN_PUSH($$, $7);
}
| switch left-paren expression right-paren statement {
  $$ = YYSCAN_TAG(selection-statement);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
  $$ = YYSCAN_PUSH($$, $4);
  $$ = YYSCAN_PUSH($$, $5);
}
;
iteration-statement
: while left-paren expression right-paren statement {
  $$ = YYSCAN_TAG(iteration-statement);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
  $$ = YYSCAN_PUSH($$, $4);
  $$ = YYSCAN_PUSH($$, $5);
}
| do statement while left-paren expression right-paren semicolon {
  $$ = YYSCAN_TAG(iteration-statement);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
  $$ = YYSCAN_PUSH($$, $4);
  $$ = YYSCAN_PUSH($$, $5);
  $$ = YYSCAN_PUSH($$, $6);
  $$ = YYSCAN_PUSH($$, $7);
}
| for left-paren expression.opt semicolon expression.opt semicolon expression.opt right-paren statement {
  $$ = YYSCAN_TAG(iteration-statement);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
  $$ = YYSCAN_PUSH($$, $4);
  $$ = YYSCAN_PUSH($$, $5);
  $$ = YYSCAN_PUSH($$, $6);
  $$ = YYSCAN_PUSH($$, $7);
  $$ = YYSCAN_PUSH($$, $8);
  $$ = YYSCAN_PUSH($$, $9);
}
;
jump-statement
: goto identifier semicolon {
  $$ = YYSCAN_TAG(jump-statement);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
}
| continue semicolon {
  $$ = YYSCAN_TAG(jump-statement);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
}
| break semicolon {
  $$ = YYSCAN_TAG(jump-statement);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
}
| return expression.opt semicolon {
  $$ = YYSCAN_TAG(jump-statement);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
}
;

/* 6.7 External definitions */
top
: translation-unit { yyscan_set_ast(YYSCAN_PARAM, $1); }
;
translation-unit
: external-declaration {
  $$ = YYSCAN_TAG(translation-unit);
  $$ = YYSCAN_PUSH($$, $1);
}
| translation-unit external-declaration {
  $$ = YYSCAN_PUSH($1, $2);
}
;
external-declaration
: function-definition
| declaration {
  $$ = YYSCAN_TAG(external-declaration);
  $$ = YYSCAN_PUSH($$, $1);
}
;
function-definition
: declarator declaration-list.opt compound-statement {
  $$ = YYSCAN_TAG(function-definition);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
}
| declaration-specifiers declarator declaration-list.opt compound-statement {
  $$ = YYSCAN_TAG(function-definition);
  $$ = YYSCAN_PUSH($$, $1);
  $$ = YYSCAN_PUSH($$, $2);
  $$ = YYSCAN_PUSH($$, $3);
  $$ = YYSCAN_PUSH($$, $4);
}
;

%%
