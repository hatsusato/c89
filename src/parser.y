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
: %empty {$$.sexp = sexp_nil();}
| identifier
;
identifier
: TOKEN_IDENTIFIER {$$.sexp = sexp_list2(sexp_symbol("identifier"), scanner_token(scanner));}
;
typedef-identifier
: TOKEN_TYPEDEF_IDENTIFIER {$$.sexp = sexp_list2(sexp_symbol("typedef-identifier"), scanner_token(scanner));}
;
floating-constant
: TOKEN_FLOATING_CONSTANT {$$.sexp = sexp_list2(sexp_symbol("floating-constant"), scanner_token(scanner));}
;
integer-constant
: TOKEN_INTEGER_CONSTANT {$$.sexp = sexp_list2(sexp_symbol("integer-constant"), scanner_token(scanner));}
;
enumeration-constant
: TOKEN_IDENTIFIER {$$.sexp = sexp_list2(sexp_symbol("enumeration-constant"), scanner_token(scanner));}
;
character-constant
: TOKEN_CHARACTER_CONSTANT {$$.sexp = sexp_list2(sexp_symbol("character-constant"), scanner_token(scanner));}
;
string-literal
: TOKEN_STRING_LITERAL {$$.sexp = sexp_list2(sexp_symbol("string-literal"), scanner_token(scanner));}
;

auto: "auto" {$$.sexp = sexp_symbol("auto");}
;
break: "break" {$$.sexp = sexp_symbol("break");}
;
case: "case" {$$.sexp = sexp_symbol("case");}
;
char: "char" {$$.sexp = sexp_symbol("char");}
;
const: "const" {$$.sexp = sexp_symbol("const");}
;
continue: "continue" {$$.sexp = sexp_symbol("continue");}
;
default: "default" {$$.sexp = sexp_symbol("default");}
;
do: "do" {$$.sexp = sexp_symbol("do");}
;
double: "double" {$$.sexp = sexp_symbol("double");}
;
else: "else" {$$.sexp = sexp_symbol("else");}
;
enum: "enum" {$$.sexp = sexp_symbol("enum");}
;
extern: "extern" {$$.sexp = sexp_symbol("extern");}
;
float: "float" {$$.sexp = sexp_symbol("float");}
;
for: "for" {$$.sexp = sexp_symbol("for");}
;
goto: "goto" {$$.sexp = sexp_symbol("goto");}
;
if: "if" {$$.sexp = sexp_symbol("if");}
;
int: "int" {$$.sexp = sexp_symbol("int");}
;
long: "long" {$$.sexp = sexp_symbol("long");}
;
register: "register" {$$.sexp = sexp_symbol("register");}
;
return: "return" {$$.sexp = sexp_symbol("return");}
;
short: "short" {$$.sexp = sexp_symbol("short");}
;
signed: "signed" {$$.sexp = sexp_symbol("signed");}
;
sizeof: "sizeof" {$$.sexp = sexp_symbol("sizeof");}
;
static: "static" {$$.sexp = sexp_symbol("static");}
;
struct: "struct" {$$.sexp = sexp_symbol("struct");}
;
switch: "switch" {$$.sexp = sexp_symbol("switch");}
;
typedef: "typedef" {$$.sexp = sexp_symbol("typedef");}
;
union: "union" {$$.sexp = sexp_symbol("union");}
;
unsigned: "unsigned" {$$.sexp = sexp_symbol("unsigned");}
;
void: "void" {$$.sexp = sexp_symbol("void");}
;
volatile: "volatile" {$$.sexp = sexp_symbol("volatile");}
;
while: "while" {$$.sexp = sexp_symbol("while");}
;

