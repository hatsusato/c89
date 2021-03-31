%code requires {
#include "yyscan_t.h"
#include "sexp/opaque.h"
}

%define api.pure full
%define api.value.type {Sexp *}
%param {yyscan_t yyscanner}

%code provides {
#include "ast/tag.h"
#include "lexer.h"
#include "yyscan.h"
#include "sexp/sexp.h"
}

/* 6.1 Lexical elements */
/* 6.1.1 Keywords */
%token TOKEN_AUTO "auto"
%token TOKEN_BREAK "break"
%token TOKEN_CASE "case"
%token TOKEN_CHAR "char"
%token TOKEN_CONST "const"
%token TOKEN_CONTINUE "continue"
%token TOKEN_DEFAULT "default"
%token TOKEN_DO "do"
%token TOKEN_DOUBLE "double"
%token TOKEN_ELSE "else"
%token TOKEN_ENUM "enum"
%token TOKEN_EXTERN "extern"
%token TOKEN_FLOAT "float"
%token TOKEN_FOR "for"
%token TOKEN_GOTO "goto"
%token TOKEN_IF "if"
%token TOKEN_INT "int"
%token TOKEN_LONG "long"
%token TOKEN_REGISTER "register"
%token TOKEN_RETURN "return"
%token TOKEN_SHORT "short"
%token TOKEN_SIGNED "signed"
%token TOKEN_SIZEOF "sizeof"
%token TOKEN_STATIC "static"
%token TOKEN_STRUCT "struct"
%token TOKEN_SWITCH "switch"
%token TOKEN_TYPEDEF "typedef"
%token TOKEN_UNION "union"
%token TOKEN_UNSIGNED "unsigned"
%token TOKEN_VOID "void"
%token TOKEN_VOLATILE "volatile"
%token TOKEN_WHILE "while"
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
%token TOKEN_PERIOD "."
%token TOKEN_ARROW "->"
%token TOKEN_INCREMENT "++"
%token TOKEN_DECREMENT "--"
%token TOKEN_AMPERSAND "&"
%token TOKEN_ASTERISK "*"
%token TOKEN_PLUS "+"
%token TOKEN_MINUS "-"
%token TOKEN_TILDE "~"
%token TOKEN_EXCLAMATION "!"
%token TOKEN_SLASH "/"
%token TOKEN_PERCENT "%"
%token TOKEN_LEFT_SHIFT "<<"
%token TOKEN_RIGHT_SHIFT ">>"
%token TOKEN_LESS_THAN "<"
%token TOKEN_GREATER_THAN ">"
%token TOKEN_LESS_EQUAL "<="
%token TOKEN_GREATER_EQUAL ">="
%token TOKEN_EQUAL "=="
%token TOKEN_NOT_EQUAL "!="
%token TOKEN_CARET "^"
%token TOKEN_BAR "|"
%token TOKEN_AND "&&"
%token TOKEN_OR "||"
%token TOKEN_QUESTION "?"
%token TOKEN_ASSIGN "="
%token TOKEN_ASTERISK_ASSIGN "*="
%token TOKEN_SLASH_ASSIGN "/="
%token TOKEN_PERCENT_ASSIGN "%="
%token TOKEN_PLUS_ASSIGN "+="
%token TOKEN_MINUS_ASSIGN "-="
%token TOKEN_LEFT_SHIFT_ASSIGN "<<="
%token TOKEN_RIGHT_SHIFT_ASSIGN ">>="
%token TOKEN_AMPERSAND_ASSIGN "&="
%token TOKEN_CARET_ASSIGN "^="
%token TOKEN_BAR_ASSIGN "|="
/* 6.1.6 Punctuators */
%token TOKEN_LEFT_BRACKET "["
%token TOKEN_RIGHT_BRACKET "]"
%token TOKEN_LEFT_PAREN "("
%token TOKEN_RIGHT_PAREN ")"
%token TOKEN_LEFT_BRACE "{"
%token TOKEN_RIGHT_BRACE "}"
%token TOKEN_COMMA ","
%token TOKEN_COLON ":"
%token TOKEN_SEMICOLON ";"
%token TOKEN_ELLIPSIS "..."

%nonassoc THEN
%nonassoc "else"

