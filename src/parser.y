%code top {
}
%code requires {
}
%code provides {
  int yylex(void);
  void yyerror(const char *);
  extern int g_result;
}

%define api.value.type {int}
%token NUM
%token PLUS "+"
%token MINUS "-"
%token ASTER "*"
%token SLASH "/"
%token LPAR "("
%token RPAR ")"
%token NL "\n"
%start top
%%
top
: expr { g_result = $expr; }
;
expr
: term
| term[lhs] PLUS expr[rhs] { $$ = $lhs + $rhs; }
| term[lhs] MINUS expr[rhs] { $$ = $lhs - $rhs; }
;
term
: factor
| factor[lhs] ASTER term[rhs] { $$ = $lhs * $rhs; }
| factor[lhs] SLASH term[rhs] { $$ = $lhs / $rhs; }
;
factor
: NUM
| LPAR expr RPAR { $$ = $expr; }
;
%%
