%code requires {
#include "sexp_type.h"
#include "scanner/yyscan.h"
}

%define api.pure full
%define api.value.type {Sexp *}
%param {yyscan_t scanner}

%code provides {
#include "lexer.h"
#include "scanner/parser.h"
#include "scanner/register.h"
#include "scanner/scanner_impl.h"
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
auto: "auto" {$$ = parser_symbol(AST_AUTO);}
;
break: "break" {$$ = parser_symbol(AST_BREAK);}
;
case: "case" {$$ = parser_symbol(AST_CASE);}
;
char: "char" {$$ = parser_symbol(AST_CHAR);}
;
const: "const" {$$ = parser_symbol(AST_CONST);}
;
continue: "continue" {$$ = parser_symbol(AST_CONTINUE);}
;
default: "default" {$$ = parser_symbol(AST_DEFAULT);}
;
do: "do" {$$ = parser_symbol(AST_DO);}
;
double: "double" {$$ = parser_symbol(AST_DOUBLE);}
;
else: "else" {$$ = parser_symbol(AST_ELSE);}
;
enum: "enum" {$$ = parser_symbol(AST_ENUM);}
;
extern: "extern" {$$ = parser_symbol(AST_EXTERN);}
;
float: "float" {$$ = parser_symbol(AST_FLOAT);}
;
for: "for" {$$ = parser_symbol(AST_FOR);}
;
goto: "goto" {$$ = parser_symbol(AST_GOTO);}
;
if: "if" {$$ = parser_symbol(AST_IF);}
;
int: "int" {$$ = parser_symbol(AST_INT);}
;
long: "long" {$$ = parser_symbol(AST_LONG);}
;
register: "register" {$$ = parser_symbol(AST_REGISTER);}
;
return: "return" {$$ = parser_symbol(AST_RETURN);}
;
short: "short" {$$ = parser_symbol(AST_SHORT);}
;
signed: "signed" {$$ = parser_symbol(AST_SIGNED);}
;
sizeof: "sizeof" {$$ = parser_symbol(AST_SIZEOF);}
;
static: "static" {$$ = parser_symbol(AST_STATIC);}
;
struct: "struct" {$$ = parser_symbol(AST_STRUCT);}
;
switch: "switch" {$$ = parser_symbol(AST_SWITCH);}
;
typedef: "typedef" {$$ = parser_symbol(AST_TYPEDEF);}
;
union: "union" {$$ = parser_symbol(AST_UNION);}
;
unsigned: "unsigned" {$$ = parser_symbol(AST_UNSIGNED);}
;
void: "void" {$$ = parser_symbol(AST_VOID);}
;
volatile: "volatile" {$$ = parser_symbol(AST_VOLATILE);}
;
while: "while" {$$ = parser_symbol(AST_WHILE);}
;

period: "." {$$ = parser_symbol(AST_PERIOD);}
;
arrow: "->" {$$ = parser_symbol(AST_ARROW);}
;
increment: "++" {$$ = parser_symbol(AST_INCREMENT);}
;
decrement: "--" {$$ = parser_symbol(AST_DECREMENT);}
;
ampersand: "&" {$$ = parser_symbol(AST_AMPERSAND);}
;
asterisk: "*" {$$ = parser_symbol(AST_ASTERISK);}
;
plus: "+" {$$ = parser_symbol(AST_PLUS);}
;
minus: "-" {$$ = parser_symbol(AST_MINUS);}
;
tilde: "~" {$$ = parser_symbol(AST_TILDE);}
;
exclamation: "!" {$$ = parser_symbol(AST_EXCLAMATION);}
;
slash: "/" {$$ = parser_symbol(AST_SLASH);}
;
percent: "%" {$$ = parser_symbol(AST_PERCENT);}
;
left-shift: "<<" {$$ = parser_symbol(AST_LEFT_SHIFT);}
;
right-shift: ">>" {$$ = parser_symbol(AST_RIGHT_SHIFT);}
;
less-than: "<" {$$ = parser_symbol(AST_LESS_THAN);}
;
greater-than: ">" {$$ = parser_symbol(AST_GREATER_THAN);}
;
less-equal: "<=" {$$ = parser_symbol(AST_LESS_EQUAL);}
;
greater-equal: ">=" {$$ = parser_symbol(AST_GREATER_EQUAL);}
;
equal: "==" {$$ = parser_symbol(AST_EQUAL);}
;
not-equal: "!=" {$$ = parser_symbol(AST_NOT_EQUAL);}
;
caret: "^" {$$ = parser_symbol(AST_CARET);}
;
bar: "|" {$$ = parser_symbol(AST_BAR);}
;
and: "&&" {$$ = parser_symbol(AST_AND);}
;
or: "||" {$$ = parser_symbol(AST_OR);}
;
question: "?" {$$ = parser_symbol(AST_QUESTION);}
;
assign: "=" {$$ = parser_symbol(AST_ASSIGN);}
;
asterisk-assign: "*=" {$$ = parser_symbol(AST_ASTERISK_ASSIGN);}
;
slash-assign: "/=" {$$ = parser_symbol(AST_SLASH_ASSIGN);}
;
percent-assign: "%=" {$$ = parser_symbol(AST_PERCENT_ASSIGN);}
;
plus-assign: "+=" {$$ = parser_symbol(AST_PLUS_ASSIGN);}
;
minus-assign: "-=" {$$ = parser_symbol(AST_MINUS_ASSIGN);}
;
left-shift-assign: "<<=" {$$ = parser_symbol(AST_LEFT_SHIFT_ASSIGN);}
;
right-shift-assign: ">>=" {$$ = parser_symbol(AST_RIGHT_SHIFT_ASSIGN);}
;
ampersand-assign: "&=" {$$ = parser_symbol(AST_AMPERSAND_ASSIGN);}
;
caret-assign: "^=" {$$ = parser_symbol(AST_CARET_ASSIGN);}
;
bar-assign: "|=" {$$ = parser_symbol(AST_BAR_ASSIGN);}
;

left-bracket: "[" {$$ = parser_symbol(AST_LEFT_BRACKET);}
;
right-bracket: "]" {$$ = parser_symbol(AST_RIGHT_BRACKET);}
;
left-paren: "(" {$$ = parser_symbol(AST_LEFT_PAREN);}
;
right-paren: ")" {$$ = parser_symbol(AST_RIGHT_PAREN);}
;
left-brace: "{" {$$ = parser_symbol(AST_LEFT_BRACE);}
;
right-brace: "}" {$$ = parser_symbol(AST_RIGHT_BRACE);}
;
comma: "," {$$ = parser_symbol(AST_COMMA);}
;
colon: ":" {$$ = parser_symbol(AST_COLON);}
;
semicolon: ";" {$$ = parser_symbol(AST_SEMICOLON);}
;
ellipsis: "..." {$$ = parser_symbol(AST_ELLIPSIS);}
;

/* 6.1 Lexical elements */
identifier.opt
: %empty {$$ = PARSER_LIST0();}
| identifier
;
identifier
: identifier.tag {$$ = parser_list_atom(AST_IDENTIFIER, $1);}
;
identifier.tag
: TOKEN_IDENTIFIER {$$ = parser_token(scanner);}
;
typedef-identifier
: typedef-identifier.tag {$$ = parser_list_atom(AST_TYPEDEF_IDENTIFIER, $1);}
;
typedef-identifier.tag
: TOKEN_TYPEDEF_IDENTIFIER {$$ = parser_token(scanner);}
;
floating-constant
: floating-constant.tag {$$ = parser_list_atom(AST_FLOATING_CONSTANT, $1);}
;
floating-constant.tag
: TOKEN_FLOATING_CONSTANT {$$ = parser_token(scanner);}
;
integer-constant
: integer-constant.tag {$$ = parser_list_atom(AST_INTEGER_CONSTANT, $1);}
;
integer-constant.tag
: TOKEN_INTEGER_CONSTANT {$$ = parser_token(scanner);}
;
enumeration-constant
: enumeration-constant.tag {$$ = parser_list_atom(AST_ENUMERATION_CONSTANT, $1);}
;
enumeration-constant.tag
: TOKEN_IDENTIFIER {$$ = parser_token(scanner);}
;
character-constant
: character-constant.tag {$$ = parser_list_atom(AST_CHARACTER_CONSTANT, $1);}
;
character-constant.tag
: TOKEN_CHARACTER_CONSTANT {$$ = parser_token(scanner);}
;
string-literal
: TOKEN_STRING_LITERAL {$$ = parser_token(scanner);}
;
string-constant
: string-literal {$$ = parser_list_atom(AST_STRING_LITERAL, $1);}
| string-constant string-literal {$$ = parser_list_snoc($1, $2);}
;

/* 6.3 Expressions */
primary-expression
: identifier
| floating-constant
| integer-constant
| character-constant
| string-constant
| left-paren expression right-paren {$$ = parser_tag(AST_PRIMARY_EXPRESSION, PARSER_LIST3($1, $2, $3));}
;
postfix-expression
: primary-expression
| postfix-expression.tag {$$ = parser_tag(AST_POSTFIX_EXPRESSION, $1);}
;
postfix-expression.tag
: postfix-expression postfix-expression.suffix {$$ = parser_cons($1, $2);}
;
postfix-expression.suffix
: left-bracket expression right-bracket {$$ = PARSER_LIST3($1, $2, $3);}
| left-paren argument-expression-list.opt right-paren {$$ = PARSER_LIST3($1, $2, $3);}
| period identifier {$$ = PARSER_LIST2($1, $2);}
| arrow identifier {$$ = PARSER_LIST2($1, $2);}
| increment {$$ = PARSER_LIST1($1);}
| decrement {$$ = PARSER_LIST1($1);}
;
argument-expression-list.opt
: %empty {$$ = parser_list_nil(AST_ARGUMENT_EXPRESSION_LIST);}
| argument-expression-list
;
argument-expression-list
: assignment-expression {$$ = parser_list_atom(AST_ARGUMENT_EXPRESSION_LIST, $1);}
| argument-expression-list "," assignment-expression {$$ = parser_list_snoc($1, $3);}
;
unary-expression
: postfix-expression
| unary-expression.tag {$$ = parser_tag(AST_UNARY_EXPRESSION, $1);}
;
unary-expression.tag
: increment unary-expression {$$ = PARSER_LIST2($1, $2);}
| decrement unary-expression {$$ = PARSER_LIST2($1, $2);}
| unary-operator cast-expression {$$ = PARSER_LIST2($1, $2);}
| sizeof unary-expression {$$ = PARSER_LIST2($1, $2);}
| sizeof left-paren type-name right-paren {$$ = PARSER_LIST4($1, $2, $3, $4);}
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
| cast-expression.tag {$$ = parser_tag(AST_CAST_EXPRESSION, $1);}
;
cast-expression.tag
: left-paren type-name right-paren cast-expression {$$ = PARSER_LIST4($1, $2, $3, $4);}
;
multiplicative-expression
: cast-expression
| multiplicative-expression.tag {$$ = parser_tag(AST_MULTIPLICATIVE_EXPRESSION, $1);}
;
multiplicative-expression.tag
: multiplicative-expression multiplicative-operator cast-expression {$$ = PARSER_LIST3($1, $2, $3);}
;
multiplicative-operator
: asterisk
| slash
| percent
;
additive-expression
: multiplicative-expression
| additive-expression.tag {$$ = parser_tag(AST_ADDITIVE_EXPRESSION, $1);}
;
additive-expression.tag
: additive-expression additive-operator multiplicative-expression {$$ = PARSER_LIST3($1, $2, $3);}
;
additive-operator
: plus
| minus
;
shift-expression
: additive-expression
| shift-expression.tag {$$ = parser_tag(AST_SHIFT_EXPRESSION, $1);}
;
shift-expression.tag
: shift-expression shift-operator additive-expression {$$ = PARSER_LIST3($1, $2, $3);}
;
shift-operator
: left-shift
| right-shift
;
relational-expression
: shift-expression
| relational-expression.tag {$$ = parser_tag(AST_RELATIONAL_EXPRESSION, $1);}
;
relational-expression.tag
: relational-expression relational-operator shift-expression {$$ = PARSER_LIST3($1, $2, $3);}
;
relational-operator
: less-than
| greater-than
| less-equal
| greater-equal
;
equality-expression
: relational-expression
| equality-expression.tag {$$ = parser_tag(AST_EQUALITY_EXPRESSION, $1);}
;
equality-expression.tag
: equality-expression equality-operator relational-expression {$$ = PARSER_LIST3($1, $2, $3);}
;
equality-operator
: equal
| not-equal
;
and-expression
: equality-expression
| and-expression.tag {$$ = parser_tag(AST_AND_EXPRESSION, $1);}
;
and-expression.tag
: and-expression ampersand equality-expression {$$ = PARSER_LIST3($1, $2, $3);}
;
exclusive-or-expression
: and-expression
| exclusive-or-expression.tag {$$ = parser_tag(AST_EXCLUSIVE_OR_EXPRESSION, $1);}
;
exclusive-or-expression.tag
: exclusive-or-expression caret and-expression {$$ = PARSER_LIST3($1, $2, $3);}
;
inclusive-or-expression
: exclusive-or-expression
| inclusive-or-expression.tag {$$ = parser_tag(AST_INCLUSIVE_OR_EXPRESSION, $1);}
;
inclusive-or-expression.tag
: inclusive-or-expression bar exclusive-or-expression {$$ = PARSER_LIST3($1, $2, $3);}
;
logical-and-expression
: inclusive-or-expression
| logical-and-expression.tag {$$ = parser_tag(AST_LOGICAL_AND_EXPRESSION, $1);}
;
logical-and-expression.tag
: logical-and-expression and inclusive-or-expression {$$ = PARSER_LIST3($1, $2, $3);}
;
logical-or-expression
: logical-and-expression
| logical-or-expression.tag {$$ = parser_tag(AST_LOGICAL_OR_EXPRESSION, $1);}
;
logical-or-expression.tag
: logical-or-expression or logical-and-expression {$$ = PARSER_LIST3($1, $2, $3);}
;
conditional-expression
: logical-or-expression
| conditional-expression.tag {$$ = parser_tag(AST_CONDITIONAL_EXPRESSION, $1);}
;
conditional-expression.tag
: logical-or-expression question expression colon conditional-expression {$$ = PARSER_LIST5($1, $2, $3, $4, $5);}
;
assignment-expression
: conditional-expression
| assignment-expression.tag {$$ = parser_tag(AST_ASSIGNMENT_EXPRESSION, $1);}
;
assignment-expression.tag
: unary-expression assignment-operator assignment-expression {$$ = PARSER_LIST3($1, $2, $3);}
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
: %empty {$$ = PARSER_LIST0();}
| expression
;
expression
: assignment-expression
| expression.tag {$$ = parser_tag(AST_EXPRESSION, $1);}
;
expression.tag
: expression "," assignment-expression {$$ = PARSER_LIST2($1, $3);}
;

/* 6.4 Constant expressions */
constant-expression.opt
: %empty {$$ = PARSER_LIST0();}
| constant-expression
;
constant-expression
: conditional-expression {$$ = parser_tag(AST_CONSTANT_EXPRESSION, PARSER_LIST1($1));}
;

/* 6.5 Declarations */
declaration
: declaration.tag {$$ = parser_tag(AST_DECLARATION, $1);}
;
declaration.tag
: declaration-specifiers init-declarator-list.opt semicolon {$$ = PARSER_LIST3($1, $2, $3);}
;
declaration-specifiers
: declaration-specifier {$$ = parser_list_atom(AST_DECLARATION_SPECIFIERS, $1);}
| declaration-specifiers declaration-specifier {$$ = parser_list_snoc($1, $2);}
;
declaration-specifier
: storage-class-specifier
| type-specifier
| type-qualifier
;
init-declarator-list.opt
: %empty {$$ = parser_list_nil(AST_INIT_DECLARATOR_LIST);}
| init-declarator-list
;
init-declarator-list
: init-declarator {$$ = parser_list_atom(AST_INIT_DECLARATOR_LIST, $1);}
| init-declarator-list "," init-declarator {$$ = parser_list_snoc($1, $3);}
;
init-declarator
: init-declarator.tag {$$ = parser_tag(AST_INIT_DECLARATOR, $1);}
;
init-declarator.tag
: declarator {$$ = PARSER_LIST1($1);}
| declarator assign initializer {$$ = PARSER_LIST3($1, $2, $3);}
;
storage-class-specifier
: storage-class-specifier.tag {$$ = parser_tag(AST_STORAGE_CLASS_SPECIFIER, PARSER_LIST1($1));}
;
storage-class-specifier.tag
: typedef
| extern
| static
| auto
| register
;
type-specifier
: type-specifier.tag {$$ = parser_tag(AST_TYPE_SPECIFIER, PARSER_LIST1($1));}
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
: struct-or-union-specifier.tag {$$ = parser_tag(AST_STRUCT_OR_UNION_SPECIFIER, $1);}
;
struct-or-union-specifier.tag
: struct-or-union identifier.opt left-brace struct-declaration-list right-brace {$$ = PARSER_LIST5($1, $2, $3, $4, $5);}
| struct-or-union identifier {$$ = PARSER_LIST2($1, $2);}
;
struct-or-union
: struct
| union
;
struct-declaration-list
: struct-declaration {$$ = parser_list_atom(AST_STRUCT_DECLARATION_LIST, $1);}
| struct-declaration-list struct-declaration {$$ = parser_list_snoc($1, $2);}
;
struct-declaration
: struct-declaration.tag {$$ = parser_tag(AST_STRUCT_DECLARATION, $1);}
struct-declaration.tag
: specifier-qualifier-list struct-declarator-list semicolon {$$ = PARSER_LIST3($1, $2, $3);}
;
specifier-qualifier-list
: specifier-qualifier {$$ = parser_list_atom(AST_SPECIFIER_QUALIFIER_LIST, $1);}
| specifier-qualifier-list specifier-qualifier {$$ = parser_list_snoc($1, $2);}
;
specifier-qualifier
: type-specifier
| type-qualifier
;
struct-declarator-list
: struct-declarator {$$ = parser_list_atom(AST_STRUCT_DECLARATOR_LIST, $1);}
| struct-declarator-list "," struct-declarator {$$ = parser_list_snoc($1, $3);}
;
struct-declarator
: struct-declarator.tag {$$ = parser_tag(AST_STRUCT_DECLARATOR, $1);}
;
struct-declarator.tag
: declarator {$$ = PARSER_LIST1($1);}
| declarator.opt colon constant-expression {$$ = PARSER_LIST3($1, $2, $3);}
;
enum-specifier
: enum-specifier.tag {$$ = parser_tag(AST_ENUM_SPECIFIER, $1);}
;
enum-specifier.tag
: enum identifier.opt left-brace enumerator-list right-brace {$$ = PARSER_LIST5($1, $2, $3, $4, $5);}
| enum identifier {$$ = PARSER_LIST2($1, $2);}
;
enumerator-list
: enumerator {$$ = parser_list_atom(AST_ENUMERATOR_LIST, $1);}
| enumerator-list "," enumerator {$$ = parser_list_snoc($1, $3);}
;
enumerator
: enumerator.tag {$$ = parser_tag(AST_ENUMERATOR, $1);}
;
enumerator.tag
: enumeration-constant {$$ = PARSER_LIST1($1);}
| enumeration-constant assign constant-expression {$$ = PARSER_LIST3($1, $2, $3);}
;
type-qualifier
: type-qualifier.tag {$$ = parser_tag(AST_TYPE_QUALIFIER, PARSER_LIST1($1));}
;
type-qualifier.tag
: const
| volatile
;
declarator.opt
: %empty {$$ = PARSER_LIST0();}
| declarator
;
declarator
: declarator.tag {$$ = parser_tag(AST_DECLARATOR, $1);}
;
declarator.tag
: direct-declarator {$$ = PARSER_LIST1($1);}
| pointer direct-declarator {$$ = PARSER_LIST2($1, $2);}
;
direct-declarator
: direct-declarator.tag {$$ = parser_tag(AST_DIRECT_DECLARATOR, $1);}
;
direct-declarator.tag
: identifier {$$ = PARSER_LIST1($1);}
| left-paren declarator right-paren {$$ = PARSER_LIST3($1, $2, $3);}
| direct-declarator direct-declarator.suffix {$$ = parser_cons($1, $2);}
;
direct-declarator.suffix
: left-bracket constant-expression.opt right-bracket {$$ = PARSER_LIST3($1, $2, $3);}
| left-paren parameter-type-list.opt right-paren {$$ = PARSER_LIST3($1, $2, $3);}
| left-paren identifier-list right-paren {$$ = PARSER_LIST3($1, $2, $3);}
;
pointer
: pointer.tag {$$ = parser_tag(AST_POINTER, $1);}
;
pointer.tag
: asterisk type-qualifier-list.opt {$$ = PARSER_LIST2($1, $2);}
| pointer asterisk type-qualifier-list.opt {$$ = PARSER_LIST3($1, $2, $3);}
;
type-qualifier-list.opt
: %empty {$$ = parser_list_nil(AST_TYPE_QUALIFIER_LIST);}
| type-qualifier-list
;
type-qualifier-list
: type-qualifier {$$ = parser_list_atom(AST_TYPE_QUALIFIER_LIST, $1);}
| type-qualifier-list type-qualifier {$$ = parser_list_snoc($1, $2);}
;
parameter-type-list.opt
: %empty {$$ = parser_list_nil(AST_PARAMETER_LIST);}
| parameter-type-list
;
parameter-type-list
: parameter-list
| parameter-list "," ellipsis {$$ = parser_list_snoc($1, $3);}
;
parameter-list
: parameter-declaration {$$ = parser_list_atom(AST_PARAMETER_LIST, $1);}
| parameter-list "," parameter-declaration {$$ = parser_list_snoc($1, $3);}
;
parameter-declaration
: parameter-declaration.tag {$$ = parser_tag(AST_PARAMETER_DECLARATION, $1);}
;
parameter-declaration.tag
: declaration-specifiers declarator {$$ = PARSER_LIST2($1, $2);}
| declaration-specifiers abstract-declarator.opt {$$ = PARSER_LIST2($1, $2);}
;
identifier-list
: identifier {$$ = parser_list_atom(AST_IDENTIFIER_LIST, $1);}
| identifier-list "," identifier {$$ = parser_list_snoc($1, $3);}
;
type-name
: type-name.tag {$$ = parser_tag(AST_TYPE_NAME, $1);}
;
type-name.tag
: specifier-qualifier-list abstract-declarator.opt {$$ = PARSER_LIST2($1, $2);}
;
abstract-declarator.opt
: %empty {$$ = PARSER_LIST0();}
| abstract-declarator
;
abstract-declarator
: abstract-declarator.tag {$$ = parser_tag(AST_ABSTRACT_DECLARATOR, $1);}
;
abstract-declarator.tag
: pointer {$$ = PARSER_LIST1($1);}
| direct-abstract-declarator {$$ = PARSER_LIST1($1);}
| pointer direct-abstract-declarator {$$ = PARSER_LIST2($1, $2);}
;
direct-abstract-declarator
: direct-abstract-declarator.tag {$$ = parser_tag(AST_DIRECT_ABSTRACT_DECLARATOR, $1);}
;
direct-abstract-declarator.tag
: left-paren abstract-declarator right-paren {$$ = PARSER_LIST3($1, $2, $3);}
| direct-abstract-declarator.suffix
| direct-abstract-declarator direct-abstract-declarator.suffix {$$ = parser_cons($1, $2);}
;
direct-abstract-declarator.suffix
: left-bracket constant-expression.opt right-bracket {$$ = PARSER_LIST3($1, $2, $3);}
| left-paren parameter-type-list.opt right-paren {$$ = PARSER_LIST3($1, $2, $3);}
;
typedef-name
: typedef-identifier {$$ = parser_tag(AST_TYPEDEF_NAME, PARSER_LIST1($1));}
;
initializer
: assignment-expression
| initializer.tag {$$ = parser_tag(AST_INITIALIZER, $1);}
;
initializer.tag
: left-brace initializer-list right-brace {$$ = PARSER_LIST3($1, $2, $3);}
| left-brace initializer-list comma right-brace {$$ = PARSER_LIST4($1, $2, $3, $4);}
;
initializer-list
: initializer {$$ = parser_list_atom(AST_INITIALIZER_LIST, $1);}
| initializer-list "," initializer {$$ = parser_list_snoc($1, $3);}
;

/* 6.6 Statements */
statement
: statement.tag {$$ = parser_tag(AST_STATEMENT, PARSER_LIST1($1));}
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
: labeled-statement.tag {$$ = parser_tag(AST_LABELED_STATEMENT, $1);}
;
labeled-statement.tag
: identifier colon statement {$$ = PARSER_LIST3($1, $2, $3);}
| case constant-expression colon statement {$$ = PARSER_LIST4($1, $2, $3, $4);}
| default colon statement {$$ = PARSER_LIST3($1, $2, $3);}
;
compound-statement
: compound-statement.tag {$$ = parser_tag(AST_COMPOUND_STATEMENT, $1);}
;
compound-statement.tag
: left-brace declaration-list.opt statement-list.opt right-brace {$$ = PARSER_LIST4($1, $2, $3, $4);}
;
declaration-list.opt
: %empty {$$ = parser_list_nil(AST_DECLARATION_LIST);}
| declaration-list
;
declaration-list
: declaration {$$ = parser_list_atom(AST_DECLARATION_LIST, $1);}
| declaration-list declaration {$$ = parser_list_snoc($1, $2);}
;
statement-list.opt
: %empty {$$ = parser_list_nil(AST_STATEMENT_LIST);}
| statement-list
;
statement-list
: statement {$$ = parser_list_atom(AST_STATEMENT_LIST, $1);}
| statement-list statement {$$ = parser_list_snoc($1, $2);}
;
expression-statement
: expression-statement.tag {$$ = parser_tag(AST_EXPRESSION_STATEMENT, $1);}
;
expression-statement.tag
: expression.opt semicolon {$$ = PARSER_LIST2($1, $2);}
;
selection-statement
: selection-statement.tag {$$ = parser_tag(AST_SELECTION_STATEMENT, $1);}
;
selection-statement.tag
: if left-paren expression right-paren statement %prec THEN {$$ = PARSER_LIST5($1, $2, $3, $4, $5);}
| if left-paren expression right-paren statement else statement {$$ = PARSER_LIST7($1, $2, $3, $4, $5, $6, $7);}
| switch left-paren expression right-paren statement {$$ = PARSER_LIST5($1, $2, $3, $4, $5);}
;
iteration-statement
: iteration-statement.tag {$$ = parser_tag(AST_ITERATION_STATEMENT, $1);}
;
iteration-statement.tag
: while left-paren expression right-paren statement {$$ = PARSER_LIST5($1, $2, $3, $4, $5);}
| do statement while left-paren expression right-paren semicolon {$$ = PARSER_LIST7($1, $2, $3, $4, $5, $6, $7);}
| for left-paren expression.opt semicolon expression.opt semicolon expression.opt right-paren statement {$$ = PARSER_LIST9($1, $2, $3, $4, $5, $6, $7, $8, $9);}
;
jump-statement
: jump-statement.tag {$$ = parser_tag(AST_JUMP_STATEMENT, $1);}
;
jump-statement.tag
: goto identifier semicolon {$$ = PARSER_LIST3($1, $2, $3);}
| continue semicolon {$$ = PARSER_LIST2($1, $2);}
| break semicolon {$$ = PARSER_LIST2($1, $2);}
| return expression.opt semicolon {$$ = PARSER_LIST3($1, $2, $3);}
;

/* 6.7 External definitions */
top
: translation-unit {scanner_finish(scanner, $1);}
;
translation-unit
: external-declaration {$$ = parser_list_atom(AST_TRANSLATION_UNIT, $1);}
| translation-unit external-declaration {$$ = parser_list_snoc($1, $2);}
;
external-declaration
: function-definition
| declaration {$$ = parser_tag(AST_EXTERNAL_DECLARATION, PARSER_LIST1($1)); register_declaration(scanner, $1);}
;
function-definition
: function-definition.tag {$$ = parser_tag(AST_FUNCTION_DEFINITION, $1);}
;
function-definition.tag
: declarator declaration-list.opt compound-statement {$$ = PARSER_LIST3($1, $2, $3);}
| declaration-specifiers declarator declaration-list.opt compound-statement {$$ = PARSER_LIST4($1, $2, $3, $4);}
;
%%