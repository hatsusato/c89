%code requires {
#include "yyscan_t.h"
#include "sexp/opaque.h"
}

%define api.pure full
%define api.value.type {Sexp *}
%param {yyscan_t yyscanner}

%code provides {
#include "lexer.h"
#include "yyscan.h"
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
  $$ = yyscan_symbol(SYNTAX_AUTO);
}
;
break: "break" {
  $$ = yyscan_symbol(SYNTAX_BREAK);
}
;
case: "case" {
  $$ = yyscan_symbol(SYNTAX_CASE);
}
;
char: "char" {
  $$ = yyscan_symbol(SYNTAX_CHAR);
}
;
const: "const" {
  $$ = yyscan_symbol(SYNTAX_CONST);
}
;
continue: "continue" {
  $$ = yyscan_symbol(SYNTAX_CONTINUE);
}
;
default: "default" {
  $$ = yyscan_symbol(SYNTAX_DEFAULT);
}
;
do: "do" {
  $$ = yyscan_symbol(SYNTAX_DO);
}
;
double: "double" {
  $$ = yyscan_symbol(SYNTAX_DOUBLE);
}
;
else: "else" {
  $$ = yyscan_symbol(SYNTAX_ELSE);
}
;
enum: "enum" {
  $$ = yyscan_symbol(SYNTAX_ENUM);
}
;
extern: "extern" {
  $$ = yyscan_symbol(SYNTAX_EXTERN);
}
;
float: "float" {
  $$ = yyscan_symbol(SYNTAX_FLOAT);
}
;
for: "for" {
  $$ = yyscan_symbol(SYNTAX_FOR);
}
;
goto: "goto" {
  $$ = yyscan_symbol(SYNTAX_GOTO);
}
;
if: "if" {
  $$ = yyscan_symbol(SYNTAX_IF);
}
;
int: "int" {
  $$ = yyscan_symbol(SYNTAX_INT);
}
;
long: "long" {
  $$ = yyscan_symbol(SYNTAX_LONG);
}
;
register: "register" {
  $$ = yyscan_symbol(SYNTAX_REGISTER);
}
;
return: "return" {
  $$ = yyscan_symbol(SYNTAX_RETURN);
}
;
short: "short" {
  $$ = yyscan_symbol(SYNTAX_SHORT);
}
;
signed: "signed" {
  $$ = yyscan_symbol(SYNTAX_SIGNED);
}
;
sizeof: "sizeof" {
  $$ = yyscan_symbol(SYNTAX_SIZEOF);
}
;
static: "static" {
  $$ = yyscan_symbol(SYNTAX_STATIC);
}
;
struct: "struct" {
  $$ = yyscan_symbol(SYNTAX_STRUCT);
}
;
switch: "switch" {
  $$ = yyscan_symbol(SYNTAX_SWITCH);
}
;
typedef: "typedef" {
  $$ = yyscan_symbol(SYNTAX_TYPEDEF);
}
;
union: "union" {
  $$ = yyscan_symbol(SYNTAX_UNION);
}
;
unsigned: "unsigned" {
  $$ = yyscan_symbol(SYNTAX_UNSIGNED);
}
;
void: "void" {
  $$ = yyscan_symbol(SYNTAX_VOID);
}
;
volatile: "volatile" {
  $$ = yyscan_symbol(SYNTAX_VOLATILE);
}
;
while: "while" {
  $$ = yyscan_symbol(SYNTAX_WHILE);
}
;

