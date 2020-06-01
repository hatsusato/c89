%code top {
}
%code requires {
#include "vector.h"
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
  typedef void* yyscan_t;
#endif
}
%code provides {
#include "lexer.h"
#include "parser.h"
}

%define api.pure full
%define api.value.type {Vector *}
%param {yyscan_t scanner}

%token TOKEN_IDENTIFIER
%token TOKEN_FLOATING_CONSTANT
%token TOKEN_INTEGER_CONSTANT
%token TOKEN_CHARACTER_CONSTANT
%token TOKEN_STRING_LITERAL
%token TOKEN_UNKNOWN

%token KEYWORD_AUTO "auto"
%token KEYWORD_BREAK "break"
%token KEYWORD_CASE "case"
%token KEYWORD_CHAR "char"
%token KEYWORD_CONST "const"
%token KEYWORD_CONTINUE "continue"
%token KEYWORD_DEFAULT "default"
%token KEYWORD_DO "do"
%token KEYWORD_DOUBLE "double"
%token KEYWORD_ELSE "else"
%token KEYWORD_ENUM "enum"
%token KEYWORD_EXTERN "extern"
%token KEYWORD_FLOAT "float"
%token KEYWORD_FOR "for"
%token KEYWORD_GOTO "goto"
%token KEYWORD_IF "if"
%token KEYWORD_INT "int"
%token KEYWORD_LONG "long"
%token KEYWORD_REGISTER "register"
%token KEYWORD_RETURN "return"
%token KEYWORD_SHORT "short"
%token KEYWORD_SIGNED "signed"
%token KEYWORD_SIZEOF "sizeof"
%token KEYWORD_STATIC "static"
%token KEYWORD_STRUCT "struct"
%token KEYWORD_SWITCH "switch"
%token KEYWORD_TYPEDEF "typedef"
%token KEYWORD_UNION "union"
%token KEYWORD_UNSIGNED "unsigned"
%token KEYWORD_VOID "void"
%token KEYWORD_VOLATILE "volatile"
%token KEYWORD_WHILE "while"

%token OPERATOR_PERIOD "."
%token OPERATOR_ARROW "->"
%token OPERATOR_INCREMENT "++"
%token OPERATOR_DECREMENT "--"
%token OPERATOR_AMPERSAND "&"
%token OPERATOR_ASTERISK "*"
%token OPERATOR_PLUS "+"
%token OPERATOR_MINUS "-"
%token OPERATOR_TILDE "~"
%token OPERATOR_EXCLAMATION "!"
%token OPERATOR_SLASH "/"
%token OPERATOR_PERCENT "%"
%token OPERATOR_LEFT_SHIFT "<<"
%token OPERATOR_RIGHT_SHIFT ">>"
%token OPERATOR_LESS_THAN "<"
%token OPERATOR_GREATER_THAN ">"
%token OPERATOR_LESS_EQUAL "<="
%token OPERATOR_GREATER_EQUAL ">="
%token OPERATOR_EQUAL "=="
%token OPERATOR_NOT_EQUAL "!="
%token OPERATOR_CARET "^"
%token OPERATOR_BAR "|"
%token OPERATOR_AND "&&"
%token OPERATOR_OR "||"
%token OPERATOR_QUESTION "?"
%token OPERATOR_ASSIGN "="
%token OPERATOR_ASTERISK_ASSIGN "*="
%token OPERATOR_SLASH_ASSIGN "/="
%token OPERATOR_PERCENT_ASSIGN "%="
%token OPERATOR_PLUS_ASSIGN "+="
%token OPERATOR_MINUS_ASSIGN "-="
%token OPERATOR_LEFT_SHIFT_ASSIGN "<<="
%token OPERATOR_RIGHT_SHIFT_ASSIGN ">>="
%token OPERATOR_AMPERSAND_ASSIGN "&="
%token OPERATOR_CARET_ASSIGN "^="
%token OPERATOR_BAR_ASSIGN "|="

%token PUNCTUATOR_LEFT_BRACKET "["
%token PUNCTUATOR_RIGHT_BRACKET "]"
%token PUNCTUATOR_LEFT_PAREN "("
%token PUNCTUATOR_RIGHT_PAREN ")"
%token PUNCTUATOR_LEFT_BRACE "{"
%token PUNCTUATOR_RIGHT_BRACE "}"
%token PUNCTUATOR_COMMA ","
%token PUNCTUATOR_COLON ":"
%token PUNCTUATOR_SEMICOLON ";"
%token PUNCTUATOR_ELLIPSIS "..."

