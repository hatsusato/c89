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
empty
: %empty { AST_APPEND0(NIL, $$); }
;
identifier
: TOKEN_IDENTIFIER { AST_NEW(IDENTIFIER, scanner, $$); }
;
floating-constant
: TOKEN_FLOATING_CONSTANT { AST_NEW(FLOATING_CONSTANT, scanner, $$); }
;
integer-constant
: TOKEN_INTEGER_CONSTANT { AST_NEW(INTEGER_CONSTANT, scanner, $$); }
;
enumeration-constant
: TOKEN_IDENTIFIER { AST_NEW(ENUMERATION_CONSTANT, scanner, $$); }
;
character-constant
: TOKEN_CHARACTER_CONSTANT { AST_NEW(CHARACTER_CONSTANT, scanner, $$); }
;
string-literal
: TOKEN_STRING_LITERAL { AST_NEW(STRING_LITERAL, scanner, $$); }
;

/* 6.3 Expressions */
primary-expression
: identifier
| floating-constant
| integer-constant
| character-constant
| string-literal
| "(" expression ")" { $$ = $2; }
;
postfix-expression
: primary-expression
| postfix-expression "[" expression "]" { AST_APPEND2(POSTFIX_ARRAY, $$, $1, $3); }
| postfix-expression "(" ")" { AST_APPEND1(POSTFIX_CALL, $$, $1); }
| postfix-expression "(" expression ")" { AST_APPEND2(POSTFIX_CALL_ARGS, $$, $1, $3); }
| postfix-expression "." identifier { AST_APPEND2(POSTFIX_MEMBER, $$, $1, $3); }
| postfix-expression "->" identifier { AST_APPEND2(POSTFIX_ARROW, $$, $1, $3); }
| postfix-expression "++" { AST_APPEND1(POSTFIX_INCR, $$, $1); }
| postfix-expression "--" { AST_APPEND1(POSTFIX_DECR, $$, $1); }
;
unary-expression
: postfix-expression
| "++" unary-expression { AST_APPEND1(UNARY_INCR, $$, $2); }
| "--" unary-expression { AST_APPEND1(UNARY_DECR, $$, $2); }
| "&" cast-expression { AST_APPEND1(UNARY_AMPER, $$, $2); }
| "*" cast-expression { AST_APPEND1(UNARY_ASTER, $$, $2); }
| "+" cast-expression { AST_APPEND1(UNARY_PLUS, $$, $2); }
| "-" cast-expression { AST_APPEND1(UNARY_MINUS, $$, $2); }
| "~" cast-expression { AST_APPEND1(UNARY_TILDE, $$, $2); }
| "!" cast-expression { AST_APPEND1(UNARY_EXCL, $$, $2); }
| "sizeof" unary-expression { AST_APPEND1(UNARY_SIZEOF, $$, $2); }
| "sizeof" "(" type-name ")" { AST_APPEND1(UNARY_SIZEOF_TYPE, $$, $3); }
;
cast-expression
: unary-expression
| "(" type-name ")" cast-expression { AST_APPEND2(CAST_EXPRESSION, $$, $2, $4); }
;
multiplicative-expression
: cast-expression
| multiplicative-expression "*" cast-expression { AST_APPEND2(MULTIPLICATIVE_ASTER, $$, $1, $3); }
| multiplicative-expression "/" cast-expression { AST_APPEND2(MULTIPLICATIVE_SLASH, $$, $1, $3); }
| multiplicative-expression "%" cast-expression { AST_APPEND2(MULTIPLICATIVE_PERC, $$, $1, $3); }
;
additive-expression
: multiplicative-expression
| additive-expression "+" multiplicative-expression { AST_APPEND2(ADDITIVE_PLUS, $$, $1, $3); }
| additive-expression "-" multiplicative-expression { AST_APPEND2(ADDITIVE_MINUS, $$, $1, $3); }
;
shift-expression
: additive-expression
| shift-expression "<<" additive-expression { AST_APPEND2(SHIFT_LEFT, $$, $1, $3); }
| shift-expression ">>" additive-expression { AST_APPEND2(SHIFT_RIGHT, $$, $1, $3); }
;
relational-expression
: shift-expression
| relational-expression "<" shift-expression { AST_APPEND2(RELATIONAL_LT, $$, $1, $3); }
| relational-expression ">" shift-expression { AST_APPEND2(RELATIONAL_GT, $$, $1, $3); }
| relational-expression "<=" shift-expression { AST_APPEND2(RELATIONAL_LE, $$, $1, $3); }
| relational-expression ">=" shift-expression { AST_APPEND2(RELATIONAL_GE, $$, $1, $3); }
;
equality-expression
: relational-expression
| equality-expression "==" relational-expression { AST_APPEND2(EQUALITY_EQ, $$, $1, $3); }
| equality-expression "!=" relational-expression { AST_APPEND2(EQUALITY_NE, $$, $1, $3); }
;
and-expression
: equality-expression
| and-expression "&" equality-expression { AST_APPEND2(AND_EXPRESSION, $$, $1, $3); }
;
exclusive-or-expression
: and-expression
| exclusive-or-expression "^" and-expression { AST_APPEND2(EXCLUSIVE_OR_EXPRESSION, $$, $1, $3); }
;
inclusive-or-expression
: exclusive-or-expression
| inclusive-or-expression "|" exclusive-or-expression { AST_APPEND2(INCLUSIVE_OR_EXPRESSION, $$, $1, $3); }
;
logical-and-expression
: inclusive-or-expression
| logical-and-expression "&&" inclusive-or-expression { AST_APPEND2(LOGICAL_AND_EXPRESSION, $$, $1, $3); }
;
logical-or-expression
: logical-and-expression
| logical-or-expression "||" logical-and-expression { AST_APPEND2(LOGICAL_OR_EXPRESSION, $$, $1, $3); }
;
conditional-expression
: logical-or-expression
| logical-or-expression "?" expression ":" conditional-expression { AST_APPEND3(CONDITIONAL_EXPRESSION, $$, $1, $3, $5); }
;
assignment-expression
: conditional-expression
| unary-expression "=" assignment-expression { AST_APPEND2(ASSIGNMENT_EXPRESSION, $$, $1, $3); }
| unary-expression "*=" assignment-expression { AST_APPEND2(ASSIGNMENT_MUL, $$, $1, $3); }
| unary-expression "/=" assignment-expression { AST_APPEND2(ASSIGNMENT_DIV, $$, $1, $3); }
| unary-expression "%=" assignment-expression { AST_APPEND2(ASSIGNMENT_MOD, $$, $1, $3); }
| unary-expression "+=" assignment-expression { AST_APPEND2(ASSIGNMENT_ADD, $$, $1, $3); }
| unary-expression "-=" assignment-expression { AST_APPEND2(ASSIGNMENT_SUB, $$, $1, $3); }
| unary-expression "<<=" assignment-expression { AST_APPEND2(ASSIGNMENT_LSH, $$, $1, $3); }
| unary-expression ">>=" assignment-expression { AST_APPEND2(ASSIGNMENT_RSH, $$, $1, $3); }
| unary-expression "&=" assignment-expression { AST_APPEND2(ASSIGNMENT_AND, $$, $1, $3); }
| unary-expression "^=" assignment-expression { AST_APPEND2(ASSIGNMENT_XOR, $$, $1, $3); }
| unary-expression "|=" assignment-expression { AST_APPEND2(ASSIGNMENT_OR, $$, $1, $3); }
;
expression
: assignment-expression
| expression "," assignment-expression { AST_APPEND2(EXPRESSION, $$, $1, $3); }
;