period: "." {
  $$ = yyscan_symbol(SYNTAX_PERIOD);
}
;
arrow: "->" {
  $$ = yyscan_symbol(SYNTAX_ARROW);
}
;
increment: "++" {
  $$ = yyscan_symbol(SYNTAX_INCREMENT);
}
;
decrement: "--" {
  $$ = yyscan_symbol(SYNTAX_DECREMENT);
}
;
ampersand: "&" {
  $$ = yyscan_symbol(SYNTAX_AMPERSAND);
}
;
asterisk: "*" {
  $$ = yyscan_symbol(SYNTAX_ASTERISK);
}
;
plus: "+" {
  $$ = yyscan_symbol(SYNTAX_PLUS);
}
;
minus: "-" {
  $$ = yyscan_symbol(SYNTAX_MINUS);
}
;
tilde: "~" {
  $$ = yyscan_symbol(SYNTAX_TILDE);
}
;
exclamation: "!" {
  $$ = yyscan_symbol(SYNTAX_EXCLAMATION);
}
;
slash: "/" {
  $$ = yyscan_symbol(SYNTAX_SLASH);
}
;
percent: "%" {
  $$ = yyscan_symbol(SYNTAX_PERCENT);
}
;
left-shift: "<<" {
  $$ = yyscan_symbol(SYNTAX_LEFT_SHIFT);
}
;
right-shift: ">>" {
  $$ = yyscan_symbol(SYNTAX_RIGHT_SHIFT);
}
;
less-than: "<" {
  $$ = yyscan_symbol(SYNTAX_LESS_THAN);
}
;
greater-than: ">" {
  $$ = yyscan_symbol(SYNTAX_GREATER_THAN);
}
;
less-equal: "<=" {
  $$ = yyscan_symbol(SYNTAX_LESS_EQUAL);
}
;
greater-equal: ">=" {
  $$ = yyscan_symbol(SYNTAX_GREATER_EQUAL);
}
;
equal: "==" {
  $$ = yyscan_symbol(SYNTAX_EQUAL);
}
;
not-equal: "!=" {
  $$ = yyscan_symbol(SYNTAX_NOT_EQUAL);
}
;
caret: "^" {
  $$ = yyscan_symbol(SYNTAX_CARET);
}
;
bar: "|" {
  $$ = yyscan_symbol(SYNTAX_BAR);
}
;
and: "&&" {
  $$ = yyscan_symbol(SYNTAX_AND);
}
;
or: "||" {
  $$ = yyscan_symbol(SYNTAX_OR);
}
;
question: "?" {
  $$ = yyscan_symbol(SYNTAX_QUESTION);
}
;
assign: "=" {
  $$ = yyscan_symbol(SYNTAX_ASSIGN);
}
;
asterisk-assign: "*=" {
  $$ = yyscan_symbol(SYNTAX_ASTERISK_ASSIGN);
}
;
slash-assign: "/=" {
  $$ = yyscan_symbol(SYNTAX_SLASH_ASSIGN);
}
;
percent-assign: "%=" {
  $$ = yyscan_symbol(SYNTAX_PERCENT_ASSIGN);
}
;
plus-assign: "+=" {
  $$ = yyscan_symbol(SYNTAX_PLUS_ASSIGN);
}
;
minus-assign: "-=" {
  $$ = yyscan_symbol(SYNTAX_MINUS_ASSIGN);
}
;
left-shift-assign: "<<=" {
  $$ = yyscan_symbol(SYNTAX_LEFT_SHIFT_ASSIGN);
}
;
right-shift-assign: ">>=" {
  $$ = yyscan_symbol(SYNTAX_RIGHT_SHIFT_ASSIGN);
}
;
ampersand-assign: "&=" {
  $$ = yyscan_symbol(SYNTAX_AMPERSAND_ASSIGN);
}
;
caret-assign: "^=" {
  $$ = yyscan_symbol(SYNTAX_CARET_ASSIGN);
}
;
bar-assign: "|=" {
  $$ = yyscan_symbol(SYNTAX_BAR_ASSIGN);
}
;

left-bracket: "[" {
  $$ = yyscan_symbol(SYNTAX_LEFT_BRACKET);
}
;
right-bracket: "]" {
  $$ = yyscan_symbol(SYNTAX_RIGHT_BRACKET);
}
;
left-paren: "(" {
  $$ = yyscan_symbol(SYNTAX_LEFT_PAREN);
}
;
right-paren: ")" {
  $$ = yyscan_symbol(SYNTAX_RIGHT_PAREN);
}
;
left-brace: "{" {
  $$ = yyscan_symbol(SYNTAX_LEFT_BRACE);
}
;
right-brace: "}" {
  $$ = yyscan_symbol(SYNTAX_RIGHT_BRACE);
}
;
comma: "," {
  $$ = yyscan_symbol(SYNTAX_COMMA);
}
;
colon: ":" {
  $$ = yyscan_symbol(SYNTAX_COLON);
}
;
semicolon: ";" {
  $$ = yyscan_symbol(SYNTAX_SEMICOLON);
}
;
ellipsis: "..." {
  $$ = yyscan_symbol(SYNTAX_ELLIPSIS);
}
;

