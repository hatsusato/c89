%code requires {
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void *yyscan_t;
#endif
}

%define api.pure full
%define api.value.type {void *}
%param {yyscan_t yyscanner}

%code provides {
#include "lexer.h"
void yyerror(yyscan_t, const char *);
}

%start top

%%

top: %empty {};

%%

void yyerror(yyscan_t yyscanner, const char *msg) {
  (void)yyscanner;
  (void)msg;
}