period: "." {$$.sexp = sexp_symbol(".");}
;
arrow: "->" {$$.sexp = sexp_symbol("->");}
;
increment: "++" {$$.sexp = sexp_symbol("++");}
;
decrement: "--" {$$.sexp = sexp_symbol("--");}
;
ampersand: "&" {$$.sexp = sexp_symbol("&");}
;
asterisk: "*" {$$.sexp = sexp_symbol("*");}
;
plus: "+" {$$.sexp = sexp_symbol("+");}
;
minus: "-" {$$.sexp = sexp_symbol("-");}
;
tilde: "~" {$$.sexp = sexp_symbol("~");}
;
exclamation: "!" {$$.sexp = sexp_symbol("!");}
;
slash: "/" {$$.sexp = sexp_symbol("/");}
;
percent: "%" {$$.sexp = sexp_symbol("%");}
;
left-shift: "<<" {$$.sexp = sexp_symbol("<<");}
;
right-shift: ">>" {$$.sexp = sexp_symbol(">>");}
;
less-than: "<" {$$.sexp = sexp_symbol("<");}
;
greater-than: ">" {$$.sexp = sexp_symbol(">");}
;
less-equal: "<=" {$$.sexp = sexp_symbol("<=");}
;
greater-equal: ">=" {$$.sexp = sexp_symbol(">=");}
;
equal: "==" {$$.sexp = sexp_symbol("==");}
;
not-equal: "!=" {$$.sexp = sexp_symbol("!=");}
;
caret: "^" {$$.sexp = sexp_symbol("^");}
;
bar: "|" {$$.sexp = sexp_symbol("|");}
;
and: "&&" {$$.sexp = sexp_symbol("&&");}
;
or: "||" {$$.sexp = sexp_symbol("||");}
;
question: "?" {$$.sexp = sexp_symbol("?");}
;
assign: "=" {$$.sexp = sexp_symbol("=");}
;
asterisk-assign: "*=" {$$.sexp = sexp_symbol("*=");}
;
slash-assign: "/=" {$$.sexp = sexp_symbol("/=");}
;
percent-assign: "%=" {$$.sexp = sexp_symbol("%=");}
;
plus-assign: "+=" {$$.sexp = sexp_symbol("+=");}
;
minus-assign: "-=" {$$.sexp = sexp_symbol("-=");}
;
left-shift-assign: "<<=" {$$.sexp = sexp_symbol("<<=");}
;
right-shift-assign: ">>=" {$$.sexp = sexp_symbol(">>=");}
;
ampersand-assign: "&=" {$$.sexp = sexp_symbol("&=");}
;
caret-assign: "^=" {$$.sexp = sexp_symbol("^=");}
;
bar-assign: "|=" {$$.sexp = sexp_symbol("|=");}
;

left-bracket: "[" {$$.sexp = sexp_symbol("[");}
;
right-bracket: "]" {$$.sexp = sexp_symbol("]");}
;
left-paren: "(" {$$.sexp = sexp_symbol("(");}
;
right-paren: ")" {$$.sexp = sexp_symbol(")");}
;
left-brace: "{" {$$.sexp = sexp_symbol("{");}
;
right-brace: "}" {$$.sexp = sexp_symbol("}");}
;
comma: "," {$$.sexp = sexp_symbol(",");}
;
colon: ":" {$$.sexp = sexp_symbol(":");}
;
semicolon: ";" {$$.sexp = sexp_symbol(";");}
;
ellipsis: "..." {$$.sexp = sexp_symbol("...");}
;

