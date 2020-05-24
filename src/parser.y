%code top {
}
%code requires {
}
%code provides {
  int yylex(void);
  void yyerror(const char *);
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