%start top
%%
auto: "auto" {
  $$ = YYSCAN_SYMBOL(AST_AUTO);
}
;
break: "break" {
  $$ = YYSCAN_SYMBOL(AST_BREAK);
}
;
case: "case" {
  $$ = YYSCAN_SYMBOL(AST_CASE);
}
;
char: "char" {
  $$ = YYSCAN_SYMBOL(AST_CHAR);
}
;
const: "const" {
  $$ = YYSCAN_SYMBOL(AST_CONST);
}
;
continue: "continue" {
  $$ = YYSCAN_SYMBOL(AST_CONTINUE);
}
;
default: "default" {
  $$ = YYSCAN_SYMBOL(AST_DEFAULT);
}
;
do: "do" {
  $$ = YYSCAN_SYMBOL(AST_DO);
}
;
double: "double" {
  $$ = YYSCAN_SYMBOL(AST_DOUBLE);
}
;
else: "else" {
  $$ = YYSCAN_SYMBOL(AST_ELSE);
}
;
enum: "enum" {
  $$ = YYSCAN_SYMBOL(AST_ENUM);
}
;
extern: "extern" {
  $$ = YYSCAN_SYMBOL(AST_EXTERN);
}
;
float: "float" {
  $$ = YYSCAN_SYMBOL(AST_FLOAT);
}
;
for: "for" {
  $$ = YYSCAN_SYMBOL(AST_FOR);
}
;
goto: "goto" {
  $$ = YYSCAN_SYMBOL(AST_GOTO);
}
;
if: "if" {
  $$ = YYSCAN_SYMBOL(AST_IF);
}
;
int: "int" {
  $$ = YYSCAN_SYMBOL(AST_INT);
}
;
long: "long" {
  $$ = YYSCAN_SYMBOL(AST_LONG);
}
;
register: "register" {
  $$ = YYSCAN_SYMBOL(AST_REGISTER);
}
;
return: "return" {
  $$ = YYSCAN_SYMBOL(AST_RETURN);
}
;
short: "short" {
  $$ = YYSCAN_SYMBOL(AST_SHORT);
}
;
signed: "signed" {
  $$ = YYSCAN_SYMBOL(AST_SIGNED);
}
;
sizeof: "sizeof" {
  $$ = YYSCAN_SYMBOL(AST_SIZEOF);
}
;
static: "static" {
  $$ = YYSCAN_SYMBOL(AST_STATIC);
}
;
struct: "struct" {
  $$ = YYSCAN_SYMBOL(AST_STRUCT);
}
;
switch: "switch" {
  $$ = YYSCAN_SYMBOL(AST_SWITCH);
}
;
typedef: "typedef" {
  $$ = YYSCAN_SYMBOL(AST_TYPEDEF);
}
;
union: "union" {
  $$ = YYSCAN_SYMBOL(AST_UNION);
}
;
unsigned: "unsigned" {
  $$ = YYSCAN_SYMBOL(AST_UNSIGNED);
}
;
void: "void" {
  $$ = YYSCAN_SYMBOL(AST_VOID);
}
;
volatile: "volatile" {
  $$ = YYSCAN_SYMBOL(AST_VOLATILE);
}
;
while: "while" {
  $$ = YYSCAN_SYMBOL(AST_WHILE);
}
;

period: "." {
  $$ = YYSCAN_SYMBOL(AST_PERIOD);
}
;
arrow: "->" {
  $$ = YYSCAN_SYMBOL(AST_ARROW);
}
;
increment: "++" {
  $$ = YYSCAN_SYMBOL(AST_INCREMENT);
}
;
decrement: "--" {
  $$ = YYSCAN_SYMBOL(AST_DECREMENT);
}
;
ampersand: "&" {
  $$ = YYSCAN_SYMBOL(AST_AMPERSAND);
}
;
asterisk: "*" {
  $$ = YYSCAN_SYMBOL(AST_ASTERISK);
}
;
plus: "+" {
  $$ = YYSCAN_SYMBOL(AST_PLUS);
}
;
minus: "-" {
  $$ = YYSCAN_SYMBOL(AST_MINUS);
}
;
tilde: "~" {
  $$ = YYSCAN_SYMBOL(AST_TILDE);
}
;
exclamation: "!" {
  $$ = YYSCAN_SYMBOL(AST_EXCLAMATION);
}
;
slash: "/" {
  $$ = YYSCAN_SYMBOL(AST_SLASH);
}
;
percent: "%" {
  $$ = YYSCAN_SYMBOL(AST_PERCENT);
}
;
left-shift: "<<" {
  $$ = YYSCAN_SYMBOL(AST_LEFT_SHIFT);
}
;
right-shift: ">>" {
  $$ = YYSCAN_SYMBOL(AST_RIGHT_SHIFT);
}
;
less-than: "<" {
  $$ = YYSCAN_SYMBOL(AST_LESS_THAN);
}
;
greater-than: ">" {
  $$ = YYSCAN_SYMBOL(AST_GREATER_THAN);
}
;
less-equal: "<=" {
  $$ = YYSCAN_SYMBOL(AST_LESS_EQUAL);
}
;
greater-equal: ">=" {
  $$ = YYSCAN_SYMBOL(AST_GREATER_EQUAL);
}
;
equal: "==" {
  $$ = YYSCAN_SYMBOL(AST_EQUAL);
}
;
not-equal: "!=" {
  $$ = YYSCAN_SYMBOL(AST_NOT_EQUAL);
}
;
caret: "^" {
  $$ = YYSCAN_SYMBOL(AST_CARET);
}
;
bar: "|" {
  $$ = YYSCAN_SYMBOL(AST_BAR);
}
;
and: "&&" {
  $$ = YYSCAN_SYMBOL(AST_AND);
}
;
or: "||" {
  $$ = YYSCAN_SYMBOL(AST_OR);
}
;
question: "?" {
  $$ = YYSCAN_SYMBOL(AST_QUESTION);
}
;
assign: "=" {
  $$ = YYSCAN_SYMBOL(AST_ASSIGN);
}
;
asterisk-assign: "*=" {
  $$ = YYSCAN_SYMBOL(AST_ASTERISK_ASSIGN);
}
;
slash-assign: "/=" {
  $$ = YYSCAN_SYMBOL(AST_SLASH_ASSIGN);
}
;
percent-assign: "%=" {
  $$ = YYSCAN_SYMBOL(AST_PERCENT_ASSIGN);
}
;
plus-assign: "+=" {
  $$ = YYSCAN_SYMBOL(AST_PLUS_ASSIGN);
}
;
minus-assign: "-=" {
  $$ = YYSCAN_SYMBOL(AST_MINUS_ASSIGN);
}
;
left-shift-assign: "<<=" {
  $$ = YYSCAN_SYMBOL(AST_LEFT_SHIFT_ASSIGN);
}
;
right-shift-assign: ">>=" {
  $$ = YYSCAN_SYMBOL(AST_RIGHT_SHIFT_ASSIGN);
}
;
ampersand-assign: "&=" {
  $$ = YYSCAN_SYMBOL(AST_AMPERSAND_ASSIGN);
}
;
caret-assign: "^=" {
  $$ = YYSCAN_SYMBOL(AST_CARET_ASSIGN);
}
;
bar-assign: "|=" {
  $$ = YYSCAN_SYMBOL(AST_BAR_ASSIGN);
}
;