/* 6.3 Expressions */
primary-expression
: identifier
| floating-constant
| integer-constant
| character-constant
| string-literal
| left-paren expression right-paren {$$.sexp = PARSER_LIST3($1, $2, $3);}
;
postfix-expression
: primary-expression
| postfix-expression postfix-expression.suffix {$$.sexp = sexp_cons($1.sexp, $2.sexp);}
;
postfix-expression.suffix
: left-bracket expression right-bracket {$$.sexp = PARSER_LIST3($1, $2, $3);}
| left-paren argument-expression-list.opt right-paren {$$.sexp = PARSER_LIST3($1, $2, $3);}
| period identifier {$$.sexp = PARSER_LIST2($1, $2);}
| arrow identifier {$$.sexp = PARSER_LIST2($1, $2);}
| increment {$$.sexp = PARSER_LIST1($1);}
| decrement {$$.sexp = PARSER_LIST1($1);}
;
argument-expression-list.opt
: %empty {$$.sexp = sexp_nil();}
| argument-expression-list
;
argument-expression-list
: assignment-expression {$$.sexp = PARSER_LIST1($1);}
| argument-expression-list comma assignment-expression {$$.sexp = sexp_snoc($1.sexp, PARSER_LIST2($2, $3));}
;
unary-expression
: postfix-expression
| unary-expression.prefix unary-expression {$$.sexp = PARSER_LIST2($1, $2);}
| sizeof unary-expression {$$.sexp = PARSER_LIST2($1, $2);}
| sizeof left-paren type-name right-paren {$$.sexp = PARSER_LIST4($1, $2, $3, $4);}
| unary-operator cast-expression {$$.sexp = PARSER_LIST2($1, $2);}
;
unary-expression.prefix
: increment {$$.sexp = $1.sexp;}
| decrement {$$.sexp = $1.sexp;}
;
unary-operator
: ampersand {$$.sexp = $1.sexp;}
| asterisk {$$.sexp = $1.sexp;};
| plus {$$.sexp = $1.sexp;};
| minus {$$.sexp = $1.sexp;};
| tilde {$$.sexp = $1.sexp;};
| exclamation {$$.sexp = $1.sexp;};
;
cast-expression
: unary-expression
| left-paren type-name right-paren cast-expression {$$.sexp = PARSER_LIST4($1, $2, $3, $4);}
;
multiplicative-expression
: cast-expression
| multiplicative-expression multiplicative-operator cast-expression {$$.sexp = PARSER_LIST3($1, $2, $3);}
;
multiplicative-operator
: asterisk {$$.sexp = $1.sexp;}
| slash {$$.sexp = $1.sexp;}
| percent {$$.sexp = $1.sexp;}
;
additive-expression
: multiplicative-expression
| additive-expression additive-operator multiplicative-expression {$$.sexp = PARSER_LIST3($1, $2, $3);}
;
additive-operator
: plus {$$.sexp = $1.sexp;}
| minus {$$.sexp = $1.sexp;}
;
shift-expression
: additive-expression
| shift-expression shift-operator additive-expression {$$.sexp = PARSER_LIST3($1, $2, $3);}
;
shift-operator
: left-shift {$$.sexp = $1.sexp;}
| right-shift {$$.sexp = $1.sexp;}
;
relational-expression
: shift-expression
| relational-expression relational-operator shift-expression {$$.sexp = PARSER_LIST3($1, $2, $3);}
;
relational-operator
: less-than {$$.sexp = $1.sexp;}
| greater-than {$$.sexp = $1.sexp;}
| less-equal {$$.sexp = $1.sexp;}
| greater-equal {$$.sexp = $1.sexp;}
;
equality-expression
: relational-expression
| equality-expression equality-operator relational-expression {$$.sexp = PARSER_LIST3($1, $2, $3);}
;
equality-operator
: equal {$$.sexp = $1.sexp;}
| not-equal {$$.sexp = $1.sexp;}
;
and-expression
: equality-expression
| and-expression and-operator equality-expression {$$.sexp = PARSER_LIST3($1, $2, $3);}
;
and-operator
: ampersand {$$.sexp = $1.sexp;}
;
exclusive-or-expression
: and-expression
| exclusive-or-expression exclusive-or-operator and-expression {$$.sexp = PARSER_LIST3($1, $2, $3);}
;
exclusive-or-operator
: caret {$$.sexp = $1.sexp;}
;
inclusive-or-expression
: exclusive-or-expression
| inclusive-or-expression inclusive-or-operator exclusive-or-expression {$$.sexp = PARSER_LIST3($1, $2, $3);}
;
inclusive-or-operator
: bar {$$.sexp = $1.sexp;}
;
logical-and-expression
: inclusive-or-expression
| logical-and-expression logical-and-operator inclusive-or-expression {$$.sexp = PARSER_LIST3($1, $2, $3);}
;
logical-and-operator
: and {$$.sexp = $1.sexp;}
;
logical-or-expression
: logical-and-expression
| logical-or-expression logical-or-operator logical-and-expression {$$.sexp = PARSER_LIST3($1, $2, $3);}
;
logical-or-operator
: or {$$.sexp = $1.sexp;}
;
conditional-expression
: logical-or-expression
| logical-or-expression question expression colon conditional-expression {$$.sexp = PARSER_LIST5($1, $2, $3, $4, $5);}
;
assignment-expression
: conditional-expression
| unary-expression assignment-operator assignment-expression {$$.sexp = PARSER_LIST3($1, $2, $3);}
;
assignment-operator
: assign {$$.sexp = $1.sexp;}
| asterisk-assign {$$.sexp = $1.sexp;}
| slash-assign {$$.sexp = $1.sexp;}
| percent-assign {$$.sexp = $1.sexp;}
| plus-assign {$$.sexp = $1.sexp;}
| minus-assign {$$.sexp = $1.sexp;}
| left-shift-assign {$$.sexp = $1.sexp;}
| right-shift-assign {$$.sexp = $1.sexp;}
| ampersand-assign {$$.sexp = $1.sexp;}
| caret-assign {$$.sexp = $1.sexp;}
| bar-assign {$$.sexp = $1.sexp;}
;
expression.opt
: %empty {$$.sexp = sexp_nil();}
| expression
;
expression
: assignment-expression
| expression comma-operator assignment-expression {$$.sexp = PARSER_LIST3($1, $2, $3);}
;
comma-operator
: comma {$$.sexp = $1.sexp;}
;

