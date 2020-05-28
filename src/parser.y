%code top {
}
%code requires {
#include <stdio.h>
#include "vector.h"
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
  typedef void* yyscan_t;
#endif
}
%code provides {
#include "lexer.h"
  void yyerror(const char *, yyscan_t);
  const char* show_token(int);
  void print_token(const char *, Vector* v);
}

%define api.pure full
%define api.value.type {Vector *}
%param {yyscan_t scanner}

%token IDENT
%token FLOATING
%token INTEGER
%token CHARACTER
%token LITERAL

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

%token LBRK "["
%token RBRK "]"
%token LPAR "("
%token RPAR ")"
%token LBRC "{"
%token RBRC "}"
%token DOT "."
%token ARROW "->"
%token INC "++"
%token DEC "--"
%token AMP "&"
%token STAR "*"
%token PLUS "+"
%token MIN "-"
%token TILDA "~"
%token EXCL "!"
%token SLA "/"
%token PERC "%"
%token LSHF "<<"
%token RSHF ">>"
%token LT "<"
%token GT ">"
%token LE "<="
%token GE ">="
%token EQ "=="
%token NE "!="
%token HAT "^"
%token BAR "|"
%token AND "&&"
%token OR "||"
%token QUEST "?"
%token COLON ":"
%token ASG "="
%token STAR_ASG "*="
%token SLA_ASG "/="
%token PERC_ASG "%="
%token PLUS_ASG "+="
%token MIN_ASG "-="
%token LSHF_ASG "<<="
%token RSHF_ASG ">>="
%token AMP_ASG "&="
%token HAT_ASG "^="
%token BAR_ASG "|="
%token COMMA ","
%token SEMIC ";"
%token ELLIP "..."
%token UNKNOWN

%start top
%%
top: %empty
| top token
;
token
: keyword { print_token("keyword", $$); }
| identifier { print_token("identifier", $$); }
| constant
| string-literal { print_token("literal", $$); }
| operator { print_token("punctuator", $$); }
| punctuator { print_token("punctuator", $$); }
;
keyword
: "auto"
| "break"
| "case"
| "char"
| "const"
| "continue"
| "default"
| "do"
| "double"
| "else"
| "enum"
| "extern"
| "float"
| "for"
| "goto"
| "if"
| "int"
| "long"
| "register"
| "return"
| "signed"
| "sizeof"
| "short"
| "static"
| "struct"
| "switch"
| "typedef"
| "union"
| "unsigned"
| "void"
| "volatile"
| "while"
;
identifier
: IDENT
;
constant
: floating-constant { print_token("floating", $$); }
| integer-constant { print_token("integer", $$); }
/* | enumeration-constant */
| character-constant { print_token("character", $$); }
;
floating-constant
: FLOATING
;
integer-constant
: INTEGER
;
/* enumeration-constant: */
/*   IDENT */
/* ; */
character-constant
: CHARACTER
;
string-literal
: LITERAL
;
operator
: "["
| "]"
| "("
| ")"
| "."
| "->"
| "++"
| "--"
| "&"
| "*"
| "+"
| "-"
| "~"
| "!"
| "/"
| "%"
| "<<"
| ">>"
| "<"
| ">"
| "<="
| ">="
| "=="
| "!="
| "^"
| "|"
| "&&"
| "||"
| "?"
| ":"
| "="
| "*="
| "/="
| "%="
| "+="
| "-="
| "<<="
| ">>="
| "&="
| "^="
| "|="
| ","
;
punctuator
/* : "[" */
/* | "]" */
/* | "(" */
/* | ")" */
: "{"
| "}"
/* | "*" */
/* | "," */
/* | ":" */
/* | "=" */
| ";"
| "..."
;
%%