%start top
%%
top
: %empty { $$ = yyget_extra(scanner); }
| top[lhs] expression[rhs] ";" { ast_set_top($lhs, $rhs); }
;
identifier
: TOKEN_IDENTIFIER
;
constant
: floating-constant
| integer-constant
/* | enumeration-constant */
| character-constant
;
floating-constant
: TOKEN_FLOATING_CONSTANT
;
integer-constant
: TOKEN_INTEGER_CONSTANT
;
/* enumeration-constant */
/* : TOKEN_IDENTIFIER */
/* ; */
character-constant
: TOKEN_CHARACTER_CONSTANT
;
string-literal
: TOKEN_STRING_LITERAL
;
primary-expression
: identifier
| constant
| string-literal
| "(" expression ")"
;
expression
: primary-expression
;
/* postfix-expression */
/* : primary-expression */
/* | postfix-expression postfix-operator */
/* ; */
/* postfix-operator */
/* : "[" expression "]" */
/* | "(" argument-expression-list.opt ")" */
/* | "." identifier */
/* | "->" identifier */
/* | "++" */
/* | "--" */
/* ; */
/* argument-expression-list.opt */
/* : %empty */
/* | expression */
/* ; */
/* unary-expression */
/* : postfix-expression */
/* | "++" unary-expression */
/* | "--" unary-expression */
/* | unary-operator cast-expression */
/* | "sizeof" unary-expression */
/* | "sizeof" "(" type-name ")" */
/* ; */
/* unary-operator */
/* : "&" | "*" | "+" | "-" | "~" | "!" */
/* ; */
/* cast-expression */
/* : unary-expression */
/* | "(" type-name ")" cast-expression */
/* ; */
/* multiplicative-expression */
/* : cast-expression */
/* | multiplicative-expression multiplicative-operator cast-expression */
/* ; */
/* multiplicative-operator */
/* : "*" | "/" | "%" */
/* ; */
/* additive-expression */
/* : multiplicative-expression */
/* | additive-expression additive-operator multiplicative-expression */
/* ; */
/* additive-operator */
/* : "+" | "-" */
/* ; */
/* shift-expression */
/* : additive-expression */
/* | shift-expression shift-operator additive-expression */
/* ; */
/* shift-operator */
/* : "<<" | ">>" */
/* ; */
/* relational-expression */
/* : shift-expression */
/* | relational-expression relational-operator shift-expression */
/* ; */
/* relational-operator */
/* : "<" | ">" | "<=" | ">=" */
/* ; */
/* equality-expression */
/* : relational-expression */
/* | equality-expression equality-operator relational-expression */
/* ; */
/* equality-operator */
/* : "==" | "!=" */
/* ; */
/* and-expression */
/* : equality-expression */
/* | and-expression "&" equality-expression */
/* ; */
/* exclusive-or-expression */
/* : and-expression */
/* | exclusive-or-expression "^" and-expression */
/* ; */
/* inclusive-or-expression */
/* : exclusive-or-expression */
/* | inclusive-or-expression "|" exclusive-or-expression */
/* ; */
/* logical-and-expression */
/* : inclusive-or-expression */
/* | logical-and-expression "&&" inclusive-or-expression */
/* ; */
/* logical-or-expression */
/* : logical-and-expression */
/* | logical-or-expression "||" logical-and-expression */
/* ; */
/* conditional-expression */
/* : logical-or-expression */
/* | logical-or-expression "?" expression ":" conditional-expression */
/* ; */
/* assignment-expression */
/* : conditional-expression */
/* | unary-expression assignment-operator assignment-expression */
/* ; */
/* assignment-operator */
/* : "=" | "*=" | "/=" | "%=" | "+=" | "-=" | "<<=" | ">>=" | "&=" | "^=" | "|=" */
/* ; */
/* expression */
/* : assignment-expression */
/* | expression "," assignment-expression */
/* ; */
/* constant-expression */
/* : conditional-expression */
/* ; */
/* type-name */
/* : "int" */
/* ; */
%%
