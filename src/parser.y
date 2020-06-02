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
#include "ast.h"
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
| top[lhs] expression[rhs] ";" {
  if ($rhs) {
    ast_append($lhs, $rhs);
  }
}
;
identifier
: TOKEN_IDENTIFIER { AST_NEW(AST_IDENTIFIER, scanner, $$); }
;
constant
: floating-constant
| integer-constant
/* | enumeration-constant */
| character-constant
;
floating-constant
: TOKEN_FLOATING_CONSTANT { AST_NEW(AST_FLOATING_CONSTANT, scanner, $$); }
;
integer-constant
: TOKEN_INTEGER_CONSTANT { AST_NEW(AST_INTEGER_CONSTANT, scanner, $$); }
;
/* enumeration-constant */
/* : TOKEN_IDENTIFIER */
/* ; */
character-constant
: TOKEN_CHARACTER_CONSTANT { AST_NEW(AST_CHARACTER_CONSTANT, scanner, $$); }
;
string-literal
: TOKEN_STRING_LITERAL { AST_NEW(AST_STRING_LITERAL, scanner, $$); }
;
primary-expression
: identifier
| constant
| string-literal
| "(" expression ")" { $$ = $2; }
;
postfix-expression
: primary-expression
| postfix-array
| postfix-call
| postfix-call-args
| postfix-member
| postfix-arrow
| postfix-incr
| postfix-decr
;
postfix-array
: postfix-expression "[" expression "]" { AST_APPEND2(AST_POSTFIX_ARRAY, $$, $1, $3); }
;
postfix-call
: postfix-expression "(" ")" { AST_APPEND1(AST_POSTFIX_CALL, $$, $1); }
;
postfix-call-args
: postfix-expression "(" expression ")" { AST_APPEND2(AST_POSTFIX_CALL_ARGS, $$, $1, $3); }
;
postfix-member
: postfix-expression "." identifier { AST_APPEND2(AST_POSTFIX_MEMBER, $$, $1, $3); }
;
postfix-arrow
: postfix-expression "->" identifier { AST_APPEND2(AST_POSTFIX_ARROW, $$, $1, $3); }
;
postfix-incr
: postfix-expression "++" { AST_APPEND1(AST_POSTFIX_INCR, $$, $1); }
;
postfix-decr
: postfix-expression "--" { AST_APPEND1(AST_POSTFIX_DECR, $$, $1); }
;
unary-expression
: postfix-expression
| unary-incr
| unary-decr
| unary-amper
| unary-aster
| unary-plus
| unary-minus
| unary-tilde
| unary-excl
| unary-sizeof
| unary-sizeof-type
;
unary-incr
: "++" unary-expression {
  $$ = ast_new_tag(AST_UNARY_INCR, 1);
  ast_append($$, $2);
}
;
unary-decr
: "--" unary-expression {
  $$ = ast_new_tag(AST_UNARY_DECR, 1);
  ast_append($$, $2);
}
;
unary-amper
: "&" cast-expression {
  $$ = ast_new_tag(AST_UNARY_AMPER, 1);
  ast_append($$, $2);
}
;
unary-aster
: "*" cast-expression {
  $$ = ast_new_tag(AST_UNARY_ASTER, 1);
  ast_append($$, $2);
}
;
unary-plus
: "+" cast-expression {
  $$ = ast_new_tag(AST_UNARY_PLUS, 1);
  ast_append($$, $2);
}
;
unary-minus
: "-" cast-expression {
  $$ = ast_new_tag(AST_UNARY_MINUS, 1);
  ast_append($$, $2);
}
;
unary-tilde
: "~" cast-expression {
  $$ = ast_new_tag(AST_UNARY_TILDE, 1);
  ast_append($$, $2);
}
;
unary-excl
: "!" cast-expression {
  $$ = ast_new_tag(AST_UNARY_EXCL, 1);
  ast_append($$, $2);
}
;
unary-sizeof
: "sizeof" unary-expression {
  $$ = ast_new_tag(AST_UNARY_SIZEOF, 1);
  ast_append($$, $2);
}
;
unary-sizeof-type
: "sizeof" "(" type-name ")" {
  $$ = ast_new_tag(AST_UNARY_SIZEOF_TYPE, 1);
  ast_append($$, $3);
}
;
cast-expression
: unary-expression
| "(" type-name ")" cast-expression {
  $$ = ast_new_tag(AST_CAST_EXPRESSION, 2);
  ast_append($$, $2);
  ast_append($$, $4);
}
;
multiplicative-expression
: cast-expression
| multiplicative-aster
| multiplicative-slash
| multiplicative-perc
;
multiplicative-aster
: multiplicative-expression "*" cast-expression {
  $$ = ast_new_tag(AST_MULTIPLICATIVE_ASTER, 2);
  ast_append($$, $1);
  ast_append($$, $3);
}
;
multiplicative-slash
: multiplicative-expression "/" cast-expression {
  $$ = ast_new_tag(AST_MULTIPLICATIVE_SLASH, 2);
  ast_append($$, $1);
  ast_append($$, $3);
}
;
multiplicative-perc
: multiplicative-expression "%" cast-expression {
  $$ = ast_new_tag(AST_MULTIPLICATIVE_PERC, 2);
  ast_append($$, $1);
  ast_append($$, $3);
}
;
additive-expression
: multiplicative-expression
| additive-plus
| additive-minus
;
additive-plus
: additive-expression "+" multiplicative-expression {
  $$ = ast_new_tag(AST_ADDITIVE_PLUS, 2);
  ast_append($$, $1);
  ast_append($$, $3);
}
;
additive-minus
: additive-expression "-" multiplicative-expression {
  $$ = ast_new_tag(AST_ADDITIVE_MINUS, 2);
  ast_append($$, $1);
  ast_append($$, $3);
}
;
shift-expression
: additive-expression
| shift-left
| shift-right
;
shift-left
: shift-expression "<<" additive-expression {
  $$ = ast_new_tag(AST_SHIFT_LEFT, 2);
  ast_append($$, $1);
  ast_append($$, $3);
}
;
shift-right
: shift-expression ">>" additive-expression {
  $$ = ast_new_tag(AST_SHIFT_RIGHT, 2);
  ast_append($$, $1);
  ast_append($$, $3);
}
;
type-name
: "int" {
  $$ = ast_new_tag(AST_TYPE_NAME, 0);
}
;
expression
: shift-expression
;
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
%%