const char* show_token(int token) {
#define CASE_TOKEN(t)                           \
  case t:                                       \
    return #t
  switch (token) {
    CASE_TOKEN(IDENT);
    CASE_TOKEN(FLOATING);
    CASE_TOKEN(INTEGER);
    CASE_TOKEN(CHARACTER);
    CASE_TOKEN(LITERAL);
    CASE_TOKEN(KEYWORD_AUTO);
    CASE_TOKEN(KEYWORD_BREAK);
    CASE_TOKEN(KEYWORD_CASE);
    CASE_TOKEN(KEYWORD_CHAR);
    CASE_TOKEN(KEYWORD_CONST);
    CASE_TOKEN(KEYWORD_CONTINUE);
    CASE_TOKEN(KEYWORD_DEFAULT);
    CASE_TOKEN(KEYWORD_DO);
    CASE_TOKEN(KEYWORD_DOUBLE);
    CASE_TOKEN(KEYWORD_ELSE);
    CASE_TOKEN(KEYWORD_ENUM);
    CASE_TOKEN(KEYWORD_EXTERN);
    CASE_TOKEN(KEYWORD_FLOAT);
    CASE_TOKEN(KEYWORD_FOR);
    CASE_TOKEN(KEYWORD_GOTO);
    CASE_TOKEN(KEYWORD_IF);
    CASE_TOKEN(KEYWORD_INT);
    CASE_TOKEN(KEYWORD_LONG);
    CASE_TOKEN(KEYWORD_REGISTER);
    CASE_TOKEN(KEYWORD_RETURN);
    CASE_TOKEN(KEYWORD_SIGNED);
    CASE_TOKEN(KEYWORD_SIZEOF);
    CASE_TOKEN(KEYWORD_SHORT);
    CASE_TOKEN(KEYWORD_STATIC);
    CASE_TOKEN(KEYWORD_STRUCT);
    CASE_TOKEN(KEYWORD_SWITCH);
    CASE_TOKEN(KEYWORD_TYPEDEF);
    CASE_TOKEN(KEYWORD_UNION);
    CASE_TOKEN(KEYWORD_UNSIGNED);
    CASE_TOKEN(KEYWORD_VOID);
    CASE_TOKEN(KEYWORD_VOLATILE);
    CASE_TOKEN(KEYWORD_WHILE);
    CASE_TOKEN(LPAR);
    CASE_TOKEN(RPAR);
    CASE_TOKEN(LBRK);
    CASE_TOKEN(RBRK);
    CASE_TOKEN(LBRC);
    CASE_TOKEN(RBRC);
    CASE_TOKEN(DOT);
    CASE_TOKEN(ARROW);
    CASE_TOKEN(INC);
    CASE_TOKEN(DEC);
    CASE_TOKEN(PLUS);
    CASE_TOKEN(MIN);
    CASE_TOKEN(EXCL);
    CASE_TOKEN(TILDA);
    CASE_TOKEN(STAR);
    CASE_TOKEN(AMP);
    CASE_TOKEN(SLA);
    CASE_TOKEN(PERC);
    CASE_TOKEN(LSHF);
    CASE_TOKEN(RSHF);
    CASE_TOKEN(GT);
    CASE_TOKEN(LT);
    CASE_TOKEN(LE);
    CASE_TOKEN(GE);
    CASE_TOKEN(EQ);
    CASE_TOKEN(NE);
    CASE_TOKEN(HAT);
    CASE_TOKEN(BAR);
    CASE_TOKEN(AND);
    CASE_TOKEN(OR);
    CASE_TOKEN(QUEST);
    CASE_TOKEN(COLON);
    CASE_TOKEN(ASG);
    CASE_TOKEN(PLUS_ASG);
    CASE_TOKEN(MIN_ASG);
    CASE_TOKEN(STAR_ASG);
    CASE_TOKEN(SLA_ASG);
    CASE_TOKEN(PERC_ASG);
    CASE_TOKEN(LSHF_ASG);
    CASE_TOKEN(RSHF_ASG);
    CASE_TOKEN(AMP_ASG);
    CASE_TOKEN(HAT_ASG);
    CASE_TOKEN(BAR_ASG);
    CASE_TOKEN(COMMA);
    CASE_TOKEN(SEMIC);
    CASE_TOKEN(ELLIP);
  default:
    return "UNKNOWN";
  }
#undef CASE_TOKEN
}

void yyerror(const char* msg, yyscan_t scanner) {
  (void)scanner;
  fprintf(stderr, "%s\n", msg);
}

void print_token(const char* header, Vector* v) {
  if (v) {
    printf("%s: %s\n", header, (char *)vector_at(v, 0));
  }
}
