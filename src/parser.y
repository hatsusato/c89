%code requires {
#include "yyscan.h"
#include "struct.h"
}

%define api.pure full
%define api.value.type {Sexp *}
%param {yyscan_t scanner}

%code provides {
#include "lexer.h"
#include "parser.h"
#include "scanner.h"
#include "sexp.h"
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
: %empty {$$ = PARSER_LIST0();}
| identifier
;
identifier
: TOKEN_IDENTIFIER {$$ = PARSER_TOKEN(identifier, scanner);}
;
typedef-identifier
: TOKEN_TYPEDEF_IDENTIFIER {$$ = PARSER_TOKEN(typedef-identifier, scanner);}
;
floating-constant
: TOKEN_FLOATING_CONSTANT {$$ = PARSER_TOKEN(floating-constant, scanner);}
;
integer-constant
: TOKEN_INTEGER_CONSTANT {$$ = PARSER_TOKEN(integer-constant, scanner);}
;
enumeration-constant
: TOKEN_IDENTIFIER {$$ = PARSER_TOKEN(enumeration-constant, scanner);}
;
character-constant
: TOKEN_CHARACTER_CONSTANT {$$ = PARSER_TOKEN(character-constant, scanner);}
;
string-literal
: TOKEN_STRING_LITERAL {$$ = PARSER_TOKEN(string-literal, scanner);}
;

auto: "auto" {$$ = PARSER_SYMBOL(auto);}
;
break: "break" {$$ = PARSER_SYMBOL(break);}
;
case: "case" {$$ = PARSER_SYMBOL(case);}
;
char: "char" {$$ = PARSER_SYMBOL(char);}
;
const: "const" {$$ = PARSER_SYMBOL(const);}
;
continue: "continue" {$$ = PARSER_SYMBOL(continue);}
;
default: "default" {$$ = PARSER_SYMBOL(default);}
;
do: "do" {$$ = PARSER_SYMBOL(do);}
;
double: "double" {$$ = PARSER_SYMBOL(double);}
;
else: "else" {$$ = PARSER_SYMBOL(else);}
;
enum: "enum" {$$ = PARSER_SYMBOL(enum);}
;
extern: "extern" {$$ = PARSER_SYMBOL(extern);}
;
float: "float" {$$ = PARSER_SYMBOL(float);}
;
for: "for" {$$ = PARSER_SYMBOL(for);}
;
goto: "goto" {$$ = PARSER_SYMBOL(goto);}
;
if: "if" {$$ = PARSER_SYMBOL(if);}
;
int: "int" {$$ = PARSER_SYMBOL(int);}
;
long: "long" {$$ = PARSER_SYMBOL(long);}
;
register: "register" {$$ = PARSER_SYMBOL(register);}
;
return: "return" {$$ = PARSER_SYMBOL(return);}
;
short: "short" {$$ = PARSER_SYMBOL(short);}
;
signed: "signed" {$$ = PARSER_SYMBOL(signed);}
;
sizeof: "sizeof" {$$ = PARSER_SYMBOL(sizeof);}
;
static: "static" {$$ = PARSER_SYMBOL(static);}
;
struct: "struct" {$$ = PARSER_SYMBOL(struct);}
;
switch: "switch" {$$ = PARSER_SYMBOL(switch);}
;
typedef: "typedef" {$$ = PARSER_SYMBOL(typedef);}
;
union: "union" {$$ = PARSER_SYMBOL(union);}
;
unsigned: "unsigned" {$$ = PARSER_SYMBOL(unsigned);}
;
void: "void" {$$ = PARSER_SYMBOL(void);}
;
volatile: "volatile" {$$ = PARSER_SYMBOL(volatile);}
;
while: "while" {$$ = PARSER_SYMBOL(while);}
;

period: "." {$$ = parser_symbol(".");}
;
arrow: "->" {$$ = parser_symbol("->");}
;
increment: "++" {$$ = parser_symbol("++");}
;
decrement: "--" {$$ = parser_symbol("--");}
;
ampersand: "&" {$$ = parser_symbol("&");}
;
asterisk: "*" {$$ = parser_symbol("*");}
;
plus: "+" {$$ = parser_symbol("+");}
;
minus: "-" {$$ = parser_symbol("-");}
;
tilde: "~" {$$ = parser_symbol("~");}
;
exclamation: "!" {$$ = parser_symbol("!");}
;
slash: "/" {$$ = parser_symbol("/");}
;
percent: "%" {$$ = parser_symbol("%");}
;
left-shift: "<<" {$$ = parser_symbol("<<");}
;
right-shift: ">>" {$$ = parser_symbol(">>");}
;
less-than: "<" {$$ = parser_symbol("<");}
;
greater-than: ">" {$$ = parser_symbol(">");}
;
less-equal: "<=" {$$ = parser_symbol("<=");}
;
greater-equal: ">=" {$$ = parser_symbol(">=");}
;
equal: "==" {$$ = parser_symbol("==");}
;
not-equal: "!=" {$$ = parser_symbol("!=");}
;
caret: "^" {$$ = parser_symbol("^");}
;
bar: "|" {$$ = parser_symbol("|");}
;
and: "&&" {$$ = parser_symbol("&&");}
;
or: "||" {$$ = parser_symbol("||");}
;
question: "?" {$$ = parser_symbol("?");}
;
assign: "=" {$$ = parser_symbol("=");}
;
asterisk-assign: "*=" {$$ = parser_symbol("*=");}
;
slash-assign: "/=" {$$ = parser_symbol("/=");}
;
percent-assign: "%=" {$$ = parser_symbol("%=");}
;
plus-assign: "+=" {$$ = parser_symbol("+=");}
;
minus-assign: "-=" {$$ = parser_symbol("-=");}
;
left-shift-assign: "<<=" {$$ = parser_symbol("<<=");}
;
right-shift-assign: ">>=" {$$ = parser_symbol(">>=");}
;
ampersand-assign: "&=" {$$ = parser_symbol("&=");}
;
caret-assign: "^=" {$$ = parser_symbol("^=");}
;
bar-assign: "|=" {$$ = parser_symbol("|=");}
;

left-bracket: "[" {$$ = parser_symbol("[");}
;
right-bracket: "]" {$$ = parser_symbol("]");}
;
left-paren: "(" {$$ = parser_symbol("(");}
;
right-paren: ")" {$$ = parser_symbol(")");}
;
left-brace: "{" {$$ = parser_symbol("{");}
;
right-brace: "}" {$$ = parser_symbol("}");}
;
comma: "," {$$ = parser_symbol(",");}
;
colon: ":" {$$ = parser_symbol(":");}
;
semicolon: ";" {$$ = parser_symbol(";");}
;
ellipsis: "..." {$$ = parser_symbol("...");}
;

/* 6.3 Expressions */
primary-expression
: identifier
| floating-constant
| integer-constant
| character-constant
| string-literal
| left-paren expression right-paren {$$ = PARSER_TAG(primary-expression, PARSER_LIST3($1, $2, $3));}
;
postfix-expression
: primary-expression
| postfix-expression.tag {$$ = PARSER_TAG(postfix-expression, $1);}
;
postfix-expression.tag
: postfix-expression postfix-expression.suffix {$$ = PARSER_CONS($1, $2);}
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
: %empty {$$ = PARSER_NIL(argument-expression-list);}
| argument-expression-list
;
argument-expression-list
: assignment-expression {$$ = PARSER_ATOM(argument-expression-list, $1);}
| argument-expression-list "," assignment-expression {$$ = PARSER_SNOC($1, $3);}
;
unary-expression
: postfix-expression
| unary-expression.tag {$$ = PARSER_TAG(unary-expression, $1);}
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
| cast-expression.tag {$$ = PARSER_TAG(cast-expression, $1);}
;
cast-expression.tag
: left-paren type-name right-paren cast-expression {$$ = PARSER_LIST4($1, $2, $3, $4);}
;
multiplicative-expression
: cast-expression
| multiplicative-expression.tag {$$ = PARSER_TAG(multiplicative-expression, $1);}
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
| additive-expression.tag {$$ = PARSER_TAG(additive-expression, $1);}
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
| shift-expression.tag {$$ = PARSER_TAG(shift-expression, $1);}
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
| relational-expression.tag {$$ = PARSER_TAG(relational-expression, $1);}
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
| equality-expression.tag {$$ = PARSER_TAG(equality-expression, $1);}
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
| and-expression.tag {$$ = PARSER_TAG(and-expression, $1);}
;
and-expression.tag
: and-expression ampersand equality-expression {$$ = PARSER_LIST3($1, $2, $3);}
;
exclusive-or-expression
: and-expression
| exclusive-or-expression.tag {$$ = PARSER_TAG(exclusive-or-expression, $1);}
;
exclusive-or-expression.tag
: exclusive-or-expression caret and-expression {$$ = PARSER_LIST3($1, $2, $3);}
;
inclusive-or-expression
: exclusive-or-expression
| inclusive-or-expression.tag {$$ = PARSER_TAG(inclusive-or-expression, $1);}
;
inclusive-or-expression.tag
: inclusive-or-expression bar exclusive-or-expression {$$ = PARSER_LIST3($1, $2, $3);}
;
logical-and-expression
: inclusive-or-expression
| logical-and-expression.tag {$$ = PARSER_TAG(logical-and-expression, $1);}
;
logical-and-expression.tag
: logical-and-expression and inclusive-or-expression {$$ = PARSER_LIST3($1, $2, $3);}
;
logical-or-expression
: logical-and-expression
| logical-or-expression.tag {$$ = PARSER_TAG(logical-or-expression, $1);}
;
logical-or-expression.tag
: logical-or-expression or logical-and-expression {$$ = PARSER_LIST3($1, $2, $3);}
;
conditional-expression
: logical-or-expression
| conditional-expression.tag {$$ = PARSER_TAG(conditional-expression, $1);}
;
conditional-expression.tag
: logical-or-expression question expression colon conditional-expression {$$ = PARSER_LIST5($1, $2, $3, $4, $5);}
;
assignment-expression
: conditional-expression
| assignment-expression.tag {$$ = PARSER_TAG(assignment-expression, $1);}
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
| expression.tag {$$ = PARSER_TAG(expression, $1);}
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
: conditional-expression {$$ = PARSER_TAG(constant-expression, PARSER_LIST1($1));}
;

/* 6.5 Declarations */
declaration
: declaration.tag {$$ = PARSER_TAG(declaration, $1); scanner_register_typedef(scanner, $$);}
;
declaration.tag
: declaration-specifiers init-declarator-list.opt semicolon {$$ = PARSER_LIST3($1, $2, $3);}
;
declaration-specifiers
: declaration-specifier {$$ = PARSER_ATOM(declaration-specifiers, $1);}
| declaration-specifiers declaration-specifier {$$ = PARSER_SNOC($1, $2);}
;
declaration-specifier
: storage-class-specifier
| type-specifier
| type-qualifier
;
init-declarator-list.opt
: %empty {$$ = PARSER_NIL(init-declarator-list);}
| init-declarator-list
;
init-declarator-list
: init-declarator {$$ = PARSER_ATOM(init-declarator-list, $1);}
| init-declarator-list "," init-declarator {$$ = PARSER_SNOC($1, $3);}
;
init-declarator
: init-declarator.tag {$$ = PARSER_TAG(init-declarator, $1);}
;
init-declarator.tag
: declarator {$$ = PARSER_LIST1($1);}
| declarator assign initializer {$$ = PARSER_LIST3($1, $2, $3);}
;
storage-class-specifier
: storage-class-specifier.tag {$$ = PARSER_TAG(storage-class-specifier, PARSER_LIST1($1));}
;
storage-class-specifier.tag
: typedef
| extern
| static
| auto
| register
;
type-specifier
: type-specifier.tag {$$ = PARSER_TAG(type-specifier, PARSER_LIST1($1));}
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
: struct-or-union-specifier.tag {$$ = PARSER_TAG(struct-or-union-specifier, $1);}
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
: struct-declaration {$$ = PARSER_ATOM(struct-declaration-list, $1);}
| struct-declaration-list struct-declaration {$$ = PARSER_SNOC($1, $2);}
;
struct-declaration
: struct-declaration.tag {$$ = PARSER_TAG(struct-declaration, $1);}
struct-declaration.tag
: specifier-qualifier-list struct-declarator-list semicolon {$$ = PARSER_LIST3($1, $2, $3);}
;
specifier-qualifier-list
: specifier-qualifier {$$ = PARSER_ATOM(specifier-qualifier-list, $1);}
| specifier-qualifier-list specifier-qualifier {$$ = PARSER_SNOC($1, $2);}
;
specifier-qualifier
: type-specifier
| type-qualifier
;
struct-declarator-list
: struct-declarator {$$ = PARSER_ATOM(struct-declarator-list, $1);}
| struct-declarator-list "," struct-declarator {$$ = PARSER_SNOC($1, $3);}
;
struct-declarator
: struct-declarator.tag {$$ = PARSER_TAG(struct-declarator, $1);}
;
struct-declarator.tag
: declarator {$$ = PARSER_LIST1($1);}
| declarator.opt colon constant-expression {$$ = PARSER_LIST3($1, $2, $3);}
;
enum-specifier
: enum-specifier.tag {$$ = PARSER_TAG(enum-specifier, $1);}
;
enum-specifier.tag
: enum identifier.opt left-brace enumerator-list right-brace {$$ = PARSER_LIST5($1, $2, $3, $4, $5);}
| enum identifier {$$ = PARSER_LIST2($1, $2);}
;
enumerator-list
: enumerator {$$ = PARSER_ATOM(enumerator-list, $1);}
| enumerator-list "," enumerator {$$ = PARSER_SNOC($1, $3);}
;
enumerator
: enumerator.tag {$$ = PARSER_TAG(enumerator, $1);}
;
enumerator.tag
: enumeration-constant {$$ = PARSER_LIST1($1);}
| enumeration-constant assign constant-expression {$$ = PARSER_LIST3($1, $2, $3);}
;
type-qualifier
: type-qualifier.tag {$$ = PARSER_TAG(type-qualifier, PARSER_LIST1($1));}
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
: declarator.tag {$$ = PARSER_TAG(declarator, $1);}
;
declarator.tag
: direct-declarator {$$ = PARSER_LIST1($1);}
| pointer direct-declarator {$$ = PARSER_LIST2($1, $2);}
;
direct-declarator
: direct-declarator.tag {$$ = PARSER_TAG(direct-declarator, $1);}
;
direct-declarator.tag
: identifier {$$ = PARSER_LIST1($1);}
| left-paren declarator right-paren {$$ = PARSER_LIST3($1, $2, $3);}
| direct-declarator direct-declarator.suffix {$$ = PARSER_CONS($1, $2);}
;
direct-declarator.suffix
: left-bracket constant-expression.opt right-bracket {$$ = PARSER_LIST3($1, $2, $3);}
| left-paren parameter-type-list.opt right-paren {$$ = PARSER_LIST3($1, $2, $3);}
| left-paren identifier-list right-paren {$$ = PARSER_LIST3($1, $2, $3);}
;
pointer
: pointer.tag {$$ = PARSER_TAG(pointer, $1);}
;
pointer.tag
: asterisk type-qualifier-list.opt {$$ = PARSER_LIST2($1, $2);}
| pointer asterisk type-qualifier-list.opt {$$ = PARSER_LIST3($1, $2, $3);}
;
type-qualifier-list.opt
: %empty {$$ = PARSER_NIL(type-qualifier-list);}
| type-qualifier-list
;
type-qualifier-list
: type-qualifier {$$ = PARSER_ATOM(type-qualifier-list, $1);}
| type-qualifier-list type-qualifier {$$ = PARSER_SNOC($1, $2);}
;
parameter-type-list.opt
: %empty {$$ = PARSER_NIL(parameter-list);}
| parameter-type-list
;
parameter-type-list
: parameter-list
| parameter-list "," ellipsis {$$ = PARSER_SNOC($1, $3);}
;
parameter-list
: parameter-declaration {$$ = PARSER_ATOM(parameter-list, $1);}
| parameter-list "," parameter-declaration {$$ = PARSER_SNOC($1, $3);}
;
parameter-declaration
: parameter-declaration.tag {$$ = PARSER_TAG(parameter-declaration, $1);}
;
parameter-declaration.tag
: declaration-specifiers declarator {$$ = PARSER_LIST2($1, $2);}
| declaration-specifiers abstract-declarator.opt {$$ = PARSER_LIST2($1, $2);}
;
identifier-list
: identifier {$$ = PARSER_ATOM(identifier-list, $1);}
| identifier-list "," identifier {$$ = PARSER_SNOC($1, $3);}
;
type-name
: type-name.tag {$$ = PARSER_TAG(type-name, $1);}
;
type-name.tag
: specifier-qualifier-list abstract-declarator.opt {$$ = PARSER_LIST2($1, $2);}
;
abstract-declarator.opt
: %empty {$$ = PARSER_LIST0();}
| abstract-declarator
;
abstract-declarator
: abstract-declarator.tag {$$ = PARSER_TAG(abstract-declarator, $1);}
;
abstract-declarator.tag
: pointer {$$ = PARSER_LIST1($1);}
| direct-abstract-declarator {$$ = PARSER_LIST1($1);}
| pointer direct-abstract-declarator {$$ = PARSER_LIST2($1, $2);}
;
direct-abstract-declarator
: direct-abstract-declarator.tag {$$ = PARSER_TAG(direct-abstract-declarator, $1);}
;
direct-abstract-declarator.tag
: left-paren abstract-declarator right-paren {$$ = PARSER_LIST3($1, $2, $3);}
| direct-abstract-declarator.suffix
| direct-abstract-declarator direct-abstract-declarator.suffix {$$ = PARSER_CONS($1, $2);}
;
direct-abstract-declarator.suffix
: left-bracket constant-expression.opt right-bracket {$$ = PARSER_LIST3($1, $2, $3);}
| left-paren parameter-type-list.opt right-paren {$$ = PARSER_LIST3($1, $2, $3);}
;
typedef-name
: typedef-identifier {$$ = PARSER_TAG(typedef-name, PARSER_LIST1($1));}
;
initializer
: assignment-expression
| initializer.tag {$$ = PARSER_TAG(initializer, $1);}
;
initializer.tag
: left-brace initializer-list right-brace {$$ = PARSER_LIST3($1, $2, $3);}
| left-brace initializer-list comma right-brace {$$ = PARSER_LIST4($1, $2, $3, $4);}
;
initializer-list
: initializer {$$ = PARSER_ATOM(initializer-list, $1);}
| initializer-list "," initializer {$$ = PARSER_SNOC($1, $3);}
;

/* 6.6 Statements */
statement
: statement.tag {$$ = PARSER_TAG(statement, PARSER_LIST1($1));}
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
: labeled-statement.tag {$$ = PARSER_TAG(labeled-statement, $1);}
;
labeled-statement.tag
: identifier colon statement {$$ = PARSER_LIST3($1, $2, $3);}
| case constant-expression colon statement {$$ = PARSER_LIST4($1, $2, $3, $4);}
| default colon statement {$$ = PARSER_LIST3($1, $2, $3);}
;
new-scope
: %empty {scanner_push_scope(scanner);}
;
compound-statement
: new-scope compound-statement.tag {$$ = PARSER_TAG(compound-statement, $2);}
;
compound-statement.tag
: left-brace declaration-list.opt statement-list.opt right-brace {$$ = PARSER_LIST4($1, $2, $3, $4); scanner_pop_scope(scanner);}
;
declaration-list.opt
: %empty {$$ = PARSER_NIL(declaration-list);}
| declaration-list
;
declaration-list
: declaration {$$ = PARSER_ATOM(declaration-list, $1);}
| declaration-list declaration {$$ = PARSER_SNOC($1, $2);}
;
statement-list.opt
: %empty {$$ = PARSER_NIL(statement-list);}
| statement-list
;
statement-list
: statement {$$ = PARSER_ATOM(statement-list, $1);}
| statement-list statement {$$ = PARSER_SNOC($1, $2);}
;
expression-statement
: expression-statement.tag {$$ = PARSER_TAG(expression-statement, $1);}
;
expression-statement.tag
: expression.opt semicolon {$$ = PARSER_LIST2($1, $2);}
;
selection-statement
: selection-statement.tag {$$ = PARSER_TAG(selection-statement, $1);}
;
selection-statement.tag
: if left-paren expression right-paren statement %prec THEN {$$ = PARSER_LIST5($1, $2, $3, $4, $5);}
| if left-paren expression right-paren statement else statement {$$ = PARSER_LIST7($1, $2, $3, $4, $5, $6, $7);}
| switch left-paren expression right-paren statement {$$ = PARSER_LIST5($1, $2, $3, $4, $5);}
;
iteration-statement
: iteration-statement.tag {$$ = PARSER_TAG(iteration-statement, $1);}
;
iteration-statement.tag
: while left-paren expression right-paren statement {$$ = PARSER_LIST5($1, $2, $3, $4, $5);}
| do statement while left-paren expression right-paren semicolon {$$ = PARSER_LIST7($1, $2, $3, $4, $5, $6, $7);}
| for left-paren expression.opt semicolon expression.opt semicolon expression.opt right-paren statement {$$ = PARSER_LIST9($1, $2, $3, $4, $5, $6, $7, $8, $9);}
;
jump-statement
: jump-statement.tag {$$ = PARSER_TAG(jump-statement, $1);}
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
: external-declaration {$$ = PARSER_ATOM(translation-unit, $1);}
| translation-unit external-declaration {$$ = PARSER_SNOC($1, $2);}
;
external-declaration
: function-definition
| declaration {$$ = PARSER_TAG(external-declaration, PARSER_LIST1($1));}
;
function-definition
: function-definition.tag {$$ = PARSER_TAG(function-definition, $1);}
;
function-definition.tag
: declarator declaration-list.opt compound-statement {$$ = PARSER_LIST3($1, $2, $3);}
| declaration-specifiers declarator declaration-list.opt compound-statement {$$ = PARSER_LIST4($1, $2, $3, $4);}
;
%%
