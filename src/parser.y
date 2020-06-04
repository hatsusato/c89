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
| top[lhs] declaration[rhs] {
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

/* 6.3 Expressions */
primary-expression
: identifier
| constant
| string-literal
| "(" expression ")" { $$ = $2; }
;
postfix-expression
: primary-expression
| postfix-expression "[" expression "]" { AST_APPEND2(AST_POSTFIX_ARRAY, $$, $1, $3); }
| postfix-expression "(" ")" { AST_APPEND1(AST_POSTFIX_CALL, $$, $1); }
| postfix-expression "(" expression ")" { AST_APPEND2(AST_POSTFIX_CALL_ARGS, $$, $1, $3); }
| postfix-expression "." identifier { AST_APPEND2(AST_POSTFIX_MEMBER, $$, $1, $3); }
| postfix-expression "->" identifier { AST_APPEND2(AST_POSTFIX_ARROW, $$, $1, $3); }
| postfix-expression "++" { AST_APPEND1(AST_POSTFIX_INCR, $$, $1); }
| postfix-expression "--" { AST_APPEND1(AST_POSTFIX_DECR, $$, $1); }
;
unary-expression
: postfix-expression
| "++" unary-expression { AST_APPEND1(AST_UNARY_INCR, $$, $2); }
| "--" unary-expression { AST_APPEND1(AST_UNARY_DECR, $$, $2); }
| "&" cast-expression { AST_APPEND1(AST_UNARY_AMPER, $$, $2); }
| "*" cast-expression { AST_APPEND1(AST_UNARY_ASTER, $$, $2); }
| "+" cast-expression { AST_APPEND1(AST_UNARY_PLUS, $$, $2); }
| "-" cast-expression { AST_APPEND1(AST_UNARY_MINUS, $$, $2); }
| "~" cast-expression { AST_APPEND1(AST_UNARY_TILDE, $$, $2); }
| "!" cast-expression { AST_APPEND1(AST_UNARY_EXCL, $$, $2); }
| "sizeof" unary-expression { AST_APPEND1(AST_UNARY_SIZEOF, $$, $2); }
| "sizeof" "(" type-name ")" { AST_APPEND1(AST_UNARY_SIZEOF_TYPE, $$, $3); }
;
cast-expression
: unary-expression
| "(" type-name ")" cast-expression { AST_APPEND2(AST_CAST_EXPRESSION, $$, $2, $4); }
;
multiplicative-expression
: cast-expression
| multiplicative-expression "*" cast-expression { AST_APPEND2(AST_MULTIPLICATIVE_ASTER, $$, $1, $3); }
| multiplicative-expression "/" cast-expression { AST_APPEND2(AST_MULTIPLICATIVE_SLASH, $$, $1, $3); }
| multiplicative-expression "%" cast-expression { AST_APPEND2(AST_MULTIPLICATIVE_PERC, $$, $1, $3); }
;
additive-expression
: multiplicative-expression
| additive-expression "+" multiplicative-expression { AST_APPEND2(AST_ADDITIVE_PLUS, $$, $1, $3); }
| additive-expression "-" multiplicative-expression { AST_APPEND2(AST_ADDITIVE_MINUS, $$, $1, $3); }
;
shift-expression
: additive-expression
| shift-expression "<<" additive-expression { AST_APPEND2(AST_SHIFT_LEFT, $$, $1, $3); }
| shift-expression ">>" additive-expression { AST_APPEND2(AST_SHIFT_RIGHT, $$, $1, $3); }
;
relational-expression
: shift-expression
| relational-expression "<" shift-expression { AST_APPEND2(AST_RELATIONAL_LT, $$, $1, $3); }
| relational-expression ">" shift-expression { AST_APPEND2(AST_RELATIONAL_GT, $$, $1, $3); }
| relational-expression "<=" shift-expression { AST_APPEND2(AST_RELATIONAL_LE, $$, $1, $3); }
| relational-expression ">=" shift-expression { AST_APPEND2(AST_RELATIONAL_GE, $$, $1, $3); }
;
equality-expression
: relational-expression
| equality-expression "==" relational-expression { AST_APPEND2(AST_EQUALITY_EQ, $$, $1, $3); }
| equality-expression "!=" relational-expression { AST_APPEND2(AST_EQUALITY_NE, $$, $1, $3); }
;
and-expression
: equality-expression
| and-expression "&" equality-expression { AST_APPEND2(AST_AND_EXPRESSION, $$, $1, $3); }
;
exclusive-or-expression
: and-expression
| exclusive-or-expression "^" and-expression { AST_APPEND2(AST_EXCLUSIVE_OR_EXPRESSION, $$, $1, $3); }
;
inclusive-or-expression
: exclusive-or-expression
| inclusive-or-expression "|" exclusive-or-expression { AST_APPEND2(AST_INCLUSIVE_OR_EXPRESSION, $$, $1, $3); }
;
logical-and-expression
: inclusive-or-expression
| logical-and-expression "&&" inclusive-or-expression { AST_APPEND2(AST_LOGICAL_AND_EXPRESSION, $$, $1, $3); }
;
logical-or-expression
: logical-and-expression
| logical-or-expression "||" logical-and-expression { AST_APPEND2(AST_LOGICAL_OR_EXPRESSION, $$, $1, $3); }
;
conditional-expression
: logical-or-expression
| logical-or-expression "?" expression ":" conditional-expression { AST_APPEND3(AST_CONDITIONAL_EXPRESSION, $$, $1, $3, $5); }
;
assignment-expression
: conditional-expression
| unary-expression "=" assignment-expression { AST_APPEND2(AST_ASSIGNMENT_EXPRESSION, $$, $1, $3); }
| unary-expression "*=" assignment-expression { AST_APPEND2(AST_ASSIGNMENT_MUL, $$, $1, $3); }
| unary-expression "/=" assignment-expression { AST_APPEND2(AST_ASSIGNMENT_DIV, $$, $1, $3); }
| unary-expression "%=" assignment-expression { AST_APPEND2(AST_ASSIGNMENT_MOD, $$, $1, $3); }
| unary-expression "+=" assignment-expression { AST_APPEND2(AST_ASSIGNMENT_ADD, $$, $1, $3); }
| unary-expression "-=" assignment-expression { AST_APPEND2(AST_ASSIGNMENT_SUB, $$, $1, $3); }
| unary-expression "<<=" assignment-expression { AST_APPEND2(AST_ASSIGNMENT_LSH, $$, $1, $3); }
| unary-expression ">>=" assignment-expression { AST_APPEND2(AST_ASSIGNMENT_RSH, $$, $1, $3); }
| unary-expression "&=" assignment-expression { AST_APPEND2(AST_ASSIGNMENT_AND, $$, $1, $3); }
| unary-expression "^=" assignment-expression { AST_APPEND2(AST_ASSIGNMENT_XOR, $$, $1, $3); }
| unary-expression "|=" assignment-expression { AST_APPEND2(AST_ASSIGNMENT_OR, $$, $1, $3); }
;
expression
: assignment-expression
| expression "," assignment-expression { AST_APPEND2(AST_EXPRESSION, $$, $1, $3); }
;

/* 6.4 Constant expressions */
constant-expression
: conditional-expression
;

/* 6.5 Declarations */
declaration
: declaration-specifiers ";" { AST_APPEND1(AST_DECLARATION, $$, $1); }
| declaration-specifiers init-declarator-list ";" { AST_APPEND2(AST_DECLARATION_INIT, $$, $1, $2); }
;
declaration-specifiers
: declaration-specifier
| declaration-specifier declaration-specifiers { AST_APPEND2(AST_DECLARATION_SPECIFIERS, $$, $1, $2); }
;
declaration-specifier
: storage-class-specifier { AST_APPEND1(AST_STORAGE_CLASS_SPECIFIER, $$, $1); }
/* | type-specifier */
/* | type-qualifier */
;
init-declarator-list
: init-declarator
| init-declarator-list "," init-declarator { AST_APPEND2(AST_INIT_DECLARATOR_LIST, $$, $1, $3); }
;
init-declarator
: declarator
| declarator "=" initializer { AST_APPEND2(AST_INIT_DECLARATOR, $$, $1, $3); }
;
storage-class-specifier
: "typedef" { AST_NEW(AST_TYPEDEF, scanner, $$); }
| "extern" { AST_NEW(AST_EXTERN, scanner, $$); }
| "static" { AST_NEW(AST_STATIC, scanner, $$); }
| "auto" { AST_NEW(AST_AUTO, scanner, $$); }
| "register" { AST_NEW(AST_REGISTER, scanner, $$); }
;

declarator: identifier;
initializer: assignment-expression;
type-name
: "int" { AST_APPEND0(AST_TYPE_NAME, $$); }
;
%%