left-bracket: "[" {
  $$ = YYSCAN_SYMBOL(AST_LEFT_BRACKET);
}
;
right-bracket: "]" {
  $$ = YYSCAN_SYMBOL(AST_RIGHT_BRACKET);
}
;
left-paren: "(" {
  $$ = YYSCAN_SYMBOL(AST_LEFT_PAREN);
}
;
right-paren: ")" {
  $$ = YYSCAN_SYMBOL(AST_RIGHT_PAREN);
}
;
left-brace: "{" {
  $$ = YYSCAN_SYMBOL(AST_LEFT_BRACE);
}
;
right-brace: "}" {
  $$ = YYSCAN_SYMBOL(AST_RIGHT_BRACE);
}
;
comma: "," {
  $$ = YYSCAN_SYMBOL(AST_COMMA);
}
;
colon: ":" {
  $$ = YYSCAN_SYMBOL(AST_COLON);
}
;
semicolon: ";" {
  $$ = YYSCAN_SYMBOL(AST_SEMICOLON);
}
;
ellipsis: "..." {
  $$ = YYSCAN_SYMBOL(AST_ELLIPSIS);
}
;

/* 6.1 Lexical elements */
identifier.opt
: %empty {
  $$ = YYSCAN_NIL();
}
| identifier
;
identifier
: identifier.tag {
  $$ = YYSCAN_TAG(AST_IDENTIFIER);
  $$ = YYSCAN_SNOC($$, $1);
}
;
identifier.tag
: TOKEN_IDENTIFIER {
  $$ = YYSCAN_TOKEN();
}
;
typedef-identifier
: typedef-identifier.tag {
  $$ = YYSCAN_TAG(AST_TYPEDEF_IDENTIFIER);
  $$ = YYSCAN_SNOC($$, $1);
}
;
typedef-identifier.tag
: TOKEN_TYPEDEF_IDENTIFIER {
  $$ = YYSCAN_TOKEN();
}
;
floating-constant
: floating-constant.tag {
  $$ = YYSCAN_TAG(AST_FLOATING_CONSTANT);
  $$ = YYSCAN_SNOC($$, $1);
}
;
floating-constant.tag
: TOKEN_FLOATING_CONSTANT {
  $$ = YYSCAN_TOKEN();
}
;
integer-constant
: integer-constant.tag {
  $$ = YYSCAN_TAG(AST_INTEGER_CONSTANT);
  $$ = YYSCAN_SNOC($$, $1);
}
;
integer-constant.tag
: TOKEN_INTEGER_CONSTANT {
  $$ = YYSCAN_TOKEN();
}
;
enumeration-constant
: enumeration-constant.tag {
  $$ = YYSCAN_TAG(AST_ENUMERATION_CONSTANT);
  $$ = YYSCAN_SNOC($$, $1);
}
;
enumeration-constant.tag
: TOKEN_IDENTIFIER {
  $$ = YYSCAN_TOKEN();
}
;
character-constant
: character-constant.tag {
  $$ = YYSCAN_TAG(AST_CHARACTER_CONSTANT);
  $$ = YYSCAN_SNOC($$, $1);
}
;
character-constant.tag
: TOKEN_CHARACTER_CONSTANT {
  $$ = YYSCAN_TOKEN();
}
;
string-literal
: TOKEN_STRING_LITERAL {
  $$ = YYSCAN_TOKEN();
}
;
string-constant
: string-literal {
  $$ = YYSCAN_TAG(AST_STRING_LITERAL);
  $$ = YYSCAN_SNOC($$, $1);
}
| string-constant string-literal {
  $$ = YYSCAN_SNOC($1, $2);
}
;

