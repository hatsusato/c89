#ifndef INCLUDE_GUARD_EB689973_FC12_413F_9E9E_C612BD832E1C
#define INCLUDE_GUARD_EB689973_FC12_413F_9E9E_C612BD832E1C

#include "typedef.h"

yyscan_t scanner_new(Result *);
void scanner_delete(yyscan_t);
int scanner_parse(yyscan_t);
void scanner_finish(yyscan_t, Sexp *);
Sexp *scanner_token(yyscan_t);
Table *scanner_table(yyscan_t);
void scanner_yyerror(yyscan_t, const char *);

#endif /* INCLUDE_GUARD_EB689973_FC12_413F_9E9E_C612BD832E1C */
