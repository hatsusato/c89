%code top {
}
%code requires {
}
%code provides {
  int yylex(void);
  void yyerror(const char *);
  const char* show_token(int);
}

%define api.value.type {int}

%token AUTO "auto"
%token BREAK "break"
%token CASE "case"
%token CHAR "char"
%token CONST "const"
%token CONTINUE "continue"
%token DEFAULT "default"
%token DO "do"
%token DOUBLE "double"
%token ELSE "else"
%token ENUM "enum"
%token EXTERN "extern"
%token FLOAT "float"
%token FOR "for"
%token GOTO "goto"
%token IF "if"
%token INT "int"
%token LONG "long"
%token REGISTER "register"
%token RETURN "return"
%token SIGNED "signed"
%token SIZEOF "sizeof"
%token SHORT "short"
%token STATIC "static"
%token STRUCT "struct"
%token SWITCH "switch"
%token TYPEDEF "typedef"
%token UNION "union"
%token UNSIGNED "unsigned"
%token VOID "void"
%token VOLATILE "volatile"
%token WHILE "while"

%token LPAR "("
%token RPAR ")"
%token LBRK "["
%token RBRK "]"
%token LBRC "{"
%token RBRC "}"
%token DOT "."
%token ARROW "->"
%token INC "++"
%token DEC "--"
%token PLUS "+"
%token MIN "-"
%token EXCL "!"
%token TILDA "~"
%token STAR "*"
%token AMP "&"
%token SLA "/"
%token PERC "%"
%token LSHF "<<"
%token RSHF ">>"
%token GT ">"
%token LT "<"
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
%token PLUS_ASG "+="
%token MIN_ASG "-="
%token STAR_ASG "*="
%token SLA_ASG "/="
%token PERC_ASG "%="
%token LSHF_ASG "<<="
%token RSHF_ASG ">>="
%token AMP_ASG "&="
%token HAT_ASG "^="
%token BAR_ASG "|="
%token COMMA ","

%start top
%%
top
: COMMA
;
%%

const char* show_token(int token) {
#define CASE_TOKEN(t)                           \
  case t:                                       \
    return #t
  switch (token) {
    CASE_TOKEN(AUTO);
    CASE_TOKEN(BREAK);
    CASE_TOKEN(CASE);
    CASE_TOKEN(CHAR);
    CASE_TOKEN(CONST);
    CASE_TOKEN(CONTINUE);
    CASE_TOKEN(DEFAULT);
    CASE_TOKEN(DO);
    CASE_TOKEN(DOUBLE);
    CASE_TOKEN(ELSE);
    CASE_TOKEN(ENUM);
    CASE_TOKEN(EXTERN);
    CASE_TOKEN(FLOAT);
    CASE_TOKEN(FOR);
    CASE_TOKEN(GOTO);
    CASE_TOKEN(IF);
    CASE_TOKEN(INT);
    CASE_TOKEN(LONG);
    CASE_TOKEN(REGISTER);
    CASE_TOKEN(RETURN);
    CASE_TOKEN(SIGNED);
    CASE_TOKEN(SIZEOF);
    CASE_TOKEN(SHORT);
    CASE_TOKEN(STATIC);
    CASE_TOKEN(STRUCT);
    CASE_TOKEN(SWITCH);
    CASE_TOKEN(TYPEDEF);
    CASE_TOKEN(UNION);
    CASE_TOKEN(UNSIGNED);
    CASE_TOKEN(VOID);
    CASE_TOKEN(VOLATILE);
    CASE_TOKEN(WHILE);
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
    default:
      return "UNKNOWN";
  }
#undef CASE_TOKEN
}