/* 6.3 Expressions */
primary-expression
: identifier
| floating-constant
| integer-constant
| character-constant
| string-constant
| left-paren expression right-paren {
  $$ = YYSCAN_TAG(AST_PRIMARY_EXPRESSION);
  $$ = YYSCAN_SNOC($$, $1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
;
postfix-expression
: primary-expression
| postfix-expression.tag {
  $$ = YYSCAN_TAG(AST_POSTFIX_EXPRESSION);
  $$ = YYSCAN_APPEND($$, $1);
}
;
postfix-expression.tag
: postfix-expression postfix-expression.suffix {
  $$ = YYSCAN_CONS($1, $2);
}
;
postfix-expression.suffix
: left-bracket expression right-bracket {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
| left-paren argument-expression-list.opt right-paren {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
| period identifier {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
}
| arrow identifier {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
}
| increment {
  $$ = YYSCAN_LIST($1);
}
| decrement {
  $$ = YYSCAN_LIST($1);
}
;
argument-expression-list.opt
: %empty {
  $$ = YYSCAN_TAG(AST_ARGUMENT_EXPRESSION_LIST);
}
| argument-expression-list
;
argument-expression-list
: assignment-expression {
  $$ = YYSCAN_TAG(AST_ARGUMENT_EXPRESSION_LIST);
  $$ = YYSCAN_SNOC($$, $1);
}
| argument-expression-list "," assignment-expression {
  $$ = YYSCAN_SNOC($1, $3);
}
;
unary-expression
: postfix-expression
| unary-expression.tag {
  $$ = YYSCAN_TAG(AST_UNARY_EXPRESSION);
  $$ = YYSCAN_APPEND($$, $1);
}
;
unary-expression.tag
: increment unary-expression {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
}
| decrement unary-expression {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
}
| unary-operator cast-expression {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
}
| sizeof unary-expression {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
}
| sizeof left-paren type-name right-paren {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
  $$ = YYSCAN_SNOC($$, $4);
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
| cast-expression.tag {
  $$ = YYSCAN_TAG(AST_CAST_EXPRESSION);
  $$ = YYSCAN_APPEND($$, $1);
}
;
cast-expression.tag
: left-paren type-name right-paren cast-expression {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
  $$ = YYSCAN_SNOC($$, $4);
}
;
multiplicative-expression
: cast-expression
| multiplicative-expression.tag {
  $$ = YYSCAN_TAG(AST_MULTIPLICATIVE_EXPRESSION);
  $$ = YYSCAN_APPEND($$, $1);
}
;
multiplicative-expression.tag
: multiplicative-expression multiplicative-operator cast-expression {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
;
multiplicative-operator
: asterisk
| slash
| percent
;
additive-expression
: multiplicative-expression
| additive-expression.tag {
  $$ = YYSCAN_TAG(AST_ADDITIVE_EXPRESSION);
  $$ = YYSCAN_APPEND($$, $1);
}
;
additive-expression.tag
: additive-expression additive-operator multiplicative-expression {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
;
additive-operator
: plus
| minus
;
shift-expression
: additive-expression
| shift-expression.tag {
  $$ = YYSCAN_TAG(AST_SHIFT_EXPRESSION);
  $$ = YYSCAN_APPEND($$, $1);
}
;
shift-expression.tag
: shift-expression shift-operator additive-expression {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
;
shift-operator
: left-shift
| right-shift
;
relational-expression
: shift-expression
| relational-expression.tag {
  $$ = YYSCAN_TAG(AST_RELATIONAL_EXPRESSION);
  $$ = YYSCAN_APPEND($$, $1);
}
;
relational-expression.tag
: relational-expression relational-operator shift-expression {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
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
| equality-expression.tag {
  $$ = YYSCAN_TAG(AST_EQUALITY_EXPRESSION);
  $$ = YYSCAN_APPEND($$, $1);
}
;
equality-expression.tag
: equality-expression equality-operator relational-expression {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
;
equality-operator
: equal
| not-equal
;
and-expression
: equality-expression
| and-expression.tag {
  $$ = YYSCAN_TAG(AST_AND_EXPRESSION);
  $$ = YYSCAN_APPEND($$, $1);
}
;
and-expression.tag
: and-expression ampersand equality-expression {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
;
exclusive-or-expression
: and-expression
| exclusive-or-expression.tag {
  $$ = YYSCAN_TAG(AST_EXCLUSIVE_OR_EXPRESSION);
  $$ = YYSCAN_APPEND($$, $1);
}
;
exclusive-or-expression.tag
: exclusive-or-expression caret and-expression {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
;
inclusive-or-expression
: exclusive-or-expression
| inclusive-or-expression.tag {
  $$ = YYSCAN_TAG(AST_INCLUSIVE_OR_EXPRESSION);
  $$ = YYSCAN_APPEND($$, $1);
}
;
inclusive-or-expression.tag
: inclusive-or-expression bar exclusive-or-expression {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
;
logical-and-expression
: inclusive-or-expression
| logical-and-expression.tag {
  $$ = YYSCAN_TAG(AST_LOGICAL_AND_EXPRESSION);
  $$ = YYSCAN_APPEND($$, $1);
}
;
logical-and-expression.tag
: logical-and-expression and inclusive-or-expression {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
;
logical-or-expression
: logical-and-expression
| logical-or-expression.tag {
  $$ = YYSCAN_TAG(AST_LOGICAL_OR_EXPRESSION);
  $$ = YYSCAN_APPEND($$, $1);
}
;
logical-or-expression.tag
: logical-or-expression or logical-and-expression {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
;
conditional-expression
: logical-or-expression
| conditional-expression.tag {
  $$ = YYSCAN_TAG(AST_CONDITIONAL_EXPRESSION);
  $$ = YYSCAN_APPEND($$, $1);
}
;
conditional-expression.tag
: logical-or-expression question expression colon conditional-expression {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
  $$ = YYSCAN_SNOC($$, $4);
  $$ = YYSCAN_SNOC($$, $5);
}
;
assignment-expression
: conditional-expression
| assignment-expression.tag {
  $$ = YYSCAN_TAG(AST_ASSIGNMENT_EXPRESSION);
  $$ = YYSCAN_APPEND($$, $1);
}
;
assignment-expression.tag
: unary-expression assignment-operator assignment-expression {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
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
  $$ = YYSCAN_NIL();
}
| expression
;
expression
: assignment-expression
| expression.tag {
  $$ = YYSCAN_TAG(AST_EXPRESSION);
  $$ = YYSCAN_APPEND($$, $1);
}
;
expression.tag
: expression "," assignment-expression {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $3);
}
;

/* 6.4 Constant expressions */
constant-expression.opt
: %empty {
  $$ = YYSCAN_NIL();
}
| constant-expression
;
constant-expression
: conditional-expression {
  $$ = YYSCAN_TAG(AST_CONSTANT_EXPRESSION);
  $$ = YYSCAN_SNOC($$, $1);
}
;

/* 6.5 Declarations */
declaration
: declaration.tag {
  $$ = YYSCAN_TAG(AST_DECLARATION);
  $$ = YYSCAN_APPEND($$, $1);
}
;
declaration.tag
: declaration-specifiers init-declarator-list.opt semicolon {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
;
declaration-specifiers
: declaration-specifier {
  $$ = YYSCAN_TAG(AST_DECLARATION_SPECIFIERS);
  $$ = YYSCAN_SNOC($$, $1);
}
| declaration-specifiers declaration-specifier {
  $$ = YYSCAN_SNOC($1, $2);
}
;
declaration-specifier
: storage-class-specifier
| type-specifier
| type-qualifier
;
init-declarator-list.opt
: %empty {
  $$ = YYSCAN_TAG(AST_INIT_DECLARATOR_LIST);
}
| init-declarator-list
;
init-declarator-list
: init-declarator {
  $$ = YYSCAN_TAG(AST_INIT_DECLARATOR_LIST);
  $$ = YYSCAN_SNOC($$, $1);
}
| init-declarator-list "," init-declarator {
  $$ = YYSCAN_SNOC($1, $3);
}
;
init-declarator
: init-declarator.tag {
  $$ = YYSCAN_TAG(AST_INIT_DECLARATOR);
  $$ = YYSCAN_APPEND($$, $1);
}
;
init-declarator.tag
: declarator {
  $$ = YYSCAN_LIST($1);
}
| declarator assign initializer {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
;
storage-class-specifier
: storage-class-specifier.tag {
  $$ = YYSCAN_TAG(AST_STORAGE_CLASS_SPECIFIER);
  $$ = YYSCAN_SNOC($$, $1);
}
;
storage-class-specifier.tag
: typedef
| extern
| static
| auto
| register
;
type-specifier
: type-specifier.tag {
  $$ = YYSCAN_TAG(AST_TYPE_SPECIFIER);
  $$ = YYSCAN_SNOC($$, $1);
}
;
type-specifier.tag
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
: struct-or-union-specifier.tag {
  $$ = YYSCAN_TAG(AST_STRUCT_OR_UNION_SPECIFIER);
  $$ = YYSCAN_APPEND($$, $1);
}
;
struct-or-union-specifier.tag
: struct-or-union identifier.opt left-brace struct-declaration-list right-brace {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
  $$ = YYSCAN_SNOC($$, $4);
  $$ = YYSCAN_SNOC($$, $5);
}
| struct-or-union identifier {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
}
;
struct-or-union
: struct
| union
;
struct-declaration-list
: struct-declaration {
  $$ = YYSCAN_TAG(AST_STRUCT_DECLARATION_LIST);
  $$ = YYSCAN_SNOC($$, $1);
}
| struct-declaration-list struct-declaration {
  $$ = YYSCAN_SNOC($1, $2);
}
;
struct-declaration
: struct-declaration.tag {
  $$ = YYSCAN_TAG(AST_STRUCT_DECLARATION);
  $$ = YYSCAN_APPEND($$, $1);
}
struct-declaration.tag
: specifier-qualifier-list struct-declarator-list semicolon {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
;
specifier-qualifier-list
: specifier-qualifier {
  $$ = YYSCAN_TAG(AST_SPECIFIER_QUALIFIER_LIST);
  $$ = YYSCAN_SNOC($$, $1);
}
| specifier-qualifier-list specifier-qualifier {
  $$ = YYSCAN_SNOC($1, $2);
}
;
specifier-qualifier
: type-specifier
| type-qualifier
;
struct-declarator-list
: struct-declarator {
  $$ = YYSCAN_TAG(AST_STRUCT_DECLARATOR_LIST);
  $$ = YYSCAN_SNOC($$, $1);
}
| struct-declarator-list "," struct-declarator {
  $$ = YYSCAN_SNOC($1, $3);
}
;
struct-declarator
: struct-declarator.tag {
  $$ = YYSCAN_TAG(AST_STRUCT_DECLARATOR);
  $$ = YYSCAN_APPEND($$, $1);
}
;
struct-declarator.tag
: declarator {
  $$ = YYSCAN_LIST($1);
}
| declarator.opt colon constant-expression {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
;
enum-specifier
: enum-specifier.tag {
  $$ = YYSCAN_TAG(AST_ENUM_SPECIFIER);
  $$ = YYSCAN_APPEND($$, $1);
}
;
enum-specifier.tag
: enum identifier.opt left-brace enumerator-list right-brace {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
  $$ = YYSCAN_SNOC($$, $4);
  $$ = YYSCAN_SNOC($$, $5);
}
| enum identifier {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
}
;
enumerator-list
: enumerator {
  $$ = YYSCAN_TAG(AST_ENUMERATOR_LIST);
  $$ = YYSCAN_SNOC($$, $1);
}
| enumerator-list "," enumerator {
  $$ = YYSCAN_SNOC($1, $3);
}
;
enumerator
: enumerator.tag {
  $$ = YYSCAN_TAG(AST_ENUMERATOR);
  $$ = YYSCAN_APPEND($$, $1);
}
;
enumerator.tag
: enumeration-constant {
  $$ = YYSCAN_LIST($1);
}
| enumeration-constant assign constant-expression {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
;
type-qualifier
: type-qualifier.tag {
  $$ = YYSCAN_TAG(AST_TYPE_QUALIFIER);
  $$ = YYSCAN_SNOC($$, $1);
}
;
type-qualifier.tag
: const
| volatile
;
declarator.opt
: %empty {
  $$ = YYSCAN_NIL();
}
| declarator
;
declarator
: declarator.tag {
  $$ = YYSCAN_TAG(AST_DECLARATOR);
  $$ = YYSCAN_APPEND($$, $1);
}
;
declarator.tag
: direct-declarator {
  $$ = YYSCAN_LIST($1);
}
| pointer direct-declarator {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
}
;
direct-declarator
: direct-declarator.tag {
  $$ = YYSCAN_TAG(AST_DIRECT_DECLARATOR);
  $$ = YYSCAN_APPEND($$, $1);
}
;
direct-declarator.tag
: identifier {
  $$ = YYSCAN_LIST($1);
}
| left-paren declarator right-paren {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
| direct-declarator direct-declarator.suffix {
  $$ = YYSCAN_CONS($1, $2);
}
;
direct-declarator.suffix
: left-bracket constant-expression.opt right-bracket {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
| left-paren parameter-type-list.opt right-paren {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
| left-paren identifier-list right-paren {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
;
pointer
: pointer.tag {
  $$ = YYSCAN_TAG(AST_POINTER);
  $$ = YYSCAN_APPEND($$, $1);
}
;
pointer.tag
: asterisk type-qualifier-list.opt {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
}
| pointer asterisk type-qualifier-list.opt {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
;
type-qualifier-list.opt
: %empty {
  $$ = YYSCAN_TAG(AST_TYPE_QUALIFIER_LIST);
}
| type-qualifier-list
;
type-qualifier-list
: type-qualifier {
  $$ = YYSCAN_TAG(AST_TYPE_QUALIFIER_LIST);
  $$ = YYSCAN_SNOC($$, $1);
}
| type-qualifier-list type-qualifier {
  $$ = YYSCAN_SNOC($1, $2);
}
;
parameter-type-list.opt
: %empty {
  $$ = YYSCAN_TAG(AST_PARAMETER_LIST);
}
| parameter-type-list
;
parameter-type-list
: parameter-list
| parameter-list "," ellipsis {
  $$ = YYSCAN_SNOC($1, $3);
}
;
parameter-list
: parameter-declaration {
  $$ = YYSCAN_TAG(AST_PARAMETER_LIST);
  $$ = YYSCAN_SNOC($$, $1);
}
| parameter-list "," parameter-declaration {
  $$ = YYSCAN_SNOC($1, $3);
}
;
parameter-declaration
: parameter-declaration.tag {
  $$ = YYSCAN_TAG(AST_PARAMETER_DECLARATION);
  $$ = YYSCAN_APPEND($$, $1);
}
;
parameter-declaration.tag
: declaration-specifiers declarator {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
}
| declaration-specifiers abstract-declarator.opt {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
}
;
identifier-list
: identifier {
  $$ = YYSCAN_TAG(AST_IDENTIFIER_LIST);
  $$ = YYSCAN_SNOC($$, $1);
}
| identifier-list "," identifier {
  $$ = YYSCAN_SNOC($1, $3);
}
;
type-name
: type-name.tag {
  $$ = YYSCAN_TAG(AST_TYPE_NAME);
  $$ = YYSCAN_APPEND($$, $1);
}
;
type-name.tag
: specifier-qualifier-list abstract-declarator.opt {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
}
;
abstract-declarator.opt
: %empty {
  $$ = YYSCAN_NIL();
}
| abstract-declarator
;
abstract-declarator
: abstract-declarator.tag {
  $$ = YYSCAN_TAG(AST_ABSTRACT_DECLARATOR);
  $$ = YYSCAN_APPEND($$, $1);
}
;
abstract-declarator.tag
: pointer {
  $$ = YYSCAN_LIST($1);
}
| direct-abstract-declarator {
  $$ = YYSCAN_LIST($1);
}
| pointer direct-abstract-declarator {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
}
;
direct-abstract-declarator
: direct-abstract-declarator.tag {
  $$ = YYSCAN_TAG(AST_DIRECT_ABSTRACT_DECLARATOR);
  $$ = YYSCAN_APPEND($$, $1);
}
;
direct-abstract-declarator.tag
: left-paren abstract-declarator right-paren {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
| direct-abstract-declarator.suffix
| direct-abstract-declarator direct-abstract-declarator.suffix {
  $$ = YYSCAN_CONS($1, $2);
}
;
direct-abstract-declarator.suffix
: left-bracket constant-expression.opt right-bracket {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
| left-paren parameter-type-list.opt right-paren {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
;
typedef-name
: typedef-identifier {
  $$ = YYSCAN_TAG(AST_TYPEDEF_NAME);
  $$ = YYSCAN_SNOC($$, $1);
}
;
initializer
: assignment-expression
| initializer.tag {
  $$ = YYSCAN_TAG(AST_INITIALIZER);
  $$ = YYSCAN_APPEND($$, $1);
}
;
initializer.tag
: left-brace initializer-list right-brace {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
| left-brace initializer-list comma right-brace {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
  $$ = YYSCAN_SNOC($$, $4);
}
;
initializer-list
: initializer {
  $$ = YYSCAN_TAG(AST_INITIALIZER_LIST);
  $$ = YYSCAN_SNOC($$, $1);
}
| initializer-list "," initializer {
  $$ = YYSCAN_SNOC($1, $3);
}
;

/* 6.6 Statements */
statement
: statement.tag {
  $$ = YYSCAN_TAG(AST_STATEMENT);
  $$ = YYSCAN_SNOC($$, $1);
}
;
statement.tag
: labeled-statement
| compound-statement
| expression-statement
| selection-statement
| iteration-statement
| jump-statement
;
labeled-statement
: labeled-statement.tag {
  $$ = YYSCAN_TAG(AST_LABELED_STATEMENT);
  $$ = YYSCAN_APPEND($$, $1);
}
;
labeled-statement.tag
: identifier colon statement {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
| case constant-expression colon statement {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
  $$ = YYSCAN_SNOC($$, $4);
}
| default colon statement {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
;
compound-statement
: compound-statement.tag {
  $$ = YYSCAN_TAG(AST_COMPOUND_STATEMENT);
  $$ = YYSCAN_APPEND($$, $1);
}
;
compound-statement.tag
: left-brace declaration-list.opt statement-list.opt right-brace {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
  $$ = YYSCAN_SNOC($$, $4);
}
;
declaration-list.opt
: %empty {
  $$ = YYSCAN_TAG(AST_DECLARATION_LIST);
}
| declaration-list
;
declaration-list
: declaration {
  $$ = YYSCAN_TAG(AST_DECLARATION_LIST);
  $$ = YYSCAN_SNOC($$, $1);
}
| declaration-list declaration {
  $$ = YYSCAN_SNOC($1, $2);
}
;
statement-list.opt
: %empty {
  $$ = YYSCAN_TAG(AST_STATEMENT_LIST);
}
| statement-list
;
statement-list
: statement {
  $$ = YYSCAN_TAG(AST_STATEMENT_LIST);
  $$ = YYSCAN_SNOC($$, $1);
}
| statement-list statement {
  $$ = YYSCAN_SNOC($1, $2);
}
;
expression-statement
: expression-statement.tag {
  $$ = YYSCAN_TAG(AST_EXPRESSION_STATEMENT);
  $$ = YYSCAN_APPEND($$, $1);
}
;
expression-statement.tag
: expression.opt semicolon {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
}
;
selection-statement
: selection-statement.tag {
  $$ = YYSCAN_TAG(AST_SELECTION_STATEMENT);
  $$ = YYSCAN_APPEND($$, $1);
}
;
selection-statement.tag
: if left-paren expression right-paren statement %prec THEN {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
  $$ = YYSCAN_SNOC($$, $4);
  $$ = YYSCAN_SNOC($$, $5);
}
| if left-paren expression right-paren statement else statement {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
  $$ = YYSCAN_SNOC($$, $4);
  $$ = YYSCAN_SNOC($$, $5);
  $$ = YYSCAN_SNOC($$, $6);
  $$ = YYSCAN_SNOC($$, $7);
}
| switch left-paren expression right-paren statement {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
  $$ = YYSCAN_SNOC($$, $4);
  $$ = YYSCAN_SNOC($$, $5);
}
;
iteration-statement
: iteration-statement.tag {
  $$ = YYSCAN_TAG(AST_ITERATION_STATEMENT);
  $$ = YYSCAN_APPEND($$, $1);
}
;
iteration-statement.tag
: while left-paren expression right-paren statement {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
  $$ = YYSCAN_SNOC($$, $4);
  $$ = YYSCAN_SNOC($$, $5);
}
| do statement while left-paren expression right-paren semicolon {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
  $$ = YYSCAN_SNOC($$, $4);
  $$ = YYSCAN_SNOC($$, $5);
  $$ = YYSCAN_SNOC($$, $6);
  $$ = YYSCAN_SNOC($$, $7);
}
| for left-paren expression.opt semicolon expression.opt semicolon expression.opt right-paren statement {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
  $$ = YYSCAN_SNOC($$, $4);
  $$ = YYSCAN_SNOC($$, $5);
  $$ = YYSCAN_SNOC($$, $6);
  $$ = YYSCAN_SNOC($$, $7);
  $$ = YYSCAN_SNOC($$, $8);
  $$ = YYSCAN_SNOC($$, $9);
}
;
jump-statement
: jump-statement.tag {
  $$ = YYSCAN_TAG(AST_JUMP_STATEMENT);
  $$ = YYSCAN_APPEND($$, $1);
}
;
jump-statement.tag
: goto identifier semicolon {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
| continue semicolon {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
}
| break semicolon {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
}
| return expression.opt semicolon {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
;

/* 6.7 External definitions */
top
: translation-unit {
  YYSCAN_FINISH($1);
}
;
translation-unit
: external-declaration {
  $$ = YYSCAN_TAG(AST_TRANSLATION_UNIT);
  $$ = YYSCAN_SNOC($$, $1);
}
| translation-unit external-declaration {
  $$ = YYSCAN_SNOC($1, $2);
}
;
external-declaration
: function-definition
| declaration {
  YYSCAN_DECLARATION($1);
  $$ = YYSCAN_TAG(AST_EXTERNAL_DECLARATION);
  $$ = YYSCAN_SNOC($$, $1);
}
;
function-definition
: function-definition.tag {
  $$ = YYSCAN_TAG(AST_FUNCTION_DEFINITION);
  $$ = YYSCAN_APPEND($$, $1);
}
;
function-definition.tag
: declarator declaration-list.opt compound-statement {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
}
| declaration-specifiers declarator declaration-list.opt compound-statement {
  $$ = YYSCAN_LIST($1);
  $$ = YYSCAN_SNOC($$, $2);
  $$ = YYSCAN_SNOC($$, $3);
  $$ = YYSCAN_SNOC($$, $4);
}
;
%%