/* 6.4 Constant expressions */
constant-expression.opt
: %empty {$$.sexp = sexp_nil();}
| constant-expression
;
constant-expression
: conditional-expression {$$.sexp = $1.sexp;}
;

/* 6.5 Declarations */
declaration
: declaration-specifiers semicolon {$$.sexp = PARSER_LIST2($1, $2);}
| declaration-specifiers init-declarator-list semicolon {$$.sexp = PARSER_LIST3($1, $2, $3);}
;
declaration-specifiers
: declaration-specifier {$$.sexp = PARSER_LIST1($1);}
| declaration-specifiers declaration-specifier {$$.sexp = sexp_snoc($1.sexp, $2.sexp);}
;
declaration-specifier
: storage-class-specifier
| type-specifier
| type-qualifier
;
init-declarator-list
: init-declarator {$$.sexp = PARSER_LIST1($1);}
| init-declarator-list comma init-declarator {$$.sexp = sexp_snoc($1.sexp, PARSER_LIST2($2, $3));}
;
init-declarator
: declarator {$$.sexp = $1.sexp;}
| declarator assign initializer {$$.sexp = PARSER_LIST3($1, $2, $3);}
;
storage-class-specifier
: storage-class-specifier.prefix {$$.sexp = $1.sexp;}
;
storage-class-specifier.prefix
: typedef {$$.sexp = $1.sexp;}
| extern {$$.sexp = $1.sexp;}
| static {$$.sexp = $1.sexp;}
| auto {$$.sexp = $1.sexp;}
| register {$$.sexp = $1.sexp;}
;
type-specifier
: type-specifier.prefix {$$.sexp = $1.sexp;}
;
type-specifier.prefix
: void {$$.sexp = $1.sexp;}
| char {$$.sexp = $1.sexp;}
| short {$$.sexp = $1.sexp;}
| int {$$.sexp = $1.sexp;}
| long {$$.sexp = $1.sexp;}
| float {$$.sexp = $1.sexp;}
| double {$$.sexp = $1.sexp;}
| signed {$$.sexp = $1.sexp;}
| unsigned {$$.sexp = $1.sexp;}
| struct-or-union-specifier
| enum-specifier
| typedef-name
;
struct-or-union-specifier
: struct-or-union identifier.opt left-brace struct-declaration-list right-brace {$$.sexp = PARSER_LIST5($1, $2, $3, $4, $5);}
| struct-or-union identifier {$$.sexp = PARSER_LIST2($1, $2);}
;
struct-or-union
: struct {$$.sexp = $1.sexp;}
| union {$$.sexp = $1.sexp;}
;
struct-declaration-list
: struct-declaration {$$.sexp = PARSER_LIST1($1);}
| struct-declaration-list struct-declaration {$$.sexp = sexp_snoc($1.sexp, $2.sexp);}
;
struct-declaration
: specifier-qualifier-list struct-declarator-list semicolon {$$.sexp = PARSER_LIST3($1, $2, $3);}
;
specifier-qualifier-list
: specifier-qualifier {$$.sexp = PARSER_LIST1($1);}
| specifier-qualifier-list specifier-qualifier {$$.sexp = sexp_snoc($1.sexp, $2.sexp);}
;
specifier-qualifier
: type-specifier
| type-qualifier
;
struct-declarator-list
: struct-declarator {$$.sexp = PARSER_LIST1($1);}
| struct-declarator-list comma struct-declarator {$$.sexp = sexp_snoc($1.sexp, PARSER_LIST2($2, $3));}
;
struct-declarator
: declarator {$$.sexp = $1.sexp;}
| declarator.opt colon constant-expression {$$.sexp = PARSER_LIST3($1, $2, $3);}
;
enum-specifier
: enum identifier.opt left-brace enumerator-list right-brace {$$.sexp = PARSER_LIST5($1, $2, $3, $4, $5);}
| enum identifier {$$.sexp = PARSER_LIST2($1, $2);}
;
enumerator-list
: enumerator {$$.sexp = PARSER_LIST1($1);}
| enumerator-list comma enumerator {$$.sexp = sexp_snoc($1.sexp, PARSER_LIST2($2, $3));}
;
enumerator
: enumeration-constant {$$.sexp = $1.sexp;}
| enumeration-constant assign constant-expression {$$.sexp = PARSER_LIST3($1, $2, $3);}
;
type-qualifier
: type-qualifier.prefix {$$.sexp = $1.sexp;}
;
type-qualifier.prefix
: const {$$.sexp = $1.sexp;}
| volatile {$$.sexp = $1.sexp;}
;
declarator.opt
: %empty {$$.sexp = sexp_nil();}
| declarator
;
declarator
: direct-declarator {$$.sexp = sexp_list2(sexp_nil(), $1.sexp);}
| pointer direct-declarator {$$.sexp = PARSER_LIST2($1, $2);}
;
direct-declarator
: direct-declarator.prefix
| direct-declarator direct-declarator.suffix {$$.sexp = PARSER_LIST2($1, $2);}
;
direct-declarator.prefix
: identifier
| "(" declarator ")" {$$.sexp = sexp_list3(sexp_symbol("("), $2.sexp, sexp_symbol(")"));}
;
direct-declarator.suffix
: left-bracket constant-expression.opt right-bracket {$$.sexp = PARSER_LIST3($1, $2, $3);}
| left-paren parameter-type-list right-paren {$$.sexp = PARSER_LIST3($1, $2, $3);}
| left-paren identifier-list.opt right-paren {$$.sexp = PARSER_LIST3($1, $2, $3);}
;
pointer
: pointer.prefix {$$.sexp = $1.sexp;}
| pointer.prefix pointer {$$.sexp = PARSER_LIST2($1, $2);}
;
pointer.prefix
: asterisk type-qualifier-list.opt {$$.sexp = PARSER_LIST2($1, $2);}
;
type-qualifier-list.opt
: %empty {$$.sexp = sexp_nil();}
| type-qualifier-list
;
type-qualifier-list
: type-qualifier {$$.sexp = PARSER_LIST1($1);}
| type-qualifier-list type-qualifier {$$.sexp = sexp_snoc($1.sexp, $2.sexp);}
;
parameter-type-list.opt
: %empty {$$.sexp = sexp_nil();}
| parameter-type-list
;
parameter-type-list
: parameter-list
| parameter-list comma ellipsis {$$.sexp = PARSER_LIST3($1, $2, $3);}
;
parameter-list
: parameter-declaration {$$.sexp = PARSER_LIST1($1);}
| parameter-list comma parameter-declaration {$$.sexp = sexp_snoc($1.sexp, PARSER_LIST2($2, $3));}
;
parameter-declaration
: declaration-specifiers {$$.sexp = $1.sexp;}
| declaration-specifiers parameter-declaration.suffix {$$.sexp = PARSER_LIST2($1, $2);}
;
parameter-declaration.suffix
: declarator
| abstract-declarator
;
identifier-list.opt
: %empty {$$.sexp = sexp_nil();}
| identifier-list
;
identifier-list
: identifier {$$.sexp = PARSER_LIST1($1);}
| identifier-list comma identifier {$$.sexp = sexp_snoc($1.sexp, PARSER_LIST2($2, $3));}
;
type-name
: specifier-qualifier-list {$$.sexp = $1.sexp;}
| specifier-qualifier-list abstract-declarator {$$.sexp = PARSER_LIST2($1, $2);}
;
abstract-declarator
: abstract-declarator.prefix {$$.sexp = $1.sexp;}
| pointer direct-abstract-declarator {$$.sexp = PARSER_LIST2($1, $2);}
;
abstract-declarator.prefix
: pointer
| direct-abstract-declarator
;
direct-abstract-declarator
: "(" abstract-declarator ")" {$$.sexp = sexp_list3(sexp_symbol("("), $2.sexp, sexp_symbol(")"));}
| direct-abstract-declarator.suffix
| direct-abstract-declarator direct-abstract-declarator.suffix {$$.sexp = PARSER_LIST2($1, $2);}
;
direct-abstract-declarator.suffix
: left-bracket constant-expression.opt right-bracket {$$.sexp = PARSER_LIST3($1, $2, $3);}
| left-paren parameter-type-list.opt right-paren {$$.sexp = PARSER_LIST3($1, $2, $3);}
;
typedef-name
: typedef-identifier {$$.sexp = $1.sexp;}
;
initializer
: assignment-expression
| initializer.suffix {$$.sexp = $1.sexp;}
;
initializer.suffix
: "{" initializer-list "}" {$$.sexp = sexp_list3(sexp_symbol("{"), $2.sexp, sexp_symbol("}"));}
| "{" initializer-list comma "}" {$$.sexp = sexp_list4(sexp_symbol("{"), $2.sexp, $3.sexp, sexp_symbol("}"));}
;
initializer-list
: initializer {$$.sexp = PARSER_LIST1($1);}
| initializer-list comma initializer {$$.sexp = sexp_snoc($1.sexp, PARSER_LIST2($2, $3));}
;

