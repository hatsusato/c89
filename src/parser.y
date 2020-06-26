%code top {
}
%code requires {
#include "ast.h"
#include "scanner.h"
}

%define api.pure full
%define api.value.type {AstList}
%param {yyscan_t scanner}

%code provides {
#include "lexer.h"
#include "parser.h"
#include "typedef.h"
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
/* 6.1 Lexical elements */
identifier.opt
: %empty {$$ = parser_empty();}
| identifier
;
identifier
: TOKEN_IDENTIFIER {$$ = parser_token(AST_IDENTIFIER, scanner);}
;
typedef-identifier
: TOKEN_TYPEDEF_IDENTIFIER {$$ = parser_token(AST_TYPEDEF_IDENTIFIER, scanner);}
;
floating-constant
: TOKEN_FLOATING_CONSTANT {$$ = parser_token(AST_FLOATING_CONSTANT, scanner);}
;
integer-constant
: TOKEN_INTEGER_CONSTANT {$$ = parser_token(AST_INTEGER_CONSTANT, scanner);}
;
enumeration-constant
: TOKEN_IDENTIFIER {$$ = parser_token(AST_ENUMERATION_CONSTANT, scanner);}
;
character-constant
: TOKEN_CHARACTER_CONSTANT {$$ = parser_token(AST_CHARACTER_CONSTANT, scanner);}
;
string-literal
: TOKEN_STRING_LITERAL {$$ = parser_token(AST_STRING_LITERAL, scanner);}
;

/* 6.3 Expressions */
primary-expression
: identifier
| floating-constant
| integer-constant
| character-constant
| string-literal
| "(" expression ")" {$$ = parser_append1(AST_PRIMARY_EXPRESSION, $2);}
;
postfix-expression
: primary-expression
| postfix-expression postfix-expression.suffix {$$ = parser_append2(AST_POSTFIX_EXPRESSION, $1, $2);}
;
postfix-expression.suffix
: "[" expression "]" {$$ = parser_append1(AST_ARRAY, $2);}
| "(" argument-expression-list.opt ")" {$$ = parser_append1(AST_CALL, $2);}
| "." identifier {$$ = parser_append1(AST_PERIOD, $2);}
| "->" identifier {$$ = parser_append1(AST_ARROW, $2);}
| "++" {$$ = parser_append0(AST_INCREMENT);}
| "--" {$$ = parser_append0(AST_DECREMENT);}
;
argument-expression-list.opt
: %empty {$$ = parser_list_empty(AST_ARGUMENT_EXPRESSION_LIST);}
| argument-expression-list
;
argument-expression-list
: assignment-expression {$$ = parser_list_new(AST_ARGUMENT_EXPRESSION_LIST, $1);}
| argument-expression-list "," assignment-expression {$$ = parser_list_push($1, $3);}
;
unary-expression
: postfix-expression
| unary-expression.prefix unary-expression {$$ = parser_append2(AST_UNARY_EXPRESSION, $1, $2);}
| "sizeof" unary-expression {$$ = parser_append2(AST_UNARY_EXPRESSION, parser_append0(AST_SIZEOF), $2);}
| "sizeof" "(" type-name ")" {$$ = parser_append1(AST_UNARY_EXPRESSION, parser_append1(AST_SIZEOF, $3));}
| unary-operator cast-expression {$$ = parser_append2(AST_UNARY_EXPRESSION, $1, $2);}
;
unary-expression.prefix
: "++" {$$ = parser_append0(AST_INCREMENT);}
| "--" {$$ = parser_append0(AST_DECREMENT);}
;
unary-operator
: "&" {$$ = parser_append0(AST_AMPERSAND);}
| "*" {$$ = parser_append0(AST_ASTERISK);};
| "+" {$$ = parser_append0(AST_PLUS);};
| "-" {$$ = parser_append0(AST_MINUS);};
| "~" {$$ = parser_append0(AST_TILDE);};
| "!" {$$ = parser_append0(AST_EXCLAMATION);};
;
cast-expression
: unary-expression
| "(" type-name ")" cast-expression {$$ = parser_append2(AST_CAST_EXPRESSION, $2, $4);}
;
multiplicative-expression
: cast-expression
| multiplicative-expression multiplicative-operator cast-expression {$$ = parser_binary($1, $2, $3);}
;
multiplicative-operator
: "*" {$$ = parser_append0(AST_ASTERISK);}
| "/" {$$ = parser_append0(AST_SLASH);}
| "%" {$$ = parser_append0(AST_PERCENT);}
;
additive-expression
: multiplicative-expression
| additive-expression additive-operator multiplicative-expression {$$ = parser_binary($1, $2, $3);}
;
additive-operator
: "+" {$$ = parser_append0(AST_PLUS);}
| "-" {$$ = parser_append0(AST_MINUS);}
;
shift-expression
: additive-expression
| shift-expression shift-operator additive-expression {$$ = parser_binary($1, $2, $3);}
;
shift-operator
: "<<" {$$ = parser_append0(AST_LEFT_SHIFT);}
| ">>" {$$ = parser_append0(AST_RIGHT_SHIFT);}
;
relational-expression
: shift-expression
| relational-expression relational-operator shift-expression {$$ = parser_binary($1, $2, $3);}
;
relational-operator
: "<" {$$ = parser_append0(AST_LESS_THAN);}
| ">" {$$ = parser_append0(AST_GREATER_THAN);}
| "<=" {$$ = parser_append0(AST_LESS_EQUAL);}
| ">=" {$$ = parser_append0(AST_GREATER_EQUAL);}
;
equality-expression
: relational-expression
| equality-expression equality-operator relational-expression {$$ = parser_binary($1, $2, $3);}
;
equality-operator
: "==" {$$ = parser_append0(AST_EQUAL);}
| "!=" {$$ = parser_append0(AST_NOT_EQUAL);}
;
and-expression
: equality-expression
| and-expression and-operator equality-expression {$$ = parser_binary($1, $2, $3);}
;
and-operator
: "&" {$$ = parser_append0(AST_AMPERSAND);}
;
exclusive-or-expression
: and-expression
| exclusive-or-expression exclusive-or-operator and-expression {$$ = parser_binary($1, $2, $3);}
;
exclusive-or-operator
: "^" {$$ = parser_append0(AST_CARET);}
;
inclusive-or-expression
: exclusive-or-expression
| inclusive-or-expression inclusive-or-operator exclusive-or-expression {$$ = parser_binary($1, $2, $3);}
;
inclusive-or-operator
: "|" {$$ = parser_append0(AST_BAR);}
;
logical-and-expression
: inclusive-or-expression
| logical-and-expression logical-and-operator inclusive-or-expression {$$ = parser_binary($1, $2, $3);}
;
logical-and-operator
: "&&" {$$ = parser_append0(AST_AND);}
;
logical-or-expression
: logical-and-expression
| logical-or-expression logical-or-operator logical-and-expression {$$ = parser_binary($1, $2, $3);}
;
logical-or-operator
: "||" {$$ = parser_append0(AST_OR);}
;
conditional-expression
: logical-or-expression
| logical-or-expression "?" expression ":" conditional-expression {$$ = parser_append3(AST_CONDITIONAL_EXPRESSION, $1, $3, $5);}
;
assignment-expression
: conditional-expression
| unary-expression assignment-operator assignment-expression {$$ = parser_binary($1, $2, $3);}
;
assignment-operator
: "=" {$$ = parser_append0(AST_ASSIGN);}
| "*=" {$$ = parser_append0(AST_ASTERISK_ASSIGN);}
| "/=" {$$ = parser_append0(AST_SLASH_ASSIGN);}
| "%=" {$$ = parser_append0(AST_PERCENT_ASSIGN);}
| "+=" {$$ = parser_append0(AST_PLUS_ASSIGN);}
| "-=" {$$ = parser_append0(AST_MINUS_ASSIGN);}
| "<<=" {$$ = parser_append0(AST_LEFT_SHIFT_ASSIGN);}
| ">>=" {$$ = parser_append0(AST_RIGHT_SHIFT_ASSIGN);}
| "&=" {$$ = parser_append0(AST_AMPERSAND_ASSIGN);}
| "^=" {$$ = parser_append0(AST_CARET_ASSIGN);}
| "|=" {$$ = parser_append0(AST_BAR_ASSIGN);}
;
expression.opt
: %empty {$$ = parser_empty();}
| expression
;
expression
: assignment-expression
| expression comma-operator assignment-expression {$$ = parser_binary($1, $2, $3);}
;
comma-operator
: "," {$$ = parser_append0(AST_COMMA);}
;

/* 6.4 Constant expressions */
constant-expression.opt
: %empty {$$ = parser_empty();}
| constant-expression
;
constant-expression
: conditional-expression {$$ = parser_append1(AST_CONSTANT_EXPRESSION, $1);}
;

/* 6.5 Declarations */
declaration
: declaration-specifiers ";" {$$ = parser_append1(AST_DECLARATION, $1);}
| declaration-specifiers init-declarator-list ";" {typedef_register(scanner, $1, $2); $$ = parser_append2(AST_DECLARATION, $1, $2);}
;
declaration-specifiers
: declaration-specifier {$$ = parser_list_new(AST_DECLARATION_SPECIFIERS, $1);}
| declaration-specifiers declaration-specifier {$$ = parser_list_push($1, $2);}
;
declaration-specifier
: storage-class-specifier
| type-specifier
| type-qualifier
;
init-declarator-list
: init-declarator {$$ = parser_list_new(AST_INIT_DECLARATOR_LIST, $1);}
| init-declarator-list "," init-declarator {$$ = parser_list_push($1, $3);}
;
init-declarator
: declarator {$$ = parser_append1(AST_INIT_DECLARATOR, $1);}
| declarator "=" initializer {$$ = parser_append2(AST_INIT_DECLARATOR, $1, $3);}
;
storage-class-specifier
: storage-class-specifier.prefix {$$ = parser_append1(AST_STORAGE_CLASS_SPECIFIER, $1);}
;
storage-class-specifier.prefix
: "typedef" {$$ = parser_append0(AST_TYPEDEF);}
| "extern" {$$ = parser_append0(AST_EXTERN);}
| "static" {$$ = parser_append0(AST_STATIC);}
| "auto" {$$ = parser_append0(AST_AUTO);}
| "register" {$$ = parser_append0(AST_REGISTER);}
;
type-specifier
: type-specifier.prefix {$$ = parser_append1(AST_TYPE_SPECIFIER, $1);}
;
type-specifier.prefix
: "void" {$$ = parser_append0(AST_VOID);}
| "char" {$$ = parser_append0(AST_CHAR);}
| "short" {$$ = parser_append0(AST_SHORT);}
| "int" {$$ = parser_append0(AST_INT);}
| "long" {$$ = parser_append0(AST_LONG);}
| "float" {$$ = parser_append0(AST_FLOAT);}
| "double" {$$ = parser_append0(AST_DOUBLE);}
| "signed" {$$ = parser_append0(AST_SIGNED);}
| "unsigned" {$$ = parser_append0(AST_UNSIGNED);}
| struct-or-union-specifier
| enum-specifier
| typedef-name
;
struct-or-union-specifier
: struct-or-union identifier.opt "{" struct-declaration-list "}" {$$ = parser_append3(AST_STRUCT_OR_UNION_SPECIFIER, $1, $2, $4);}
| struct-or-union identifier {$$ = parser_append2(AST_STRUCT_OR_UNION_SPECIFIER, $1, $2);}
;
struct-or-union
: "struct" {$$ = parser_append0(AST_STRUCT);}
| "union" {$$ = parser_append0(AST_UNION);}
;
struct-declaration-list
: struct-declaration {$$ = parser_list_new(AST_STRUCT_DECLARATION_LIST, $1);}
| struct-declaration-list struct-declaration {$$ = parser_list_push($1, $2);}
;
struct-declaration
: specifier-qualifier-list struct-declarator-list ";" {$$ = parser_append2(AST_STRUCT_DECLARATION, $1, $2);}
;
specifier-qualifier-list
: specifier-qualifier {$$ = parser_list_new(AST_SPECIFIER_QUALIFIER_LIST, $1);}
| specifier-qualifier-list specifier-qualifier {$$ = parser_list_push($1, $2);}
;
specifier-qualifier
: type-specifier
| type-qualifier
;
struct-declarator-list
: struct-declarator {$$ = parser_list_new(AST_STRUCT_DECLARATOR_LIST, $1);}
| struct-declarator-list "," struct-declarator {$$ = parser_list_push($1, $3);}
;
struct-declarator
: declarator {$$ = parser_append1(AST_STRUCT_DECLARATOR, $1);}
| declarator.opt ":" constant-expression {$$ = parser_append2(AST_STRUCT_DECLARATOR, $1, $3);}
;
enum-specifier
: "enum" identifier.opt "{" enumerator-list "}" {$$ = parser_append2(AST_ENUM_SPECIFIER, $2, $4); }
| "enum" identifier {$$ = parser_append1(AST_ENUM_SPECIFIER, $2); }
;
enumerator-list
: enumerator {$$ = parser_list_new(AST_ENUMERATOR_LIST, $1);}
| enumerator-list "," enumerator {$$ = parser_list_push($1, $3);}
;
enumerator
: enumeration-constant {$$ = parser_append1(AST_ENUMERATOR, $1);}
| enumeration-constant "=" constant-expression {$$ = parser_append2(AST_ENUMERATOR, $1, $3);}
;
type-qualifier
: type-qualifier.prefix {$$ = parser_append1(AST_TYPE_QUALIFIER, $1);}
;
type-qualifier.prefix
: "const" {$$ = parser_append0(AST_CONST);}
| "volatile" {$$ = parser_append0(AST_VOLATILE);}
;
declarator.opt
: %empty {$$ = parser_empty();}
| declarator
;
declarator
: direct-declarator {$$ = parser_append1(AST_DECLARATOR, $1);}
| pointer direct-declarator {$$ = parser_append2(AST_DECLARATOR, $1, $2);}
;
direct-declarator
: direct-declarator.prefix
| direct-declarator direct-declarator.suffix {$$ = parser_append2(AST_DIRECT_DECLARATOR, $1, $2);}
;
direct-declarator.prefix
: identifier
| "(" declarator ")" {$$ = parser_append1(AST_DIRECT_DECLARATOR, $2);}
;
direct-declarator.suffix
: "[" constant-expression.opt "]" {$$ = parser_append1(AST_ARRAY, $2);}
| "(" parameter-type-list ")" {$$ = parser_append1(AST_CALL, $2);}
| "(" identifier-list.opt ")" {$$ = parser_append1(AST_OLD, $2);}
;
pointer
: pointer.prefix {$$ = parser_append1(AST_POINTER, $1);}
| pointer.prefix pointer {$$ = parser_append2(AST_POINTER, $1, $2);}
;
pointer.prefix
: "*" type-qualifier-list.opt {$$ = $2;}
;
type-qualifier-list.opt
: %empty {$$ = parser_list_empty(AST_TYPE_QUALIFIER_LIST);}
| type-qualifier-list
;
type-qualifier-list
: type-qualifier {$$ = parser_list_new(AST_TYPE_QUALIFIER_LIST, $1);}
| type-qualifier-list type-qualifier {$$ = parser_list_push($1, $2);}
;
parameter-type-list.opt
: %empty {$$ = parser_list_empty(AST_PARAMETER_LIST);}
| parameter-type-list
;
parameter-type-list
: parameter-list
| parameter-list "," "..." {$$ = parser_append1(AST_PARAMETER_TYPE_LIST, $1);}
;
parameter-list
: parameter-declaration {$$ = parser_list_new(AST_PARAMETER_LIST, $1);}
| parameter-list "," parameter-declaration {$$ = parser_list_push($1, $3);}
;
parameter-declaration
: declaration-specifiers {$$ = parser_append1(AST_PARAMETER_DECLARATION, $1);}
| declaration-specifiers parameter-declaration.suffix {$$ = parser_append2(AST_PARAMETER_DECLARATION, $1, $2);}
;
parameter-declaration.suffix
: declarator
| abstract-declarator
;
identifier-list.opt
: %empty {$$ = parser_list_empty(AST_IDENTIFIER_LIST);}
| identifier-list
;
identifier-list
: identifier {$$ = parser_list_new(AST_IDENTIFIER_LIST, $1);}
| identifier-list "," identifier {$$ = parser_list_push($1, $3);}
;
type-name
: specifier-qualifier-list {$$ = parser_append1(AST_TYPE_NAME, $1);}
| specifier-qualifier-list abstract-declarator {$$ = parser_append2(AST_TYPE_NAME, $1, $2);}
;
abstract-declarator
: abstract-declarator.prefix {$$ = parser_append1(AST_ABSTRACT_DECLARATOR, $1);}
| pointer direct-abstract-declarator {$$ = parser_append2(AST_ABSTRACT_DECLARATOR, $1, $2);}
;
abstract-declarator.prefix
: pointer
| direct-abstract-declarator
;
direct-abstract-declarator
: "(" abstract-declarator ")" {$$ = parser_append1(AST_DIRECT_ABSTRACT_DECLARATOR, $2);}
| direct-abstract-declarator.suffix
| direct-abstract-declarator direct-abstract-declarator.suffix {$$ = parser_append2(AST_DIRECT_ABSTRACT_DECLARATOR, $1, $2);}
;
direct-abstract-declarator.suffix
: "[" constant-expression.opt "]" {$$ = parser_append1(AST_ARRAY, $2);}
| "(" parameter-type-list.opt ")" {$$ = parser_append1(AST_CALL, $2);}
;
typedef-name
: typedef-identifier {$$ = parser_append1(AST_TYPEDEF_NAME, $1);}
;
initializer
: assignment-expression
| initializer.suffix {$$ = parser_append1(AST_INITIALIZER, $1);}
;
initializer.suffix
: "{" initializer-list "}" {$$ = $2;}
| "{" initializer-list "," "}" {$$ = $2;}
;
initializer-list
: initializer {$$ = parser_list_new(AST_INITIALIZER_LIST, $1);}
| initializer-list "," initializer {$$ = parser_list_push($1, $3);}
;

/* 6.6 Statements */
statement
: statement.prefix {$$ = parser_append1(AST_STATEMENT, $1);}
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
: labeled-statement.prefix ":" statement {$$ = parser_append2(AST_LABELED_STATEMENT, $1, $3);}
;
labeled-statement.prefix
: identifier
| "case" constant-expression {$$ = parser_append1(AST_CASE, $2);}
| "default" {$$ = parser_append0(AST_DEFAULT);}
;
compound-statement
: "{" declaration-list.opt statement-list.opt "}" {$$ = parser_append2(AST_COMPOUND_STATEMENT, $2, $3);}
;
declaration-list.opt
: %empty {$$ = parser_list_empty(AST_DECLARATION_LIST);}
| declaration-list
;
declaration-list
: declaration {$$ = parser_list_new(AST_DECLARATION_LIST, $1);}
| declaration-list declaration {$$ = parser_list_push($1, $2);}
;
statement-list.opt
: %empty {$$ = parser_list_empty(AST_STATEMENT_LIST);}
| statement-list
;
statement-list
: statement {$$ = parser_list_new(AST_STATEMENT_LIST, $1);}
| statement-list statement {$$ = parser_list_push($1, $2);}
;
expression-statement
: expression.opt ";" {$$ = parser_append1(AST_EXPRESSION_STATEMENT, $1);}
;
selection-statement
: selection-statement.suffix {$$ = parser_append1(AST_SELECTION_STATEMENT, $1);}
;
selection-statement.suffix
: "if" selection-statement.if {$$ = $2;}
| "switch" selection-statement.switch {$$ = $2;}
;
selection-statement.if
: "(" expression ")" statement %prec THEN {$$ = parser_append2(AST_IF, $2, $4);}
| "(" expression ")" statement "else" statement {$$ = parser_append3(AST_IF, $2, $4, $6);}
;
selection-statement.switch
: "(" expression ")" statement {$$ = parser_append2(AST_SWITCH, $2, $4);}
;
iteration-statement
: iteration-statement.suffix {$$ = parser_append1(AST_ITERATION_STATEMENT, $1);}
;
iteration-statement.suffix
: "while" iteration-statement.while {$$ = $2;}
| "do" iteration-statement.do {$$ = $2;}
| "for" iteration-statement.for {$$ = $2;}
;
iteration-statement.while
: "(" expression ")" statement {$$ = parser_append2(AST_WHILE, $2, $4);}
;
iteration-statement.do
: statement "while" "(" expression ")" ";" {$$ = parser_append2(AST_DO, $1, $4);}
;
iteration-statement.for
: "(" expression.opt ";" expression.opt ";" expression.opt ")" statement {$$ = parser_append4(AST_FOR, $2, $4, $6, $8);}
;
jump-statement
: jump-statement.suffix ";" {$$ = parser_append1(AST_JUMP_STATEMENT, $1);}
;
jump-statement.suffix
: "goto" identifier {$$ = parser_append1(AST_GOTO, $2);}
| "continue" {$$ = parser_append0(AST_CONTINUE);}
| "break" {$$ = parser_append0(AST_BREAK);}
| "return" expression.opt {$$ = parser_append1(AST_RETURN, $2);}
;

/* 6.7 External definitions */
top
: translation-unit {scanner_set_ast(scanner, parser_list_finish($1));}
;
translation-unit
: external-declaration {$$ = parser_list_new(AST_TRANSLATION_UNIT, $1);}
| translation-unit external-declaration {$$ = parser_list_push($1, $2);}
;
external-declaration
: function-definition
| declaration {$$ = parser_append1(AST_EXTERNAL_DECLARATION, $1);}
;
function-definition
: function-definition.old {$$ = parser_append1(AST_FUNCTION_DEFINITION, $1);}
| declaration-specifiers declarator compound-statement {$$ = parser_append3(AST_FUNCTION_DEFINITION, $1, $2, $3);}
;
function-definition.old
: declarator compound-statement {$$ = parser_append2(AST_OLD, $1, $2);}
| declarator declaration-list compound-statement {$$ = parser_append3(AST_OLD, $1, $2, $3);}
| declaration-specifiers declarator declaration-list compound-statement {$$ = parser_append4(AST_OLD, $1, $2, $3, $4);}
;
%%
