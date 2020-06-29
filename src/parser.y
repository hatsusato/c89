%code top {
}
%code requires {
#include "ast.h"
#include "scanner.h"
}

%define api.pure full
%define api.value.type {Sexp *}
%param {yyscan_t scanner}

%code provides {
#include "lexer.h"
#include "parser.h"
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
: %empty {$$ = sexp_nil();}
| identifier
;
identifier
: TOKEN_IDENTIFIER {$$ = PARSER_TAG(identifier, scanner_token(scanner));}
;
typedef-identifier
: TOKEN_TYPEDEF_IDENTIFIER {$$ = PARSER_TAG(typedef-identifier, scanner_token(scanner));}
;
floating-constant
: TOKEN_FLOATING_CONSTANT {$$ = PARSER_TAG(floating-constant, scanner_token(scanner));}
;
integer-constant
: TOKEN_INTEGER_CONSTANT {$$ = PARSER_TAG(integer-constant, scanner_token(scanner));}
;
enumeration-constant
: TOKEN_IDENTIFIER {$$ = PARSER_TAG(enumeration-constant, scanner_token(scanner));}
;
character-constant
: TOKEN_CHARACTER_CONSTANT {$$ = PARSER_TAG(character-constant, scanner_token(scanner));}
;
string-literal
: TOKEN_STRING_LITERAL {$$ = PARSER_TAG(string-literal, scanner_token(scanner));}
;

auto: "auto" {$$ = sexp_symbol("auto");}
;
break: "break" {$$ = sexp_symbol("break");}
;
case: "case" {$$ = sexp_symbol("case");}
;
char: "char" {$$ = sexp_symbol("char");}
;
const: "const" {$$ = sexp_symbol("const");}
;
continue: "continue" {$$ = sexp_symbol("continue");}
;
default: "default" {$$ = sexp_symbol("default");}
;
do: "do" {$$ = sexp_symbol("do");}
;
double: "double" {$$ = sexp_symbol("double");}
;
else: "else" {$$ = sexp_symbol("else");}
;
enum: "enum" {$$ = sexp_symbol("enum");}
;
extern: "extern" {$$ = sexp_symbol("extern");}
;
float: "float" {$$ = sexp_symbol("float");}
;
for: "for" {$$ = sexp_symbol("for");}
;
goto: "goto" {$$ = sexp_symbol("goto");}
;
if: "if" {$$ = sexp_symbol("if");}
;
int: "int" {$$ = sexp_symbol("int");}
;
long: "long" {$$ = sexp_symbol("long");}
;
register: "register" {$$ = sexp_symbol("register");}
;
return: "return" {$$ = sexp_symbol("return");}
;
short: "short" {$$ = sexp_symbol("short");}
;
signed: "signed" {$$ = sexp_symbol("signed");}
;
sizeof: "sizeof" {$$ = sexp_symbol("sizeof");}
;
static: "static" {$$ = sexp_symbol("static");}
;
struct: "struct" {$$ = sexp_symbol("struct");}
;
switch: "switch" {$$ = sexp_symbol("switch");}
;
typedef: "typedef" {$$ = sexp_symbol("typedef");}
;
union: "union" {$$ = sexp_symbol("union");}
;
unsigned: "unsigned" {$$ = sexp_symbol("unsigned");}
;
void: "void" {$$ = sexp_symbol("void");}
;
volatile: "volatile" {$$ = sexp_symbol("volatile");}
;
while: "while" {$$ = sexp_symbol("while");}
;

period: "." {$$ = sexp_symbol(".");}
;
arrow: "->" {$$ = sexp_symbol("->");}
;
increment: "++" {$$ = sexp_symbol("++");}
;
decrement: "--" {$$ = sexp_symbol("--");}
;
ampersand: "&" {$$ = sexp_symbol("&");}
;
asterisk: "*" {$$ = sexp_symbol("*");}
;
plus: "+" {$$ = sexp_symbol("+");}
;
minus: "-" {$$ = sexp_symbol("-");}
;
tilde: "~" {$$ = sexp_symbol("~");}
;
exclamation: "!" {$$ = sexp_symbol("!");}
;
slash: "/" {$$ = sexp_symbol("/");}
;
percent: "%" {$$ = sexp_symbol("%");}
;
left-shift: "<<" {$$ = sexp_symbol("<<");}
;
right-shift: ">>" {$$ = sexp_symbol(">>");}
;
less-than: "<" {$$ = sexp_symbol("<");}
;
greater-than: ">" {$$ = sexp_symbol(">");}
;
less-equal: "<=" {$$ = sexp_symbol("<=");}
;
greater-equal: ">=" {$$ = sexp_symbol(">=");}
;
equal: "==" {$$ = sexp_symbol("==");}
;
not-equal: "!=" {$$ = sexp_symbol("!=");}
;
caret: "^" {$$ = sexp_symbol("^");}
;
bar: "|" {$$ = sexp_symbol("|");}
;
and: "&&" {$$ = sexp_symbol("&&");}
;
or: "||" {$$ = sexp_symbol("||");}
;
question: "?" {$$ = sexp_symbol("?");}
;
assign: "=" {$$ = sexp_symbol("=");}
;
asterisk-assign: "*=" {$$ = sexp_symbol("*=");}
;
slash-assign: "/=" {$$ = sexp_symbol("/=");}
;
percent-assign: "%=" {$$ = sexp_symbol("%=");}
;
plus-assign: "+=" {$$ = sexp_symbol("+=");}
;
minus-assign: "-=" {$$ = sexp_symbol("-=");}
;
left-shift-assign: "<<=" {$$ = sexp_symbol("<<=");}
;
right-shift-assign: ">>=" {$$ = sexp_symbol(">>=");}
;
ampersand-assign: "&=" {$$ = sexp_symbol("&=");}
;
caret-assign: "^=" {$$ = sexp_symbol("^=");}
;
bar-assign: "|=" {$$ = sexp_symbol("|=");}
;

left-bracket: "[" {$$ = sexp_symbol("[");}
;
right-bracket: "]" {$$ = sexp_symbol("]");}
;
left-paren: "(" {$$ = sexp_symbol("(");}
;
right-paren: ")" {$$ = sexp_symbol(")");}
;
left-brace: "{" {$$ = sexp_symbol("{");}
;
right-brace: "}" {$$ = sexp_symbol("}");}
;
comma: "," {$$ = sexp_symbol(",");}
;
colon: ":" {$$ = sexp_symbol(":");}
;
semicolon: ";" {$$ = sexp_symbol(";");}
;
ellipsis: "..." {$$ = sexp_symbol("...");}
;

/* 6.3 Expressions */
primary-expression
: identifier
| floating-constant
| integer-constant
| character-constant
| string-literal
| left-paren expression right-paren {$$ = PARSER_TAG(primary-expression, sexp_list3($1, $2, $3));}
;
postfix-expression
: primary-expression
| postfix-expression.tag {$$ = PARSER_TAG(postfix-expression, $1);}
;
postfix-expression.tag
: postfix-expression left-bracket expression right-bracket {$$ = sexp_list4($1, $2, $3, $4);}
| postfix-expression left-paren argument-expression-list.opt right-paren {$$ = sexp_list4($1, $2, $3, $4);}
| postfix-expression period identifier {$$ = sexp_list3($1, $2, $3);}
| postfix-expression arrow identifier {$$ = sexp_list3($1, $2, $3);}
| postfix-expression increment {$$ = sexp_list2($1, $2);}
| postfix-expression decrement {$$ = sexp_list2($1, $2);}
;
argument-expression-list.opt
: %empty {$$ = PARSER_TAG(argument-expression-list, sexp_nil());}
| argument-expression-list
;
argument-expression-list
: assignment-expression {$$ = PARSER_TAG(argument-expression-list, sexp_list1($1));}
| argument-expression-list comma assignment-expression {$$ = parser_sexp_push($1, sexp_list2($2, $3));}
;
unary-expression
: postfix-expression
| unary-expression.tag {$$ = PARSER_TAG(unary-expression, $1);}
;
unary-expression.tag
: increment unary-expression {$$ = sexp_list2($1, $2);}
| decrement unary-expression {$$ = sexp_list2($1, $2);}
| unary-operator cast-expression {$$ = sexp_list2($1, $2);}
| sizeof unary-expression {$$ = sexp_list2($1, $2);}
| sizeof left-paren type-name right-paren {$$ = sexp_list4($1, $2, $3, $4);}
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
: left-paren type-name right-paren cast-expression {$$ = sexp_list4($1, $2, $3, $4);}
;
multiplicative-expression
: cast-expression
| multiplicative-expression.tag {$$ = PARSER_TAG(multiplicative-expression, $1);}
;
multiplicative-expression.tag
: multiplicative-expression multiplicative-operator cast-expression {$$ = sexp_list3($1, $2, $3);}
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
: additive-expression additive-operator multiplicative-expression {$$ = sexp_list3($1, $2, $3);}
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
: shift-expression shift-operator additive-expression {$$ = sexp_list3($1, $2, $3);}
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
: relational-expression relational-operator shift-expression {$$ = sexp_list3($1, $2, $3);}
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
: equality-expression equality-operator relational-expression {$$ = sexp_list3($1, $2, $3);}
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
: and-expression ampersand equality-expression {$$ = sexp_list3($1, $2, $3);}
;
exclusive-or-expression
: and-expression
| exclusive-or-expression exclusive-or-operator and-expression {$$ = PARSER_LIST3($1, $2, $3);}
;
exclusive-or-operator
: caret {$$ = $1;}
;
inclusive-or-expression
: exclusive-or-expression
| inclusive-or-expression inclusive-or-operator exclusive-or-expression {$$ = PARSER_LIST3($1, $2, $3);}
;
inclusive-or-operator
: bar {$$ = $1;}
;
logical-and-expression
: inclusive-or-expression
| logical-and-expression logical-and-operator inclusive-or-expression {$$ = PARSER_LIST3($1, $2, $3);}
;
logical-and-operator
: and {$$ = $1;}
;
logical-or-expression
: logical-and-expression
| logical-or-expression logical-or-operator logical-and-expression {$$ = PARSER_LIST3($1, $2, $3);}
;
logical-or-operator
: or {$$ = $1;}
;
conditional-expression
: logical-or-expression
| logical-or-expression question expression colon conditional-expression {$$ = PARSER_LIST5($1, $2, $3, $4, $5);}
;
assignment-expression
: conditional-expression
| unary-expression assignment-operator assignment-expression {$$ = PARSER_LIST3($1, $2, $3);}
;
assignment-operator
: assign {$$ = $1;}
| asterisk-assign {$$ = $1;}
| slash-assign {$$ = $1;}
| percent-assign {$$ = $1;}
| plus-assign {$$ = $1;}
| minus-assign {$$ = $1;}
| left-shift-assign {$$ = $1;}
| right-shift-assign {$$ = $1;}
| ampersand-assign {$$ = $1;}
| caret-assign {$$ = $1;}
| bar-assign {$$ = $1;}
;
expression.opt
: %empty {$$ = sexp_nil();}
| expression
;
expression
: assignment-expression
| expression comma-operator assignment-expression {$$ = PARSER_LIST3($1, $2, $3);}
;
comma-operator
: comma {$$ = $1;}
;

/* 6.4 Constant expressions */
constant-expression.opt
: %empty {$$ = sexp_nil();}
| constant-expression
;
constant-expression
: conditional-expression {$$ = $1;}
;

/* 6.5 Declarations */
declaration
: declaration-specifiers semicolon {$$ = PARSER_LIST2($1, $2);}
| declaration-specifiers init-declarator-list semicolon {$$ = PARSER_LIST3($1, $2, $3);}
;
declaration-specifiers
: declaration-specifier {$$ = PARSER_LIST1($1);}
| declaration-specifiers declaration-specifier {$$ = sexp_snoc($1, $2);}
;
declaration-specifier
: storage-class-specifier
| type-specifier
| type-qualifier
;
init-declarator-list
: init-declarator {$$ = PARSER_LIST1($1);}
| init-declarator-list comma init-declarator {$$ = sexp_snoc($1, PARSER_LIST2($2, $3));}
;
init-declarator
: declarator {$$ = $1;}
| declarator assign initializer {$$ = PARSER_LIST3($1, $2, $3);}
;
storage-class-specifier
: storage-class-specifier.prefix {$$ = $1;}
;
storage-class-specifier.prefix
: typedef {$$ = $1;}
| extern {$$ = $1;}
| static {$$ = $1;}
| auto {$$ = $1;}
| register {$$ = $1;}
;
type-specifier
: type-specifier.prefix {$$ = $1;}
;
type-specifier.prefix
: void {$$ = $1;}
| char {$$ = $1;}
| short {$$ = $1;}
| int {$$ = $1;}
| long {$$ = $1;}
| float {$$ = $1;}
| double {$$ = $1;}
| signed {$$ = $1;}
| unsigned {$$ = $1;}
| struct-or-union-specifier
| enum-specifier
| typedef-name
;
struct-or-union-specifier
: struct-or-union identifier.opt left-brace struct-declaration-list right-brace {$$ = PARSER_LIST5($1, $2, $3, $4, $5);}
| struct-or-union identifier {$$ = PARSER_LIST2($1, $2);}
;
struct-or-union
: struct {$$ = $1;}
| union {$$ = $1;}
;
struct-declaration-list
: struct-declaration {$$ = PARSER_LIST1($1);}
| struct-declaration-list struct-declaration {$$ = sexp_snoc($1, $2);}
;
struct-declaration
: specifier-qualifier-list struct-declarator-list semicolon {$$ = PARSER_LIST3($1, $2, $3);}
;
specifier-qualifier-list
: specifier-qualifier {$$ = PARSER_LIST1($1);}
| specifier-qualifier-list specifier-qualifier {$$ = sexp_snoc($1, $2);}
;
specifier-qualifier
: type-specifier
| type-qualifier
;
struct-declarator-list
: struct-declarator {$$ = PARSER_LIST1($1);}
| struct-declarator-list comma struct-declarator {$$ = sexp_snoc($1, PARSER_LIST2($2, $3));}
;
struct-declarator
: declarator {$$ = $1;}
| declarator.opt colon constant-expression {$$ = PARSER_LIST3($1, $2, $3);}
;
enum-specifier
: enum identifier.opt left-brace enumerator-list right-brace {$$ = PARSER_LIST5($1, $2, $3, $4, $5);}
| enum identifier {$$ = PARSER_LIST2($1, $2);}
;
enumerator-list
: enumerator {$$ = PARSER_LIST1($1);}
| enumerator-list comma enumerator {$$ = sexp_snoc($1, PARSER_LIST2($2, $3));}
;
enumerator
: enumeration-constant {$$ = $1;}
| enumeration-constant assign constant-expression {$$ = PARSER_LIST3($1, $2, $3);}
;
type-qualifier
: type-qualifier.prefix {$$ = $1;}
;
type-qualifier.prefix
: const {$$ = $1;}
| volatile {$$ = $1;}
;
declarator.opt
: %empty {$$ = sexp_nil();}
| declarator
;
declarator
: direct-declarator {$$ = sexp_list2(sexp_nil(), $1);}
| pointer direct-declarator {$$ = PARSER_LIST2($1, $2);}
;
direct-declarator
: direct-declarator.prefix
| direct-declarator direct-declarator.suffix {$$ = PARSER_LIST2($1, $2);}
;
direct-declarator.prefix
: identifier
| "(" declarator ")" {$$ = sexp_list3(sexp_symbol("("), $2, sexp_symbol(")"));}
;
direct-declarator.suffix
: left-bracket constant-expression.opt right-bracket {$$ = PARSER_LIST3($1, $2, $3);}
| left-paren parameter-type-list right-paren {$$ = PARSER_LIST3($1, $2, $3);}
| left-paren identifier-list.opt right-paren {$$ = PARSER_LIST3($1, $2, $3);}
;
pointer
: pointer.prefix {$$ = $1;}
| pointer.prefix pointer {$$ = PARSER_LIST2($1, $2);}
;
pointer.prefix
: asterisk type-qualifier-list.opt {$$ = PARSER_LIST2($1, $2);}
;
type-qualifier-list.opt
: %empty {$$ = sexp_nil();}
| type-qualifier-list
;
type-qualifier-list
: type-qualifier {$$ = PARSER_LIST1($1);}
| type-qualifier-list type-qualifier {$$ = sexp_snoc($1, $2);}
;
parameter-type-list.opt
: %empty {$$ = sexp_nil();}
| parameter-type-list
;
parameter-type-list
: parameter-list
| parameter-list comma ellipsis {$$ = PARSER_LIST3($1, $2, $3);}
;
parameter-list
: parameter-declaration {$$ = PARSER_LIST1($1);}
| parameter-list comma parameter-declaration {$$ = sexp_snoc($1, PARSER_LIST2($2, $3));}
;
parameter-declaration
: declaration-specifiers {$$ = $1;}
| declaration-specifiers parameter-declaration.suffix {$$ = PARSER_LIST2($1, $2);}
;
parameter-declaration.suffix
: declarator
| abstract-declarator
;
identifier-list.opt
: %empty {$$ = sexp_nil();}
| identifier-list
;
identifier-list
: identifier {$$ = PARSER_LIST1($1);}
| identifier-list comma identifier {$$ = sexp_snoc($1, PARSER_LIST2($2, $3));}
;
type-name
: specifier-qualifier-list {$$ = $1;}
| specifier-qualifier-list abstract-declarator {$$ = PARSER_LIST2($1, $2);}
;
abstract-declarator
: abstract-declarator.prefix {$$ = $1;}
| pointer direct-abstract-declarator {$$ = PARSER_LIST2($1, $2);}
;
abstract-declarator.prefix
: pointer
| direct-abstract-declarator
;
direct-abstract-declarator
: "(" abstract-declarator ")" {$$ = sexp_list3(sexp_symbol("("), $2, sexp_symbol(")"));}
| direct-abstract-declarator.suffix
| direct-abstract-declarator direct-abstract-declarator.suffix {$$ = PARSER_LIST2($1, $2);}
;
direct-abstract-declarator.suffix
: left-bracket constant-expression.opt right-bracket {$$ = PARSER_LIST3($1, $2, $3);}
| left-paren parameter-type-list.opt right-paren {$$ = PARSER_LIST3($1, $2, $3);}
;
typedef-name
: typedef-identifier {$$ = $1;}
;
initializer
: assignment-expression
| initializer.suffix {$$ = $1;}
;
initializer.suffix
: "{" initializer-list "}" {$$ = sexp_list3(sexp_symbol("{"), $2, sexp_symbol("}"));}
| "{" initializer-list comma "}" {$$ = sexp_list4(sexp_symbol("{"), $2, $3, sexp_symbol("}"));}
;
initializer-list
: initializer {$$ = PARSER_LIST1($1);}
| initializer-list comma initializer {$$ = sexp_snoc($1, PARSER_LIST2($2, $3));}
;

/* 6.6 Statements */
statement
: statement.prefix {$$ = $1;}
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
: labeled-statement.prefix colon statement {$$ = PARSER_LIST3($1, $2, $3);}
;
labeled-statement.prefix
: identifier
| case constant-expression {$$ = PARSER_LIST2($1, $2);}
| default {$$ = $1;}
;
compound-statement
: left-brace declaration-list.opt statement-list.opt right-brace {$$ = PARSER_LIST4($1, $2, $3, $4);}
;
declaration-list.opt
: %empty {$$ = sexp_nil();}
| declaration-list
;
declaration-list
: declaration {$$ = PARSER_LIST1($1);}
| declaration-list declaration {$$ = sexp_snoc($1, $2);}
;
statement-list.opt
: %empty {$$ = sexp_nil();}
| statement-list
;
statement-list
: statement {$$ = PARSER_LIST1($1);}
| statement-list statement {$$ = sexp_snoc($1, $2);}
;
expression-statement
: expression.opt semicolon {$$ = PARSER_LIST2($1, $2);}
;
selection-statement
: selection-statement.suffix {$$ = $1;}
;
selection-statement.suffix
: if selection-statement.if {$$ = sexp_cons($1, $2);}
| switch selection-statement.switch {$$ = sexp_cons($1, $2);}
;
selection-statement.if
: "(" expression ")" statement %prec THEN {$$ = sexp_list4(sexp_symbol("("), $2, sexp_symbol(")"), $4);}
| "(" expression ")" statement else statement {$$ = sexp_list6(sexp_symbol("("), $2, sexp_symbol(")"), $4, $5, $6);}
;
selection-statement.switch
: left-paren expression right-paren statement {$$ = PARSER_LIST4($1, $2, $3, $4);}
;
iteration-statement
: iteration-statement.suffix {$$ = $1;}
;
iteration-statement.suffix
: while iteration-statement.while {$$ = sexp_cons($1, $2);}
| do iteration-statement.do {$$ = sexp_cons($1, $2);}
| for iteration-statement.for {$$ = sexp_cons($1, $2);}
;
iteration-statement.while
: left-paren expression right-paren statement {$$ = PARSER_LIST4($1, $2, $3, $4);}
;
iteration-statement.do
: statement while left-paren expression right-paren semicolon {$$ = PARSER_LIST6($1, $2, $3, $4, $5, $6);}
;
iteration-statement.for
: left-paren expression.opt semicolon expression.opt semicolon expression.opt right-paren statement {$$ = sexp_list4($1, PARSER_LIST5($2, $3, $4, $5, $6), $7, $8);}
;
jump-statement
: jump-statement.suffix semicolon {$$ = sexp_snoc($1, $2);}
;
jump-statement.suffix
: goto identifier {$$ = PARSER_LIST2($1, $2);}
| continue {$$ = PARSER_LIST1($1);}
| break {$$ = PARSER_LIST1($1);}
| return expression.opt {$$ = PARSER_LIST2($1, $2);}
;

/* 6.7 External definitions */
top
: translation-unit {scanner_finish(scanner, $1);}
;
translation-unit
: external-declaration {$$ = PARSER_LIST1($1);}
| translation-unit external-declaration {$$ = sexp_snoc($1, $2);}
;
external-declaration
: function-definition
| declaration {$$ = $1;}
;
function-definition
: function-definition.old {$$ = $1;}
| declaration-specifiers declarator compound-statement {$$ = PARSER_LIST3($1, $2, $3);}
;
function-definition.old
: declarator compound-statement {$$ = PARSER_LIST2($1, $2);}
| declarator declaration-list compound-statement {$$ = PARSER_LIST3($1, $2, $3);}
| declaration-specifiers declarator declaration-list compound-statement {$$ = PARSER_LIST4($1, $2, $3, $4);}
;
%%