/* 6.1 Lexical elements */
identifier.opt
: %empty {
  $$ = yyscan_nil();
}
| identifier
;
identifier
: identifier.tag {
  $$ = yyscan_tag(SYNTAX_IDENTIFIER);
  $$ = yyscan_snoc($$, $1);
}
;
identifier.tag
: TOKEN_IDENTIFIER {
  $$ = yyscan_token(yyscanner);
}
;
typedef-identifier
: typedef-identifier.tag {
  $$ = yyscan_tag(SYNTAX_TYPEDEF_IDENTIFIER);
  $$ = yyscan_snoc($$, $1);
}
;
typedef-identifier.tag
: TOKEN_TYPEDEF_IDENTIFIER {
  $$ = yyscan_token(yyscanner);
}
;
floating-constant
: floating-constant.tag {
  $$ = yyscan_tag(SYNTAX_FLOATING_CONSTANT);
  $$ = yyscan_snoc($$, $1);
}
;
floating-constant.tag
: TOKEN_FLOATING_CONSTANT {
  $$ = yyscan_token(yyscanner);
}
;
integer-constant
: integer-constant.tag {
  $$ = yyscan_tag(SYNTAX_INTEGER_CONSTANT);
  $$ = yyscan_snoc($$, $1);
}
;
integer-constant.tag
: TOKEN_INTEGER_CONSTANT {
  $$ = yyscan_token(yyscanner);
}
;
enumeration-constant
: enumeration-constant.tag {
  $$ = yyscan_tag(SYNTAX_ENUMERATION_CONSTANT);
  $$ = yyscan_snoc($$, $1);
}
;
enumeration-constant.tag
: TOKEN_IDENTIFIER {
  $$ = yyscan_token(yyscanner);
}
;
character-constant
: character-constant.tag {
  $$ = yyscan_tag(SYNTAX_CHARACTER_CONSTANT);
  $$ = yyscan_snoc($$, $1);
}
;
character-constant.tag
: TOKEN_CHARACTER_CONSTANT {
  $$ = yyscan_token(yyscanner);
}
;
string-literal
: TOKEN_STRING_LITERAL {
  $$ = yyscan_token(yyscanner);
}
;
string-constant
: string-literal {
  $$ = yyscan_tag(SYNTAX_STRING_LITERAL);
  $$ = yyscan_snoc($$, $1);
}
| string-constant string-literal {
  $$ = $1;
  $$ = yyscan_snoc($$, $2);
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
  $$ = yyscan_tag(SYNTAX_PRIMARY_EXPRESSION);
  $$ = yyscan_snoc($$, $1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
}
;
postfix-expression
: primary-expression
| postfix-expression.tag {
  $$ = yyscan_tag(SYNTAX_POSTFIX_EXPRESSION);
  $$ = yyscan_append($$, $1);
}
;
postfix-expression.tag
: postfix-expression postfix-expression.suffix {
  $$ = yyscan_cons($1, $2);
}
;
postfix-expression.suffix
: left-bracket expression right-bracket {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
}
| left-paren argument-expression-list.opt right-paren {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
}
| period identifier {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
}
| arrow identifier {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
}
| increment {
  $$ = yyscan_list($1);
}
| decrement {
  $$ = yyscan_list($1);
}
;
argument-expression-list.opt
: %empty {
  $$ = yyscan_tag(SYNTAX_ARGUMENT_EXPRESSION_LIST);
}
| argument-expression-list
;
argument-expression-list
: assignment-expression {
  $$ = yyscan_tag(SYNTAX_ARGUMENT_EXPRESSION_LIST);
  $$ = yyscan_snoc($$, $1);
}
| argument-expression-list "," assignment-expression {
  $$ = $1;
  $$ = yyscan_snoc($$, $3);
}
;
unary-expression
: postfix-expression
| unary-expression.tag {
  $$ = yyscan_tag(SYNTAX_UNARY_EXPRESSION);
  $$ = yyscan_append($$, $1);
}
;
unary-expression.tag
: increment unary-expression {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
}
| decrement unary-expression {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
}
| unary-operator cast-expression {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
}
| sizeof unary-expression {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
}
| sizeof left-paren type-name right-paren {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
  $$ = yyscan_snoc($$, $4);
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
  $$ = yyscan_tag(SYNTAX_CAST_EXPRESSION);
  $$ = yyscan_append($$, $1);
}
;
cast-expression.tag
: left-paren type-name right-paren cast-expression {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
  $$ = yyscan_snoc($$, $4);
}
;
multiplicative-expression
: cast-expression
| multiplicative-expression.tag {
  $$ = yyscan_tag(SYNTAX_MULTIPLICATIVE_EXPRESSION);
  $$ = yyscan_append($$, $1);
}
;
multiplicative-expression.tag
: multiplicative-expression multiplicative-operator cast-expression {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
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
  $$ = yyscan_tag(SYNTAX_ADDITIVE_EXPRESSION);
  $$ = yyscan_append($$, $1);
}
;
additive-expression.tag
: additive-expression additive-operator multiplicative-expression {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
}
;
additive-operator
: plus
| minus
;
shift-expression
: additive-expression
| shift-expression.tag {
  $$ = yyscan_tag(SYNTAX_SHIFT_EXPRESSION);
  $$ = yyscan_append($$, $1);
}
;
shift-expression.tag
: shift-expression shift-operator additive-expression {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
}
;
shift-operator
: left-shift
| right-shift
;
relational-expression
: shift-expression
| relational-expression.tag {
  $$ = yyscan_tag(SYNTAX_RELATIONAL_EXPRESSION);
  $$ = yyscan_append($$, $1);
}
;
relational-expression.tag
: relational-expression relational-operator shift-expression {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
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
  $$ = yyscan_tag(SYNTAX_EQUALITY_EXPRESSION);
  $$ = yyscan_append($$, $1);
}
;
equality-expression.tag
: equality-expression equality-operator relational-expression {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
}
;
equality-operator
: equal
| not-equal
;
and-expression
: equality-expression
| and-expression.tag {
  $$ = yyscan_tag(SYNTAX_AND_EXPRESSION);
  $$ = yyscan_append($$, $1);
}
;
and-expression.tag
: and-expression ampersand equality-expression {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
}
;
exclusive-or-expression
: and-expression
| exclusive-or-expression.tag {
  $$ = yyscan_tag(SYNTAX_EXCLUSIVE_OR_EXPRESSION);
  $$ = yyscan_append($$, $1);
}
;
exclusive-or-expression.tag
: exclusive-or-expression caret and-expression {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
}
;
inclusive-or-expression
: exclusive-or-expression
| inclusive-or-expression.tag {
  $$ = yyscan_tag(SYNTAX_INCLUSIVE_OR_EXPRESSION);
  $$ = yyscan_append($$, $1);
}
;
inclusive-or-expression.tag
: inclusive-or-expression bar exclusive-or-expression {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
}
;
logical-and-expression
: inclusive-or-expression
| logical-and-expression.tag {
  $$ = yyscan_tag(SYNTAX_LOGICAL_AND_EXPRESSION);
  $$ = yyscan_append($$, $1);
}
;
logical-and-expression.tag
: logical-and-expression and inclusive-or-expression {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
}
;
logical-or-expression
: logical-and-expression
| logical-or-expression.tag {
  $$ = yyscan_tag(SYNTAX_LOGICAL_OR_EXPRESSION);
  $$ = yyscan_append($$, $1);
}
;
logical-or-expression.tag
: logical-or-expression or logical-and-expression {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
}
;
conditional-expression
: logical-or-expression
| conditional-expression.tag {
  $$ = yyscan_tag(SYNTAX_CONDITIONAL_EXPRESSION);
  $$ = yyscan_append($$, $1);
}
;
conditional-expression.tag
: logical-or-expression question expression colon conditional-expression {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
  $$ = yyscan_snoc($$, $4);
  $$ = yyscan_snoc($$, $5);
}
;
assignment-expression
: conditional-expression
| assignment-expression.tag {
  $$ = yyscan_tag(SYNTAX_ASSIGNMENT_EXPRESSION);
  $$ = yyscan_append($$, $1);
}
;
assignment-expression.tag
: unary-expression assignment-operator assignment-expression {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
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
  $$ = yyscan_nil();
}
| expression
;
expression
: assignment-expression
| expression.tag {
  $$ = yyscan_tag(SYNTAX_EXPRESSION);
  $$ = yyscan_append($$, $1);
}
;
expression.tag
: expression "," assignment-expression {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $3);
}
;