/* 6.4 Constant expressions */
constant-expression
: conditional-expression
;

/* 6.5 Declarations */
declaration
: declaration-specifiers ";" { AST_APPEND1(DECLARATION, $$, $1); }
| declaration-specifiers init-declarator-list ";" { AST_APPEND2(DECLARATION_INIT, $$, $1, $2); }
;
declaration-specifiers
: declaration-specifier
| declaration-specifier declaration-specifiers { AST_APPEND2(DECLARATION_SPECIFIERS, $$, $1, $2); }
;
declaration-specifier
: storage-class-specifier { AST_APPEND1(STORAGE_CLASS_SPECIFIER, $$, $1); }
| type-specifier { AST_APPEND1(TYPE_SPECIFIER, $$, $1); }
| type-qualifier { AST_APPEND1(TYPE_QUALIFIER, $$, $1); }
;
init-declarator-list
: init-declarator
| init-declarator-list "," init-declarator { AST_APPEND2(INIT_DECLARATOR_LIST, $$, $1, $3); }
;
init-declarator
: declarator
| declarator "=" initializer { AST_APPEND2(INIT_DECLARATOR, $$, $1, $3); }
;
storage-class-specifier
: "typedef" { AST_NEW(TYPEDEF, scanner, $$); }
| "extern" { AST_NEW(EXTERN, scanner, $$); }
| "static" { AST_NEW(STATIC, scanner, $$); }
| "auto" { AST_NEW(AUTO, scanner, $$); }
| "register" { AST_NEW(REGISTER, scanner, $$); }
;
type-specifier
: "void" { AST_NEW(VOID, scanner, $$); }
| "char" { AST_NEW(CHAR, scanner, $$); }
| "short" { AST_NEW(SHORT, scanner, $$); }
| "int" { AST_NEW(INT, scanner, $$); }
| "long" { AST_NEW(LONG, scanner, $$); }
| "float" { AST_NEW(FLOAT, scanner, $$); }
| "double" { AST_NEW(DOUBLE, scanner, $$); }
| "signed" { AST_NEW(SIGNED, scanner, $$); }
| "unsigned" { AST_NEW(UNSIGNED, scanner, $$); }
| struct-or-union-specifier
| enum-specifier
/* | typedef-name */
;
struct-or-union-specifier
: struct-or-union "{" struct-declaration-list "}" { AST_APPEND2(STRUCT_SPECIFIER_ANONYMOUS, $$, $1, $3); }
| struct-or-union identifier "{" struct-declaration-list "}" { AST_APPEND3(STRUCT_SPECIFIER, $$, $1, $2, $4); }
| struct-or-union identifier { AST_APPEND2(STRUCT_SPECIFIER_DECL, $$, $1, $2); }
;
struct-or-union
: "struct" { AST_NEW(STRUCT, scanner, $$); }
| "union" { AST_NEW(UNION, scanner, $$); }
;
struct-declaration-list
: struct-declaration
| struct-declaration-list struct-declaration { AST_APPEND2(STRUCT_DECLARATION_LIST, $$, $1, $2); }
;
struct-declaration
: specifier-qualifier-list struct-declarator-list ";" { AST_APPEND2(STRUCT_DECLARATION, $$, $1, $2); }
;
specifier-qualifier-list
: specifier-qualifier
| specifier-qualifier-list specifier-qualifier { AST_APPEND2(SPECIFIER_QUALIFIER_LIST, $$, $1, $2); }
;
specifier-qualifier
: type-specifier { AST_APPEND1(TYPE_SPECIFIER, $$, $1); }
| type-qualifier { AST_APPEND1(TYPE_QUALIFIER, $$, $1); }
;
struct-declarator-list
: struct-declarator
| struct-declarator-list "," struct-declarator { AST_APPEND2(STRUCT_DECLARATOR_LIST, $$, $1, $2); }
;
struct-declarator
: declarator { AST_APPEND1(STRUCT_DECLARATOR, $$, $1); }
| declarator ":" constant-expression { AST_APPEND2(STRUCT_DECLARATOR_BITFIELD, $$, $1, $2); }
| ":" constant-expression { AST_APPEND1(STRUCT_DECLARATOR_EMPTY, $$, $1); }
;
enum-specifier
: "enum" "{" enumerator-list "}" { AST_APPEND1(ENUM_SPECIFIER_ANONYMOUS, $$, $3); }
| "enum" identifier "{" enumerator-list "}" { AST_APPEND2(ENUM_SPECIFIER, $$, $2, $4); }
| "enum" identifier { AST_APPEND1(ENUM_SPECIFIER_DECL, $$, $2); }
;
enumerator-list
: enumerator
| enumerator-list "," enumerator { AST_APPEND2(ENUMERATOR_LIST, $$, $1, $3); }
;
enumerator
: enumeration-constant { AST_APPEND1(ENUMERATOR, $$, $1); }
| enumeration-constant "=" constant-expression { AST_APPEND2(ENUMERATOR_INIT, $$, $1, $3); }
;
type-qualifier
: "const" { AST_NEW(CONST, scanner, $$); }
| "volatile" { AST_NEW(VOLATILE, scanner, $$); }
;
declarator
: direct-declarator { AST_APPEND1(DECLARATOR, $$, $1); }
| pointer direct-declarator { AST_APPEND2(DECLARATOR_POINTER, $$, $1, $2); }
;
direct-declarator
: identifier { AST_APPEND1(DIRECT_DECLARATOR, $$, $1); }
| "(" declarator ")" { AST_APPEND1(DIRECT_DECLARATOR_PAREN, $$, $2); }
| direct-declarator "[" constant-expression "]" { AST_APPEND2(DIRECT_DECLARATOR_ARRAY, $$, $1, $3); }
| direct-declarator "[" "]" { AST_APPEND1(DIRECT_DECLARATOR_ARRAY_EMPTY, $$, $1); }
| direct-declarator "(" parameter-type-list ")" { AST_APPEND2(DIRECT_DECLARATOR_FUNC, $$, $1, $3); }
| direct-declarator "(" identifier-list ")" { AST_APPEND2(DIRECT_DECLARATOR_FUNC_OLD, $$, $1, $3); }
| direct-declarator "(" ")" { AST_APPEND1(DIRECT_DECLARATOR_FUNC_EMPTY, $$, $1); }
;
pointer
: "*" type-qualifier-list { AST_APPEND1(POINTER, $$, $2); }
| "*" type-qualifier-list pointer { AST_APPEND2(POINTER_LIST, $$, $2, $3); }
;
type-qualifier-list
: %empty { AST_APPEND0(TYPE_QUALIFIER_LIST_EMPTY, $$); }
| type-qualifier-list type-qualifier { AST_APPEND2(TYPE_QUALIFIER_LIST, $$, $1, $2); }
;
parameter-type-list
: parameter-list
| parameter-list "," "..." { AST_APPEND1(PARAMETER_TYPE_LIST, $$, $1); }
;
parameter-list
: parameter-declaration
| parameter-list "," parameter-declaration { AST_APPEND2(PARAMETER_LIST, $$, $1, $3); }
;
parameter-declaration
: declaration-specifiers declarator { AST_APPEND2(PARAMETER_DECLARATION_DECLARATOR, $$, $1, $2); }
/* | declaration-specifiers abstract-declarator { AST_APPEND2(PARAMETER_DECLARATION_ABSTRACT, $$, $1, $2); } */
| declaration-specifiers { AST_APPEND1(PARAMETER_DECLARATION, $$, $1); }
;
identifier-list
: identifier
| identifier-list "," identifier { AST_APPEND2(IDENTIFIER_LIST, $$, $1, $3); }
;

initializer: assignment-expression;
type-name
: "int" { AST_APPEND0(TYPE_NAME, $$); }
;
%%
