%code top {
}
%code requires {
#include "list.h"
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
%define api.value.type {struct {Vector *vec; List *list;}}
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
| "++" {$$ = ast_arity0(AST_INCREMENT);}
| "--" {$$ = ast_arity0(AST_DECREMENT);}
;
argument-expression-list.opt
: %empty {AST_LIST_EMPTY($$, ARGUMENT_EXPRESSION_LIST);}
| argument-expression-list
;
argument-expression-list
: argument-expression-list.cons {AST_LIST_EXIST($$, ARGUMENT_EXPRESSION_LIST, $1);}
;
argument-expression-list.cons
: assignment-expression
| argument-expression-list.cons "," assignment-expression {AST_LIST_CONS($$, $1, $3);}
;
unary-expression
: postfix-expression
| unary-expression.prefix {$$ = ast_arity2(AST_UNARY_EXPRESSION); $$ = ast_push($$, $1);}
;
unary-expression.prefix
: "++" unary-expression {$$ = ast_arity0(AST_INCREMENT); $$ = ast_push($$, $2);}
| "--" unary-expression {$$ = ast_arity0(AST_DECREMENT); $$ = ast_push($$, $2);}
| unary-operator cast-expression {$$ = ast_push($1, $2);}
| "sizeof" unary-expression {$$ = ast_arity0(AST_SIZEOF); $$ = ast_push($$, $2);}
| "sizeof" "(" type-name ")" {$$ = ast_arity0(AST_SIZEOF); $$ = ast_push($$, $3);}
;
unary-operator
: "&" {$$ = ast_arity0(AST_AMPERSAND);}
| "*" {$$ = ast_arity0(AST_ASTERISK);};
| "+" {$$ = ast_arity0(AST_PLUS);};
| "-" {$$ = ast_arity0(AST_MINUS);};
| "~" {$$ = ast_arity0(AST_TILDE);};
| "!" {$$ = ast_arity0(AST_EXCLAMATION);};
;
cast-expression
: unary-expression
| "(" type-name ")" cast-expression {$$ = ast_append2(AST_CAST_EXPRESSION, $2, $4);}
;
multiplicative-expression
: cast-expression
| multiplicative-expression multiplicative-operator cast-expression {$$ = ast_append3(AST_MULTIPLICATIVE_EXPRESSION, $2, $1, $3);}
;
multiplicative-operator
: "*" {$$ = ast_arity0(AST_ASTERISK);}
| "/" {$$ = ast_arity0(AST_SLASH);}
| "%" {$$ = ast_arity0(AST_PERCENT);}
;
additive-expression
: multiplicative-expression
| additive-expression additive-operator multiplicative-expression {$$ = ast_append3(AST_ADDITIVE_EXPRESSION, $2, $1, $3);}
;
additive-operator
: "+" {$$ = ast_arity0(AST_PLUS);}
| "-" {$$ = ast_arity0(AST_MINUS);}
;
shift-expression
: additive-expression
| shift-expression shift-operator additive-expression {$$ = ast_append3(AST_SHIFT_EXPRESSION, $2, $1, $3);}
;
shift-operator
: "<<" {$$ = ast_arity0(AST_LEFT_SHIFT);}
| ">>" {$$ = ast_arity0(AST_RIGHT_SHIFT);}
;
relational-expression
: shift-expression
| relational-expression relational-operator shift-expression {AST_TAG($$, RELATIONAL_EXPRESSION); AST_PUSH($$, $2); AST_PUSH($$, $1); AST_PUSH($$, $3);}
;
relational-operator
: "<" {AST_TAG($$, LESS_THAN);}
| ">" {AST_TAG($$, GREATER_THAN);}
| "<=" {AST_TAG($$, LESS_EQUAL);}
| ">=" {AST_TAG($$, GREATER_EQUAL);}
;
equality-expression
: relational-expression
| equality-expression equality-operator relational-expression {AST_TAG($$, EQUALITY_EXPRESSION); AST_PUSH($$, $2); AST_PUSH($$, $1); AST_PUSH($$, $3);}
;
equality-operator
: "==" {AST_TAG($$, EQUAL);}
| "!=" {AST_TAG($$, NOT_EQUAL);}
;
and-expression
: equality-expression
| and-expression "&" equality-expression {AST_TAG($$, AND_EXPRESSION); AST_PUSH_TAG($$, AMPERSAND); AST_PUSH($$, $1); AST_PUSH($$, $3);}
;
exclusive-or-expression
: and-expression
| exclusive-or-expression "^" and-expression {AST_TAG($$, EXCLUSIVE_OR_EXPRESSION); AST_PUSH_TAG($$, CARET); AST_PUSH($$, $1); AST_PUSH($$, $3);}
;
inclusive-or-expression
: exclusive-or-expression
| inclusive-or-expression "|" exclusive-or-expression {AST_TAG($$, INCLUSIVE_OR_EXPRESSION); AST_PUSH_TAG($$, BAR); AST_PUSH($$, $1); AST_PUSH($$, $3);}
;
logical-and-expression
: inclusive-or-expression
| logical-and-expression "&&" inclusive-or-expression {AST_TAG($$, LOGICAL_AND_EXPRESSION); AST_PUSH_TAG($$, AND); AST_PUSH($$, $1); AST_PUSH($$, $3);}
;
logical-or-expression
: logical-and-expression
| logical-or-expression "||" logical-and-expression {AST_TAG($$, LOGICAL_OR_EXPRESSION); AST_PUSH_TAG($$, OR); AST_PUSH($$, $1); AST_PUSH($$, $3);}
;
conditional-expression
: logical-or-expression
| logical-or-expression "?" expression ":" conditional-expression {AST_TAG($$, CONDITIONAL_EXPRESSION); AST_PUSH($$, $1); AST_PUSH($$, $3); AST_PUSH($$, $5);}
;
assignment-expression
: conditional-expression
| unary-expression assignment-operator assignment-expression {AST_TAG($$, ASSIGNMENT_EXPRESSION); AST_PUSH($$, $2); AST_PUSH($$, $1); AST_PUSH($$, $3);}
;
assignment-operator
: "=" {AST_TAG($$, ASSIGN);}
| "*=" {AST_TAG($$, ASTERISK_ASSIGN);}
| "/=" {AST_TAG($$, SLASH_ASSIGN);}
| "%=" {AST_TAG($$, PERCENT_ASSIGN);}
| "+=" {AST_TAG($$, PLUS_ASSIGN);}
| "-=" {AST_TAG($$, MINUS_ASSIGN);}
| "<<=" {AST_TAG($$, LEFT_SHIFT_ASSIGN);}
| ">>=" {AST_TAG($$, RIGHT_SHIFT_ASSIGN);}
| "&=" {AST_TAG($$, AMPERSAND_ASSIGN);}
| "^=" {AST_TAG($$, CARET_ASSIGN);}
| "|=" {AST_TAG($$, BAR_ASSIGN);}
;
expression.opt
: %empty {AST_EMPTY($$);}
| expression
;
expression
: assignment-expression
| expression "," assignment-expression {AST_TAG($$, EXPRESSION); AST_PUSH($$, $1); AST_PUSH($$, $3);}
;

/* 6.4 Constant expressions */
constant-expression.opt
: %empty {AST_EMPTY($$);}
| constant-expression
;
constant-expression
: conditional-expression {AST_TAG($$, CONSTANT_EXPRESSION); AST_PUSH($$, $1);}
;

/* 6.5 Declarations */
declaration
: declaration-specifiers init-declarator-list.opt ";" {AST_TAG($$, DECLARATION); AST_PUSH($$, $1); AST_PUSH($$, $2);}
;
declaration-specifiers
: declaration-specifiers.cons {AST_LIST_EXIST($$, DECLARATION_SPECIFIERS, $1);}
;
declaration-specifiers.cons
: declaration-specifier
| declaration-specifiers.cons declaration-specifier {AST_LIST_CONS($$, $1, $2);}
;
declaration-specifier
: storage-class-specifier
| type-specifier
| type-qualifier
;
init-declarator-list.opt
: %empty {AST_LIST_EMPTY($$, INIT_DECLARATOR_LIST);}
| init-declarator-list
;
init-declarator-list
: init-declarator-list.cons {AST_LIST_EXIST($$, INIT_DECLARATOR_LIST, $1);}
;
init-declarator-list.cons
: init-declarator
| init-declarator-list.cons "," init-declarator {AST_LIST_CONS($$, $1, $3);}
;
init-declarator
: declarator {AST_TAG($$, INIT_DECLARATOR); AST_PUSH($$, $1); AST_PUSH_TAG($$, NIL);}
| declarator "=" initializer {AST_TAG($$, INIT_DECLARATOR); AST_PUSH($$, $1); AST_PUSH($$, $3);}
;
storage-class-specifier
: storage-class-specifier.impl {AST_TAG($$, STORAGE_CLASS_SPECIFIER); AST_PUSH($$, $1);}
;
storage-class-specifier.impl
: "typedef" {AST_TAG($$, TYPEDEF);}
| "extern" {AST_TAG($$, EXTERN);}
| "static" {AST_TAG($$, STATIC);}
| "auto" {AST_TAG($$, AUTO);}
| "register" {AST_TAG($$, REGISTER);}
;
type-specifier
: type-specifier.impl {AST_TAG($$, TYPE_SPECIFIER); AST_PUSH($$, $1);}
;
type-specifier.impl
: "void" {AST_TAG($$, VOID);}
| "char" {AST_TAG($$, CHAR);}
| "short" {AST_TAG($$, SHORT);}
| "int" {AST_TAG($$, INT);}
| "long" {AST_TAG($$, LONG);}
| "float" {AST_TAG($$, FLOAT);}
| "double" {AST_TAG($$, DOUBLE);}
| "signed" {AST_TAG($$, SIGNED);}
| "unsigned" {AST_TAG($$, UNSIGNED);}
| struct-or-union-specifier
| enum-specifier
| typedef-name
;
struct-or-union-specifier
: struct-or-union identifier.opt "{" struct-declaration-list "}" {AST_TAG($$, STRUCT_OR_UNION_SPECIFIER); AST_PUSH($$, $1); AST_PUSH($$, $2); AST_PUSH($$, $4);}
| struct-or-union identifier {AST_TAG($$, STRUCT_OR_UNION_SPECIFIER); AST_PUSH($$, $1); AST_PUSH($$, $2); AST_PUSH_TAG($$, NIL);}
;
struct-or-union
: "struct" {AST_TAG($$, STRUCT);}
| "union" {AST_TAG($$, UNION);}
;
struct-declaration-list
: struct-declaration-list.cons {AST_LIST_EXIST($$, STRUCT_DECLARATION_LIST, $1);}
;
struct-declaration-list.cons
: struct-declaration
| struct-declaration-list.cons struct-declaration {AST_LIST_CONS($$, $1, $2);}
;
struct-declaration
: specifier-qualifier-list struct-declarator-list ";" {AST_TAG($$, STRUCT_DECLARATION); AST_PUSH($$, $1); AST_PUSH($$, $2);}
;
specifier-qualifier-list
: specifier-qualifier-list.cons {AST_LIST_EXIST($$, SPECIFIER_QUALIFIER_LIST, $1);}
;
specifier-qualifier-list.cons
: specifier-qualifier
| specifier-qualifier-list.cons specifier-qualifier {AST_LIST_CONS($$, $1, $2);}
;
specifier-qualifier
: type-specifier
| type-qualifier
;
struct-declarator-list
: struct-declarator-list.cons {AST_LIST_EXIST($$, STRUCT_DECLARATOR_LIST, $1);}
;
struct-declarator-list.cons
: struct-declarator
| struct-declarator-list.cons "," struct-declarator {AST_LIST_CONS($$, $1, $3); }
;
struct-declarator
: declarator {AST_TAG($$, STRUCT_DECLARATOR); AST_PUSH($$, $1); AST_PUSH_TAG($$, NIL);}
| declarator.opt ":" constant-expression {AST_TAG($$, STRUCT_DECLARATOR); AST_PUSH($$, $1); AST_PUSH($$, $3);}
;
enum-specifier
: "enum" identifier.opt "{" enumerator-list "}" {AST_TAG($$, ENUM_SPECIFIER); AST_PUSH($$, $2); AST_PUSH($$, $4); }
| "enum" identifier {AST_TAG($$, ENUM_SPECIFIER); AST_PUSH($$, $2); AST_PUSH_TAG($$, NIL);}
;
enumerator-list
: enumerator-list.cons {AST_LIST_EXIST($$, ENUMERATOR_LIST, $1);}
;
enumerator-list.cons
: enumerator
| enumerator-list.cons "," enumerator {AST_LIST_CONS($$, $1, $3);}
;
enumerator
: enumeration-constant {AST_TAG($$, ENUMERATOR); AST_PUSH($$, $1); AST_PUSH_TAG($$, NIL);}
| enumeration-constant "=" constant-expression {AST_TAG($$, ENUMERATOR); AST_PUSH($$, $1); AST_PUSH($$, $3);}
;
type-qualifier
: type-qualifier.impl {AST_TAG($$, TYPE_QUALIFIER); AST_PUSH($$, $1);}
;
type-qualifier.impl
: "const" {AST_TAG($$, CONST);}
| "volatile" {AST_TAG($$, VOLATILE);}
;
declarator.opt
: %empty {AST_EMPTY($$);}
| declarator
;
declarator
: declarator.prefix direct-declarator {AST_TAG($$, DECLARATOR); AST_PUSH_TAG($$, NIL); AST_PUSH($$, $1); AST_PUSH($$, $2);}
| pointer declarator.prefix direct-declarator {AST_TAG($$, DECLARATOR); AST_PUSH($$, $1); AST_PUSH($$, $2); AST_PUSH($$, $3);}
;
declarator.prefix
: identifier
| "(" declarator ")" {$$ = $2;}
;
direct-declarator
: %empty {AST_LIST_EMPTY($$, DIRECT_DECLARATOR_LIST);}
| direct-declarator.cons {AST_LIST_EXIST($$, DIRECT_DECLARATOR_LIST, $1);}
;
direct-declarator.cons
: direct-declarator.suffix
| direct-declarator.cons direct-declarator.suffix {AST_LIST_CONS($$, $1, $2);}
;
direct-declarator.suffix
: direct-declarator.suffix.impl {AST_TAG($$, DIRECT_DECLARATOR); AST_PUSH($$, $1);}
;
direct-declarator.suffix.impl
: "[" constant-expression.opt "]" {AST_TAG($$, ARRAY); AST_PUSH($$, $2);}
| "(" parameter-type-list ")" {AST_TAG($$, CALL); AST_PUSH($$, $2);}
| "(" identifier-list.opt ")" {AST_TAG($$, OLD); AST_PUSH($$, $2);}
;
pointer
: pointer.cons {AST_LIST_EXIST($$, POINTER_LIST, $1);}
;
pointer.cons
: pointer.prefix
| pointer.cons pointer.prefix {AST_LIST_CONS($$, $1, $2);}
;
pointer.prefix
: "*" type-qualifier-list.opt {AST_TAG($$, POINTER); AST_PUSH($$, $2);}
;
type-qualifier-list.opt
: %empty {AST_LIST_EMPTY($$, TYPE_QUALIFIER_LIST);}
| type-qualifier-list {AST_LIST_EXIST($$, TYPE_QUALIFIER_LIST, $1);}
;
type-qualifier-list
: type-qualifier
| type-qualifier-list type-qualifier {AST_LIST_CONS($$, $1, $2);}
;
parameter-type-list.opt
: %empty {AST_LIST_EMPTY($$, PARAMETER_LIST);}
| parameter-type-list
;
parameter-type-list
: parameter-list {AST_INIT($$); AST_PUSH($$, $1); AST_PUSH_TAG($$, NIL);}
| parameter-list "," "..." {AST_INIT($$); AST_PUSH($$, $1); AST_PUSH_TAG($$, ELLIPSIS); AST_PUSH_TAG($$, NIL);}
;
parameter-list
: parameter-declaration {AST_TAG($$, LIST); AST_PUSH_TAG($$, PARAMETER_LIST); AST_PUSH($$, $1);}
| parameter-list "," parameter-declaration {AST_LIST_CONS($$, $1, $3);}
;
parameter-declaration
: declaration-specifiers parameter-declaration.suffix {AST_TAG($$, PARAMETER_DECLARATION); AST_PUSH($$, $1); AST_PUSH($$, $2);}
;
parameter-declaration.suffix
: declarator
| abstract-declarator.opt
;
identifier-list.opt
: %empty {AST_LIST_EMPTY($$, IDENTIFIER_LIST);}
| identifier-list
;
identifier-list
: identifier-list.cons {AST_LIST_EXIST($$, IDENTIFIER_LIST, $1);}
;
identifier-list.cons
: identifier
| identifier-list.cons "," identifier {AST_LIST_CONS($$, $1, $3);}
;
type-name
: specifier-qualifier-list abstract-declarator.opt {AST_TAG($$, TYPE_NAME); AST_PUSH($$, $1); AST_PUSH($$, $2);}
;
abstract-declarator.opt
: %empty {AST_EMPTY($$);}
| abstract-declarator
;
abstract-declarator
: pointer direct-abstract-declarator.opt {AST_TAG($$, ABSTRACT_DECLARATOR); AST_PUSH($$, $1); AST_PUSH($$, $2);}
| direct-abstract-declarator {AST_TAG($$, ABSTRACT_DECLARATOR); AST_PUSH_TAG($$, NIL); AST_PUSH($$, $1);}
;
direct-abstract-declarator.opt
: %empty {AST_EMPTY($$);}
| direct-abstract-declarator
;
direct-abstract-declarator
: "(" abstract-declarator ")" direct-abstract-declarator.list {AST_TAG($$, DIRECT_ABSTRACT_DECLARATOR); AST_PUSH($$, $2); AST_PUSH($$, $4);}
;
direct-abstract-declarator.list
: direct-abstract-declarator.cons {AST_LIST_EXIST($$, DIRECT_ABSTRACT_DECLARATOR_LIST, $1);}
;
direct-abstract-declarator.cons
: %empty {AST_INIT($$);}
| direct-abstract-declarator.cons direct-abstract-declarator.suffix {AST_LIST_CONS($$, $1, $2);}
;
direct-abstract-declarator.suffix
: direct-abstract-declarator.suffix.impl {AST_TAG($$, DIRECT_ABSTRACT_DECLARATOR_SUFFIX); AST_PUSH($$, $1);}
;
direct-abstract-declarator.suffix.impl
: "[" constant-expression.opt "]" {AST_TAG($$, ARRAY); AST_PUSH($$, $2);}
| "(" parameter-type-list.opt ")" {AST_TAG($$, CALL); AST_PUSH($$, $2);}
;
typedef-name
: TOKEN_TYPEDEF_NAME {AST_TAG($$, TYPEDEF_NAME); AST_PUSH($$, $1);}
;
initializer
: assignment-expression {AST_TAG($$, INITIALIZER); AST_PUSH($$, $1);}
| initializer-list {AST_TAG($$, INITIALIZER); AST_PUSH($$, $1); }
;
initializer-list
: "{" initializer-list.cons "}" {AST_LIST_EXIST($$, INITIALIZER_LIST, $2);}
| "{" initializer-list.cons "," "}" {AST_LIST_EXIST($$, INITIALIZER_LIST, $2);}
;
initializer-list.cons
: initializer
| initializer-list.cons "," initializer {AST_LIST_CONS($$, $1, $3);}
;

/* 6.6 Statements */
statement
: labeled-statement {AST_TAG($$, STATEMENT); AST_PUSH($$, $1);}
| compound-statement {AST_TAG($$, STATEMENT); AST_PUSH($$, $1);}
| expression-statement {AST_TAG($$, STATEMENT); AST_PUSH($$, $1);}
| selection-statement {AST_TAG($$, STATEMENT); AST_PUSH($$, $1);}
| iteration-statement {AST_TAG($$, STATEMENT); AST_PUSH($$, $1);}
| jump-statement {AST_TAG($$, STATEMENT); AST_PUSH($$, $1);}
;
labeled-statement
: labeled-statement.prefix ":" statement {AST_TAG($$, LABELED_STATEMENT); AST_PUSH($$, $1); AST_PUSH($$, $3);}
;
labeled-statement.prefix
: identifier {AST_TAG($$, ID); AST_PUSH_TAG($$, NIL);}
| "case" constant-expression {AST_TAG($$, CASE); AST_PUSH($$, $2);}
| "default" {AST_TAG($$, DEFAULT); AST_PUSH_TAG($$, NIL);}
;
compound-statement
: "{" declaration-list.opt statement-list.opt "}" {AST_TAG($$, COMPOUND_STATEMENT); AST_PUSH($$, $2); AST_PUSH($$, $3);}
;
declaration-list.opt
: %empty {AST_LIST_EMPTY($$, DECLARATION_LIST);}
| declaration-list
;
declaration-list
: declaration-list.cons {AST_LIST_EXIST($$, DECLARATION_LIST, $1);}
;
declaration-list.cons
: declaration
| declaration-list.cons declaration {AST_LIST_CONS($$, $1, $2);}
;
statement-list.opt
: %empty {AST_LIST_EMPTY($$, STATEMENT_LIST);}
| statement-list
;
statement-list
: statement-list.cons {AST_LIST_EXIST($$, STATEMENT_LIST, $1);}
;
statement-list.cons
: statement
| statement-list.cons statement {AST_LIST_CONS($$, $1, $2);}
;
expression-statement
: expression.opt ";" {AST_TAG($$, EXPRESSION_STATEMENT); AST_PUSH($$, $1);}
;
selection-statement
: "if" selection-statement.if {AST_TAG($$, SELECTION_STATEMENT); AST_PUSH($$, $2);}
| "switch" selection-statement.switch {AST_TAG($$, SELECTION_STATEMENT); AST_PUSH($$, $2);}
;
selection-statement.if
: "(" expression ")" statement %prec THEN {AST_TAG($$, IF); AST_PUSH($$, $2); AST_PUSH($$, $4); AST_PUSH_TAG($$, NIL);}
| "(" expression ")" statement "else" statement {AST_TAG($$, IF); AST_PUSH($$, $2); AST_PUSH($$, $4); AST_PUSH($$, $6);}
;
selection-statement.switch
: "(" expression ")" statement {AST_TAG($$, SWITCH); AST_PUSH($$, $2); AST_PUSH($$, $4); AST_PUSH_TAG($$, NIL);}
;
iteration-statement
: "while" iteration-statement.while statement {AST_TAG($$, ITERATION_STATEMENT); AST_PUSH_TAG($$, WHILE); AST_PUSH($$, $2); AST_PUSH($$, $3);}
| "do" statement iteration-statement.do {AST_TAG($$, ITERATION_STATEMENT); AST_PUSH_TAG($$, DO); AST_PUSH($$, $2); AST_PUSH($$, $3);}
| "for" iteration-statement.for statement {AST_TAG($$, ITERATION_STATEMENT); AST_PUSH_TAG($$, FOR); AST_PUSH($$, $2); AST_PUSH($$, $3);}
;
iteration-statement.while
: "(" expression ")" {$$ = $2;}
;
iteration-statement.do
: "while" "(" expression ")" ";" {$$ = $3;}
;
iteration-statement.for
: "(" expression.opt ";" expression.opt ";" expression.opt ")" {AST_TAG($$, ITERATION_STATEMENT_FOR); AST_PUSH($$, $2); AST_PUSH($$, $4); AST_PUSH($$, $6);}
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
