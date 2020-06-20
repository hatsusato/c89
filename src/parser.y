%code top {
}
%code requires {
#include "list.h"
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
%define api.value.type {struct {List *list; List *last;}}
%param {yyscan_t scanner}

%token TOKEN_IDENTIFIER
%token TOKEN_FLOATING_CONSTANT
%token TOKEN_INTEGER_CONSTANT
%token TOKEN_CHARACTER_CONSTANT
%token TOKEN_STRING_LITERAL
%token TOKEN_TYPEDEF_NAME
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

%nonassoc THEN
%nonassoc "else"

%start top
%%
/* 6.1 Lexical elements */
identifier.opt
: %empty {AST_EMPTY($$);}
| identifier
;
identifier
: TOKEN_IDENTIFIER {$$ = ast_new_token(AST_IDENTIFIER, scanner);}
;
floating-constant
: TOKEN_FLOATING_CONSTANT {$$ = ast_new_token(AST_FLOATING_CONSTANT, scanner);}
;
integer-constant
: TOKEN_INTEGER_CONSTANT {$$ = ast_new_token(AST_INTEGER_CONSTANT, scanner);}
;
enumeration-constant
: TOKEN_IDENTIFIER {$$ = ast_new_token(AST_ENUMERATION_CONSTANT, scanner);}
;
character-constant
: TOKEN_CHARACTER_CONSTANT {$$ = ast_new_token(AST_CHARACTER_CONSTANT, scanner);}
;
string-literal
: TOKEN_STRING_LITERAL {$$ = ast_new_token(AST_STRING_LITERAL, scanner);}
;

/* 6.3 Expressions */
primary-expression
: primary-expression.suffix {$$ = ast_append1(AST_PRIMARY_EXPRESSION, $1);}
;
primary-expression.suffix
: identifier
| floating-constant
| integer-constant
| character-constant
| string-literal
| "(" expression ")" {$$ = $2;}
;
postfix-expression
: primary-expression
| postfix-expression postfix-expression.suffix {$$ = ast_append2(AST_POSTFIX_EXPRESSION, $1, $2);}
;
postfix-expression.suffix
: "[" expression "]" {$$ = ast_append1(AST_ARRAY, $2);}
| "(" argument-expression-list.opt ")" {$$ = ast_append1(AST_CALL, $2);}
| "." identifier {$$ = ast_append1(AST_PERIOD, $2);}
| "->" identifier {$$ = ast_append1(AST_ARROW, $2);}
| "++" {$$ = ast_append0(AST_INCREMENT);}
| "--" {$$ = ast_append0(AST_DECREMENT);}
;
argument-expression-list.opt
: %empty {$$ = ast_list_empty(AST_ARGUMENT_EXPRESSION_LIST);}
| argument-expression-list
;
argument-expression-list
: assignment-expression {$$ = ast_list_new(AST_ARGUMENT_EXPRESSION_LIST, $1);}
| argument-expression-list "," assignment-expression {$$ = ast_list_push($1, $3);}
;
unary-expression
: postfix-expression
| unary-expression.prefix unary-expression {$$ = ast_append2(AST_UNARY_EXPRESSION, $1, $2);}
| "sizeof" unary-expression {$$ = ast_append2(AST_UNARY_EXPRESSION, ast_append0(AST_SIZEOF), $2);}
| "sizeof" "(" type-name ")" {$$ = ast_append1(AST_UNARY_EXPRESSION, ast_append1(AST_SIZEOF, $3));}
| unary-operator cast-expression {$$ = ast_append2(AST_UNARY_EXPRESSION, $1, $2);}
;
unary-expression.prefix
: "++" {$$ = ast_append0(AST_INCREMENT);}
| "--" {$$ = ast_append0(AST_DECREMENT);}
;
unary-operator
: "&" {$$ = ast_append0(AST_AMPERSAND);}
| "*" {$$ = ast_append0(AST_ASTERISK);};
| "+" {$$ = ast_append0(AST_PLUS);};
| "-" {$$ = ast_append0(AST_MINUS);};
| "~" {$$ = ast_append0(AST_TILDE);};
| "!" {$$ = ast_append0(AST_EXCLAMATION);};
;
cast-expression
: unary-expression
| "(" type-name ")" cast-expression {$$ = ast_append2(AST_CAST_EXPRESSION, $2, $4);}
;
multiplicative-expression
: cast-expression
| multiplicative-expression multiplicative-operator cast-expression {$$ = ast_binary($1, $2, $3);}
;
multiplicative-operator
: "*" {$$ = ast_append0(AST_ASTERISK);}
| "/" {$$ = ast_append0(AST_SLASH);}
| "%" {$$ = ast_append0(AST_PERCENT);}
;
additive-expression
: multiplicative-expression
| additive-expression additive-operator multiplicative-expression {$$ = ast_binary($1, $2, $3);}
;
additive-operator
: "+" {$$ = ast_append0(AST_PLUS);}
| "-" {$$ = ast_append0(AST_MINUS);}
;
shift-expression
: additive-expression
| shift-expression shift-operator additive-expression {$$ = ast_binary($1, $2, $3);}
;
shift-operator
: "<<" {$$ = ast_append0(AST_LEFT_SHIFT);}
| ">>" {$$ = ast_append0(AST_RIGHT_SHIFT);}
;
relational-expression
: shift-expression
| relational-expression relational-operator shift-expression {$$ = ast_binary($1, $2, $3);}
;
relational-operator
: "<" {$$ = ast_append0(AST_LESS_THAN);}
| ">" {$$ = ast_append0(AST_GREATER_THAN);}
| "<=" {$$ = ast_append0(AST_LESS_EQUAL);}
| ">=" {$$ = ast_append0(AST_GREATER_EQUAL);}
;
equality-expression
: relational-expression
| equality-expression equality-operator relational-expression {$$ = ast_binary($1, $2, $3);}
;
equality-operator
: "==" {$$ = ast_append0(AST_EQUAL);}
| "!=" {$$ = ast_append0(AST_NOT_EQUAL);}
;
and-expression
: equality-expression
| and-expression and-operator equality-expression {$$ = ast_binary($1, $2, $3);}
;
and-operator
: "&" {$$ = ast_append0(AST_AMPERSAND);}
;
exclusive-or-expression
: and-expression
| exclusive-or-expression exclusive-or-operator and-expression {$$ = ast_binary($1, $2, $3);}
;
exclusive-or-operator
: "^" {$$ = ast_append0(AST_CARET);}
;
inclusive-or-expression
: exclusive-or-expression
| inclusive-or-expression inclusive-or-operator exclusive-or-expression {$$ = ast_binary($1, $2, $3);}
;
inclusive-or-operator
: "|" {$$ = ast_append0(AST_BAR);}
;
logical-and-expression
: inclusive-or-expression
| logical-and-expression logical-and-operator inclusive-or-expression {$$ = ast_binary($1, $2, $3);}
;
logical-and-operator
: "&&" {$$ = ast_append0(AST_AND);}
;
logical-or-expression
: logical-and-expression
| logical-or-expression logical-or-operator logical-and-expression {$$ = ast_binary($1, $2, $3);}
;
logical-or-operator
: "||" {$$ = ast_append0(AST_OR);}
;
conditional-expression
: logical-or-expression
| logical-or-expression "?" expression ":" conditional-expression {$$ = ast_append3(AST_CONDITIONAL_EXPRESSION, $1, $3, $5);}
;
assignment-expression
: conditional-expression
| unary-expression assignment-operator assignment-expression {$$ = ast_binary($1, $2, $3);}
;
assignment-operator
: "=" {$$ = ast_append0(AST_ASSIGN);}
| "*=" {$$ = ast_append0(AST_ASTERISK_ASSIGN);}
| "/=" {$$ = ast_append0(AST_SLASH_ASSIGN);}
| "%=" {$$ = ast_append0(AST_PERCENT_ASSIGN);}
| "+=" {$$ = ast_append0(AST_PLUS_ASSIGN);}
| "-=" {$$ = ast_append0(AST_MINUS_ASSIGN);}
| "<<=" {$$ = ast_append0(AST_LEFT_SHIFT_ASSIGN);}
| ">>=" {$$ = ast_append0(AST_RIGHT_SHIFT_ASSIGN);}
| "&=" {$$ = ast_append0(AST_AMPERSAND_ASSIGN);}
| "^=" {$$ = ast_append0(AST_CARET_ASSIGN);}
| "|=" {$$ = ast_append0(AST_BAR_ASSIGN);}
;
expression.opt
: %empty {$$ = ast_append0(AST_NIL);}
| expression
;
expression
: assignment-expression
| expression comma-operator assignment-expression {$$ = ast_binary($1, $2, $3);}
;
comma-operator
: "," {$$ = ast_append0(AST_COMMA);}
;

/* 6.4 Constant expressions */
constant-expression.opt
: %empty {$$ = ast_append0(AST_NIL);}
| constant-expression
;
constant-expression
: conditional-expression {$$ = ast_append1(AST_CONSTANT_EXPRESSION, $1);}
;

/* 6.5 Declarations */
declaration
: declaration-specifiers ";" {$$ = ast_append1(AST_DECLARATION, $1);}
| declaration-specifiers init-declarator-list ";" {$$ = ast_append2(AST_DECLARATION, $1, $2);}
;
declaration-specifiers
: declaration-specifier {$$ = ast_list_new(AST_DECLARATION_SPECIFIERS, $1);}
| declaration-specifiers declaration-specifier {$$ = ast_list_push($1, $2);}
;
declaration-specifier
: storage-class-specifier
| type-specifier
| type-qualifier
;
init-declarator-list
: init-declarator {$$ = ast_list_new(AST_INIT_DECLARATOR_LIST, $1);}
| init-declarator-list "," init-declarator {$$ = ast_list_push($1, $3);}
;
init-declarator
: declarator {$$ = ast_append1(AST_INIT_DECLARATOR, $1);}
| declarator "=" initializer {$$ = ast_append2(AST_INIT_DECLARATOR, $1, $3);}
;
storage-class-specifier
: storage-class-specifier.prefix {$$ = ast_append1(AST_STORAGE_CLASS_SPECIFIER, $1);}
;
storage-class-specifier.prefix
: "typedef" {$$ = ast_append0(AST_TYPEDEF);}
| "extern" {$$ = ast_append0(AST_EXTERN);}
| "static" {$$ = ast_append0(AST_STATIC);}
| "auto" {$$ = ast_append0(AST_AUTO);}
| "register" {$$ = ast_append0(AST_REGISTER);}
;
type-specifier
: type-specifier.prefix {$$ = ast_append1(AST_TYPE_SPECIFIER, $1);}
;
type-specifier.prefix
: "void" {$$ = ast_append0(AST_VOID);}
| "char" {$$ = ast_append0(AST_CHAR);}
| "short" {$$ = ast_append0(AST_SHORT);}
| "int" {$$ = ast_append0(AST_INT);}
| "long" {$$ = ast_append0(AST_LONG);}
| "float" {$$ = ast_append0(AST_FLOAT);}
| "double" {$$ = ast_append0(AST_DOUBLE);}
| "signed" {$$ = ast_append0(AST_SIGNED);}
| "unsigned" {$$ = ast_append0(AST_UNSIGNED);}
| struct-or-union-specifier
| enum-specifier
| typedef-name
;
struct-or-union-specifier
: struct-or-union identifier.opt "{" struct-declaration-list "}" {$$ = ast_append3(AST_STRUCT_OR_UNION_SPECIFIER, $1, $2, $4);}
| struct-or-union identifier {$$ = ast_append2(AST_STRUCT_OR_UNION_SPECIFIER, $1, $2);}
;
struct-or-union
: "struct" {$$ = ast_append0(AST_STRUCT);}
| "union" {$$ = ast_append0(AST_UNION);}
;
struct-declaration-list
: struct-declaration {$$ = ast_list_new(AST_STRUCT_DECLARATION_LIST, $1);}
| struct-declaration-list struct-declaration {$$ = ast_list_push($1, $2);}
;
struct-declaration
: specifier-qualifier-list struct-declarator-list ";" {$$ = ast_append2(AST_STRUCT_DECLARATION, $1, $2);}
;
specifier-qualifier-list
: specifier-qualifier {$$ = ast_list_new(AST_SPECIFIER_QUALIFIER_LIST, $1);}
| specifier-qualifier-list specifier-qualifier {$$ = ast_list_push($1, $2);}
;
specifier-qualifier
: type-specifier
| type-qualifier
;
struct-declarator-list
: struct-declarator {$$ = ast_list_new(AST_STRUCT_DECLARATOR_LIST, $1);}
| struct-declarator-list "," struct-declarator {$$ = ast_list_push($1, $3);}
;
struct-declarator
: declarator {$$ = ast_append1(AST_STRUCT_DECLARATOR, $1);}
| declarator.opt ":" constant-expression {$$ = ast_append2(AST_STRUCT_DECLARATOR, $1, $3);}
;
enum-specifier
: "enum" identifier.opt "{" enumerator-list "}" {$$ = ast_append2(AST_ENUM_SPECIFIER, $2, $4); }
| "enum" identifier {$$ = ast_append1(AST_ENUM_SPECIFIER, $2); }
;
enumerator-list
: enumerator {$$ = ast_list_new(AST_ENUMERATOR_LIST, $1);}
| enumerator-list "," enumerator {$$ = ast_list_push($1, $3);}
;
enumerator
: enumeration-constant {$$ = ast_append1(AST_ENUMERATOR, $1);}
| enumeration-constant "=" constant-expression {$$ = ast_append2(AST_ENUMERATOR, $1, $3);}
;
type-qualifier
: type-qualifier.prefix {$$ = ast_append1(AST_TYPE_QUALIFIER, $1);}
;
type-qualifier.prefix
: "const" {$$ = ast_append0(AST_CONST);}
| "volatile" {$$ = ast_append0(AST_VOLATILE);}
;
declarator.opt
: %empty {AST_EMPTY($$);}
| declarator
;
declarator
: direct-declarator {$$ = ast_append1(AST_DECLARATOR, $1);}
| pointer direct-declarator {$$ = ast_append2(AST_DECLARATOR, $1, $2);}
;
direct-declarator
: direct-declarator.prefix {$$ = ast_append1(AST_DIRECT_DECLARATOR, $1);}
| direct-declarator direct-declarator.suffix {$$ = ast_append2(AST_DIRECT_DECLARATOR, $1, $2);}
;
direct-declarator.prefix
: identifier
| "(" declarator ")" {$$ = $2;}
;
direct-declarator.suffix
: "[" constant-expression.opt "]" {$$ = ast_append1(AST_ARRAY, $2);}
| "(" parameter-type-list ")" {$$ = ast_append1(AST_CALL, $2);}
| "(" identifier-list.opt ")" {$$ = ast_append1(AST_OLD, $2);}
;
pointer
: pointer.prefix {$$ = ast_append1(AST_POINTER, $1);}
| pointer.prefix pointer {$$ = ast_append2(AST_POINTER, $1, $2);}
;
pointer.prefix
: "*" type-qualifier-list.opt {$$ = $2;}
;
type-qualifier-list.opt
: %empty {$$ = ast_list_empty(AST_TYPE_QUALIFIER_LIST);}
| type-qualifier-list
;
type-qualifier-list
: type-qualifier {$$ = ast_list_new(AST_TYPE_QUALIFIER_LIST, $1);}
| type-qualifier-list type-qualifier {$$ = ast_list_push($1, $2);}
;
parameter-type-list.opt
: %empty {$$ = ast_list_empty(AST_PARAMETER_LIST);}
| parameter-type-list
;
parameter-type-list
: parameter-list
| parameter-list "," "..." {$$ = ast_append1(AST_PARAMETER_TYPE_LIST, $1);}
;
parameter-list
: parameter-declaration {$$ = ast_list_new(AST_PARAMETER_LIST, $1);}
| parameter-list "," parameter-declaration {$$ = ast_list_push($1, $3);}
;
parameter-declaration
: declaration-specifiers {$$ = ast_append1(AST_PARAMETER_DECLARATION, $1);}
| declaration-specifiers parameter-declaration.suffix {$$ = ast_append2(AST_PARAMETER_DECLARATION, $1, $2);}
;
parameter-declaration.suffix
: declarator
| abstract-declarator
;
identifier-list.opt
: %empty {$$ = ast_list_empty(AST_IDENTIFIER_LIST);}
| identifier-list
;
identifier-list
: identifier {$$ = ast_list_new(AST_IDENTIFIER_LIST, $1);}
| identifier-list "," identifier {$$ = ast_list_push($1, $3);}
;
type-name
: specifier-qualifier-list {$$ = ast_append1(AST_TYPE_NAME, $1);}
| specifier-qualifier-list abstract-declarator {$$ = ast_append2(AST_TYPE_NAME, $1, $2);}
;
abstract-declarator
: abstract-declarator.prefix {$$ = ast_append1(AST_ABSTRACT_DECLARATOR, $1);}
| pointer direct-abstract-declarator {$$ = ast_append2(AST_ABSTRACT_DECLARATOR, $1, $2);}
;
abstract-declarator.prefix
: pointer
| direct-abstract-declarator
;
direct-abstract-declarator
: direct-abstract-declarator.prefix {$$ = ast_append1(AST_DIRECT_ABSTRACT_DECLARATOR, $1);}
| direct-abstract-declarator direct-abstract-declarator.suffix {$$ = ast_append2(AST_DIRECT_ABSTRACT_DECLARATOR, $1, $2);}
;
direct-abstract-declarator.prefix
: "(" abstract-declarator ")" {$$ = $2;}
| direct-abstract-declarator.suffix {$$ = $1;}
;
direct-abstract-declarator.suffix
: "[" constant-expression.opt "]" {$$ = ast_append1(AST_ARRAY, $2);}
| "(" parameter-type-list.opt ")" {$$ = ast_append1(AST_CALL, $2);}
;
typedef-name
: TOKEN_TYPEDEF_NAME {$$ = ast_append1(AST_TYPEDEF_NAME, $1);}
;
initializer
: initializer.suffix {$$ = ast_append1(AST_INITIALIZER, $1);}
;
initializer.suffix
: assignment-expression
| "{" initializer-list "}" {$$ = $2;}
| "{" initializer-list "," "}" {$$ = $2;}
;
initializer-list
: initializer {$$ = ast_list_new(AST_INITIALIZER_LIST, $1);}
| initializer-list "," initializer {$$ = ast_list_push($1, $3);}
;

/* 6.6 Statements */
statement
: statement.prefix {$$ = ast_append1(AST_STATEMENT, $1);}
;
statement.prefix
: labeled-statement
| compound-statement
| expression-statement
| selection-statement
| iteration-statement
| jump-statement
;
labeled-statement
: labeled-statement.prefix ":" statement {$$ = ast_append2(AST_LABELED_STATEMENT, $1, $3);}
;
labeled-statement.prefix
: identifier
| "case" constant-expression {$$ = ast_append1(AST_CASE, $2);}
| "default" {$$ = ast_append0(AST_DEFAULT);}
;
compound-statement
: "{" declaration-list.opt statement-list.opt "}" {$$ = ast_append2(AST_COMPOUND_STATEMENT, $2, $3);}
;
declaration-list.opt
: %empty {$$ = ast_list_empty(AST_DECLARATION_LIST);}
| declaration-list
;
declaration-list
: declaration {$$ = ast_list_new(AST_DECLARATION_LIST, $1);}
| declaration-list declaration {$$ = ast_list_push($1, $2);}
;
statement-list.opt
: %empty {$$ = ast_list_empty(AST_STATEMENT_LIST);}
| statement-list
;
statement-list
: statement {$$ = ast_list_new(AST_STATEMENT_LIST, $1);}
| statement-list statement {$$ = ast_list_push($1, $2);}
;
expression-statement
: expression.opt ";" {$$ = ast_append1(AST_EXPRESSION_STATEMENT, $1);}
;
selection-statement
: selection-statement.suffix {$$ = ast_append1(AST_SELECTION_STATEMENT, $1);}
;
selection-statement.suffix
: "if" selection-statement.if {$$ = $2;}
| "switch" selection-statement.switch {$$ = $2;}
;
selection-statement.if
: "(" expression ")" statement %prec THEN {$$ = ast_append2(AST_IF, $2, $4);}
| "(" expression ")" statement "else" statement {$$ = ast_append3(AST_IF, $2, $4, $6);}
;
selection-statement.switch
: "(" expression ")" statement {$$ = ast_append2(AST_SWITCH, $2, $4);}
;
iteration-statement
: iteration-statement.suffix {$$ = ast_append1(AST_ITERATION_STATEMENT, $1);}
;
iteration-statement.suffix
: "while" iteration-statement.while {$$ = $2;}
| "do" iteration-statement.do {$$ = $2;}
| "for" iteration-statement.for {$$ = $2;}
;
iteration-statement.while
: "(" expression ")" statement {$$ = ast_append2(AST_WHILE, $2, $4);}
;
iteration-statement.do
: statement "while" "(" expression ")" ";" {$$ = ast_append2(AST_DO, $1, $4);}
;
iteration-statement.for
: "(" expression.opt ";" expression.opt ";" expression.opt ")" statement {$$ = ast_append4(AST_FOR, $2, $4, $6, $8);}
;
jump-statement
: jump-statement.impl {AST_TAG($$, JUMP_STATEMENT); AST_PUSH($$, $1);}
;
jump-statement.impl
: "goto" identifier ";" {AST_TAG($$, GOTO); AST_PUSH($$, $2);}
| "continue" ";" {AST_TAG($$, CONTINUE); AST_PUSH_TAG($$, NIL);}
| "break" ";" {AST_TAG($$, BREAK); AST_PUSH_TAG($$, NIL);}
| "return" expression.opt ";" {AST_TAG($$, RETURN); AST_PUSH($$, $2);}
;

/* 6.7 External definitions */
top
: translation-unit {AST_LIST_EXIST($$, TRANSLATION_UNIT, $1); yyset_extra($$, scanner);}
translation-unit
: external-declaration
| translation-unit external-declaration {AST_LIST_CONS($$, $1, $2);}
;
external-declaration
: function-definition
| declaration {AST_TAG($$, EXTERNAL_DECLARATION); AST_PUSH($$, $1);}
;
function-definition
: declarator declaration-list.opt compound-statement {AST_TAG($$, FUNCTION_DEFINITION); AST_PUSH_TAG($$, NIL); AST_PUSH($$, $1); AST_PUSH($$, $2); AST_PUSH($$, $3);}
| declaration-specifiers declarator declaration-list.opt compound-statement {AST_TAG($$, FUNCTION_DEFINITION); AST_PUSH($$, $1); AST_PUSH($$, $2); AST_PUSH($$, $3); AST_PUSH($$, $4);}
;
%%