/* 6.4 Constant expressions */
constant-expression.opt
: %empty {
  $$ = yyscan_nil();
}
| constant-expression
;
constant-expression
: conditional-expression {
  $$ = yyscan_tag(SYNTAX_CONSTANT_EXPRESSION);
  $$ = yyscan_snoc($$, $1);
}
;

/* 6.5 Declarations */
declaration
: declaration.tag {
  $$ = yyscan_tag(SYNTAX_DECLARATION);
  $$ = yyscan_append($$, $1);
}
;
declaration.tag
: declaration-specifiers init-declarator-list.opt semicolon {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
}
;
declaration-specifiers
: declaration-specifier {
  $$ = yyscan_tag(SYNTAX_DECLARATION_SPECIFIERS);
  $$ = yyscan_snoc($$, $1);
}
| declaration-specifiers declaration-specifier {
  $$ = $1;
  $$ = yyscan_snoc($$, $2);
}
;
declaration-specifier
: storage-class-specifier
| type-specifier
| type-qualifier
;
init-declarator-list.opt
: %empty {
  $$ = yyscan_tag(SYNTAX_INIT_DECLARATOR_LIST);
}
| init-declarator-list
;
init-declarator-list
: init-declarator {
  $$ = yyscan_tag(SYNTAX_INIT_DECLARATOR_LIST);
  $$ = yyscan_snoc($$, $1);
}
| init-declarator-list "," init-declarator {
  $$ = $1;
  $$ = yyscan_snoc($$, $3);
}
;
init-declarator
: init-declarator.tag {
  $$ = yyscan_tag(SYNTAX_INIT_DECLARATOR);
  $$ = yyscan_append($$, $1);
}
;
init-declarator.tag
: declarator {
  $$ = yyscan_list($1);
}
| declarator assign initializer {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
}
;
storage-class-specifier
: storage-class-specifier.tag {
  $$ = yyscan_tag(SYNTAX_STORAGE_CLASS_SPECIFIER);
  $$ = yyscan_snoc($$, $1);
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
  $$ = yyscan_tag(SYNTAX_TYPE_SPECIFIER);
  $$ = yyscan_snoc($$, $1);
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
  $$ = yyscan_tag(SYNTAX_STRUCT_OR_UNION_SPECIFIER);
  $$ = yyscan_append($$, $1);
}
;
struct-or-union-specifier.tag
: struct-or-union identifier.opt left-brace struct-declaration-list right-brace {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
  $$ = yyscan_snoc($$, $4);
  $$ = yyscan_snoc($$, $5);
}
| struct-or-union identifier {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
}
;
struct-or-union
: struct
| union
;
struct-declaration-list
: struct-declaration {
  $$ = yyscan_tag(SYNTAX_STRUCT_DECLARATION_LIST);
  $$ = yyscan_snoc($$, $1);
}
| struct-declaration-list struct-declaration {
  $$ = $1;
  $$ = yyscan_snoc($$, $2);
}
;
struct-declaration
: struct-declaration.tag {
  $$ = yyscan_tag(SYNTAX_STRUCT_DECLARATION);
  $$ = yyscan_append($$, $1);
}
struct-declaration.tag
: specifier-qualifier-list struct-declarator-list semicolon {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
}
;
specifier-qualifier-list
: specifier-qualifier {
  $$ = yyscan_tag(SYNTAX_SPECIFIER_QUALIFIER_LIST);
  $$ = yyscan_snoc($$, $1);
}
| specifier-qualifier-list specifier-qualifier {
  $$ = $1;
  $$ = yyscan_snoc($$, $2);
}
;
specifier-qualifier
: type-specifier
| type-qualifier
;
struct-declarator-list
: struct-declarator {
  $$ = yyscan_tag(SYNTAX_STRUCT_DECLARATOR_LIST);
  $$ = yyscan_snoc($$, $1);
}
| struct-declarator-list "," struct-declarator {
  $$ = $1;
  $$ = yyscan_snoc($$, $3);
}
;
struct-declarator
: struct-declarator.tag {
  $$ = yyscan_tag(SYNTAX_STRUCT_DECLARATOR);
  $$ = yyscan_append($$, $1);
}
;
struct-declarator.tag
: declarator {
  $$ = yyscan_list($1);
}
| declarator.opt colon constant-expression {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
}
;
enum-specifier
: enum-specifier.tag {
  $$ = yyscan_tag(SYNTAX_ENUM_SPECIFIER);
  $$ = yyscan_append($$, $1);
}
;
enum-specifier.tag
: enum identifier.opt left-brace enumerator-list right-brace {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
  $$ = yyscan_snoc($$, $4);
  $$ = yyscan_snoc($$, $5);
}
| enum identifier {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
}
;
enumerator-list
: enumerator {
  $$ = yyscan_tag(SYNTAX_ENUMERATOR_LIST);
  $$ = yyscan_snoc($$, $1);
}
| enumerator-list "," enumerator {
  $$ = $1;
  $$ = yyscan_snoc($$, $3);
}
;
enumerator
: enumerator.tag {
  $$ = yyscan_tag(SYNTAX_ENUMERATOR);
  $$ = yyscan_append($$, $1);
}
;
enumerator.tag
: enumeration-constant {
  $$ = yyscan_list($1);
}
| enumeration-constant assign constant-expression {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
}
;
type-qualifier
: type-qualifier.tag {
  $$ = yyscan_tag(SYNTAX_TYPE_QUALIFIER);
  $$ = yyscan_snoc($$, $1);
}
;
type-qualifier.tag
: const
| volatile
;
declarator.opt
: %empty {
  $$ = yyscan_nil();
}
| declarator
;
declarator
: declarator.tag {
  $$ = yyscan_tag(SYNTAX_DECLARATOR);
  $$ = yyscan_append($$, $1);
}
;
declarator.tag
: direct-declarator {
  $$ = yyscan_list($1);
}
| pointer direct-declarator {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
}
;
direct-declarator
: direct-declarator.tag {
  $$ = yyscan_tag(SYNTAX_DIRECT_DECLARATOR);
  $$ = yyscan_append($$, $1);
}
;
direct-declarator.tag
: identifier {
  $$ = yyscan_list($1);
}
| left-paren declarator right-paren {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
}
| direct-declarator direct-declarator.suffix {
  $$ = yyscan_cons($1, $2);
}
;
direct-declarator.suffix
: left-bracket constant-expression.opt right-bracket {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
}
| left-paren parameter-type-list.opt right-paren {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
}
| left-paren identifier-list right-paren {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
}
;
pointer
: pointer.tag {
  $$ = yyscan_tag(SYNTAX_POINTER);
  $$ = yyscan_append($$, $1);
}
;
pointer.tag
: asterisk type-qualifier-list.opt {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
}
| pointer asterisk type-qualifier-list.opt {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
}
;
type-qualifier-list.opt
: %empty {
  $$ = yyscan_tag(SYNTAX_TYPE_QUALIFIER_LIST);
}
| type-qualifier-list
;
type-qualifier-list
: type-qualifier {
  $$ = yyscan_tag(SYNTAX_TYPE_QUALIFIER_LIST);
  $$ = yyscan_snoc($$, $1);
}
| type-qualifier-list type-qualifier {
  $$ = $1;
  $$ = yyscan_snoc($$, $2);
}
;
parameter-type-list.opt
: %empty {
  $$ = yyscan_tag(SYNTAX_PARAMETER_LIST);
}
| parameter-type-list
;
parameter-type-list
: parameter-list
| parameter-list "," ellipsis {
  $$ = $1;
  $$ = yyscan_snoc($$, $3);
}
;
parameter-list
: parameter-declaration {
  $$ = yyscan_tag(SYNTAX_PARAMETER_LIST);
  $$ = yyscan_snoc($$, $1);
}
| parameter-list "," parameter-declaration {
  $$ = $1;
  $$ = yyscan_snoc($$, $3);
}
;
parameter-declaration
: parameter-declaration.tag {
  $$ = yyscan_tag(SYNTAX_PARAMETER_DECLARATION);
  $$ = yyscan_append($$, $1);
}
;
parameter-declaration.tag
: declaration-specifiers declarator {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
}
| declaration-specifiers abstract-declarator.opt {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
}
;
identifier-list
: identifier {
  $$ = yyscan_tag(SYNTAX_IDENTIFIER_LIST);
  $$ = yyscan_snoc($$, $1);
}
| identifier-list "," identifier {
  $$ = $1;
  $$ = yyscan_snoc($$, $3);
}
;
type-name
: type-name.tag {
  $$ = yyscan_tag(SYNTAX_TYPE_NAME);
  $$ = yyscan_append($$, $1);
}
;
type-name.tag
: specifier-qualifier-list abstract-declarator.opt {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
}
;
abstract-declarator.opt
: %empty {
  $$ = yyscan_nil();
}
| abstract-declarator
;
abstract-declarator
: abstract-declarator.tag {
  $$ = yyscan_tag(SYNTAX_ABSTRACT_DECLARATOR);
  $$ = yyscan_append($$, $1);
}
;
abstract-declarator.tag
: pointer {
  $$ = yyscan_list($1);
}
| direct-abstract-declarator {
  $$ = yyscan_list($1);
}
| pointer direct-abstract-declarator {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
}
;
direct-abstract-declarator
: direct-abstract-declarator.tag {
  $$ = yyscan_tag(SYNTAX_DIRECT_ABSTRACT_DECLARATOR);
  $$ = yyscan_append($$, $1);
}
;
direct-abstract-declarator.tag
: left-paren abstract-declarator right-paren {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
}
| direct-abstract-declarator.suffix
| direct-abstract-declarator direct-abstract-declarator.suffix {
  $$ = yyscan_cons($1, $2);
}
;
direct-abstract-declarator.suffix
: left-bracket constant-expression.opt right-bracket {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
}
| left-paren parameter-type-list.opt right-paren {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
}
;
typedef-name
: typedef-identifier {
  $$ = yyscan_tag(SYNTAX_TYPEDEF_NAME);
  $$ = yyscan_snoc($$, $1);
}
;
initializer
: assignment-expression
| initializer.tag {
  $$ = yyscan_tag(SYNTAX_INITIALIZER);
  $$ = yyscan_append($$, $1);
}
;
initializer.tag
: left-brace initializer-list right-brace {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
}
| left-brace initializer-list comma right-brace {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
  $$ = yyscan_snoc($$, $4);
}
;
initializer-list
: initializer {
  $$ = yyscan_tag(SYNTAX_INITIALIZER_LIST);
  $$ = yyscan_snoc($$, $1);
}
| initializer-list "," initializer {
  $$ = $1;
  $$ = yyscan_snoc($$, $3);
}
;