/* 6.6 Statements */
statement
: statement.prefix {$$.sexp = $1.sexp;}
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
: labeled-statement.prefix colon statement {$$.sexp = PARSER_LIST3($1, $2, $3);}
;
labeled-statement.prefix
: identifier
| case constant-expression {$$.sexp = PARSER_LIST2($1, $2);}
| default {$$.sexp = $1.sexp;}
;
compound-statement
: left-brace declaration-list.opt statement-list.opt right-brace {$$.sexp = PARSER_LIST4($1, $2, $3, $4);}
;
declaration-list.opt
: %empty {$$.sexp = sexp_nil();}
| declaration-list
;
declaration-list
: declaration {$$.sexp = PARSER_LIST1($1);}
| declaration-list declaration {$$.sexp = sexp_snoc($1.sexp, $2.sexp);}
;
statement-list.opt
: %empty {$$.sexp = sexp_nil();}
| statement-list
;
statement-list
: statement {$$.sexp = PARSER_LIST1($1);}
| statement-list statement {$$.sexp = sexp_snoc($1.sexp, $2.sexp);}
;
expression-statement
: expression.opt semicolon {$$.sexp = PARSER_LIST2($1, $2);}
;
selection-statement
: selection-statement.suffix {$$.sexp = $1.sexp;}
;
selection-statement.suffix
: if selection-statement.if {$$.sexp = sexp_cons($1.sexp, $2.sexp);}
| switch selection-statement.switch {$$.sexp = sexp_cons($1.sexp, $2.sexp);}
;
selection-statement.if
: "(" expression ")" statement %prec THEN {$$.sexp = sexp_list4(sexp_symbol("("), $2.sexp, sexp_symbol(")"), $4.sexp);}
| "(" expression ")" statement else statement {$$.sexp = sexp_list6(sexp_symbol("("), $2.sexp, sexp_symbol(")"), $4.sexp, $5.sexp, $6.sexp);}
;
selection-statement.switch
: left-paren expression right-paren statement {$$.sexp = PARSER_LIST4($1, $2, $3, $4);}
;
iteration-statement
: iteration-statement.suffix {$$.sexp = $1.sexp;}
;
iteration-statement.suffix
: while iteration-statement.while {$$.sexp = sexp_cons($1.sexp, $2.sexp);}
| do iteration-statement.do {$$.sexp = sexp_cons($1.sexp, $2.sexp);}
| for iteration-statement.for {$$.sexp = sexp_cons($1.sexp, $2.sexp);}
;
iteration-statement.while
: left-paren expression right-paren statement {$$.sexp = PARSER_LIST4($1, $2, $3, $4);}
;
iteration-statement.do
: statement while left-paren expression right-paren semicolon {$$.sexp = PARSER_LIST6($1, $2, $3, $4, $5, $6);}
;
iteration-statement.for
: left-paren expression.opt semicolon expression.opt semicolon expression.opt right-paren statement {$$.sexp = sexp_list4($1.sexp, PARSER_LIST5($2, $3, $4, $5, $6), $7.sexp, $8.sexp);}
;
jump-statement
: jump-statement.suffix semicolon {$$.sexp = sexp_snoc($1.sexp, $2.sexp);}
;
jump-statement.suffix
: goto identifier {$$.sexp = PARSER_LIST2($1, $2);}
| continue {$$.sexp = PARSER_LIST1($1);}
| break {$$.sexp = PARSER_LIST1($1);}
| return expression.opt {$$.sexp = PARSER_LIST2($1, $2);}
;

/* 6.7 External definitions */
top
: translation-unit {scanner_finish(scanner, $1);}
;
translation-unit
: external-declaration {$$.sexp = PARSER_LIST1($1);}
| translation-unit external-declaration {$$.sexp = sexp_snoc($1.sexp, $2.sexp);}
;
external-declaration
: function-definition
| declaration {$$.sexp = $1.sexp;}
;
function-definition
: function-definition.old {$$.sexp = $1.sexp;}
| declaration-specifiers declarator compound-statement {$$.sexp = PARSER_LIST3($1, $2, $3);}
;
function-definition.old
: declarator compound-statement {$$.sexp = PARSER_LIST2($1, $2);}
| declarator declaration-list compound-statement {$$.sexp = PARSER_LIST3($1, $2, $3);}
| declaration-specifiers declarator declaration-list compound-statement {$$.sexp = PARSER_LIST4($1, $2, $3, $4);}
;
%%