/* 6.6 Statements */
statement
: statement.tag {
  $$ = yyscan_tag(SYNTAX_STATEMENT);
  $$ = yyscan_snoc($$, $1);
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
  $$ = yyscan_tag(SYNTAX_LABELED_STATEMENT);
  $$ = yyscan_append($$, $1);
}
;
labeled-statement.tag
: identifier colon statement {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
}
| case constant-expression colon statement {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
  $$ = yyscan_snoc($$, $4);
}
| default colon statement {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
}
;
compound-statement
: compound-statement.tag {
  $$ = yyscan_tag(SYNTAX_COMPOUND_STATEMENT);
  $$ = yyscan_append($$, $1);
}
;
compound-statement.tag
: left-brace declaration-list.opt statement-list.opt right-brace {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
  $$ = yyscan_snoc($$, $4);
}
;
declaration-list.opt
: %empty {
  $$ = yyscan_tag(SYNTAX_DECLARATION_LIST);
}
| declaration-list
;
declaration-list
: declaration {
  $$ = yyscan_tag(SYNTAX_DECLARATION_LIST);
  $$ = yyscan_snoc($$, $1);
}
| declaration-list declaration {
  $$ = $1;
  $$ = yyscan_snoc($$, $2);
}
;
statement-list.opt
: %empty {
  $$ = yyscan_tag(SYNTAX_STATEMENT_LIST);
}
| statement-list
;
statement-list
: statement {
  $$ = yyscan_tag(SYNTAX_STATEMENT_LIST);
  $$ = yyscan_snoc($$, $1);
}
| statement-list statement {
  $$ = $1;
  $$ = yyscan_snoc($$, $2);
}
;
expression-statement
: expression-statement.tag {
  $$ = yyscan_tag(SYNTAX_EXPRESSION_STATEMENT);
  $$ = yyscan_append($$, $1);
}
;
expression-statement.tag
: expression.opt semicolon {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
}
;
selection-statement
: selection-statement.tag {
  $$ = yyscan_tag(SYNTAX_SELECTION_STATEMENT);
  $$ = yyscan_append($$, $1);
}
;
selection-statement.tag
: if left-paren expression right-paren statement %prec THEN {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
  $$ = yyscan_snoc($$, $4);
  $$ = yyscan_snoc($$, $5);
}
| if left-paren expression right-paren statement else statement {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
  $$ = yyscan_snoc($$, $4);
  $$ = yyscan_snoc($$, $5);
  $$ = yyscan_snoc($$, $6);
  $$ = yyscan_snoc($$, $7);
}
| switch left-paren expression right-paren statement {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
  $$ = yyscan_snoc($$, $4);
  $$ = yyscan_snoc($$, $5);
}
;
iteration-statement
: iteration-statement.tag {
  $$ = yyscan_tag(SYNTAX_ITERATION_STATEMENT);
  $$ = yyscan_append($$, $1);
}
;
iteration-statement.tag
: while left-paren expression right-paren statement {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
  $$ = yyscan_snoc($$, $4);
  $$ = yyscan_snoc($$, $5);
}
| do statement while left-paren expression right-paren semicolon {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
  $$ = yyscan_snoc($$, $4);
  $$ = yyscan_snoc($$, $5);
  $$ = yyscan_snoc($$, $6);
  $$ = yyscan_snoc($$, $7);
}
| for left-paren expression.opt semicolon expression.opt semicolon expression.opt right-paren statement {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
  $$ = yyscan_snoc($$, $4);
  $$ = yyscan_snoc($$, $5);
  $$ = yyscan_snoc($$, $6);
  $$ = yyscan_snoc($$, $7);
  $$ = yyscan_snoc($$, $8);
  $$ = yyscan_snoc($$, $9);
}
;
jump-statement
: jump-statement.tag {
  $$ = yyscan_tag(SYNTAX_JUMP_STATEMENT);
  $$ = yyscan_append($$, $1);
}
;
jump-statement.tag
: goto identifier semicolon {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
}
| continue semicolon {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
}
| break semicolon {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
}
| return expression.opt semicolon {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
}
;

/* 6.7 External definitions */
top
: translation-unit {
  yyscan_finish($1, yyscanner);
}
;
translation-unit
: external-declaration {
  $$ = yyscan_tag(SYNTAX_TRANSLATION_UNIT);
  $$ = yyscan_snoc($$, $1);
}
| translation-unit external-declaration {
  $$ = $1;
  $$ = yyscan_snoc($$, $2);
}
;
external-declaration
: function-definition
| declaration {
  yyscan_declaration($1, yyscanner);
  $$ = yyscan_tag(SYNTAX_EXTERNAL_DECLARATION);
  $$ = yyscan_snoc($$, $1);
}
;
function-definition
: function-definition.tag {
  $$ = yyscan_tag(SYNTAX_FUNCTION_DEFINITION);
  $$ = yyscan_append($$, $1);
}
;
function-definition.tag
: declarator declaration-list.opt compound-statement {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
}
| declaration-specifiers declarator declaration-list.opt compound-statement {
  $$ = yyscan_list($1);
  $$ = yyscan_snoc($$, $2);
  $$ = yyscan_snoc($$, $3);
  $$ = yyscan_snoc($$, $4);
}
;
%%
