#ifndef INCLUDE_GUARD_EB689973_FC12_413F_9E9E_C612BD832E1C
#define INCLUDE_GUARD_EB689973_FC12_413F_9E9E_C612BD832E1C

#include "scanner_type.h"
#include "typedef.h"

yyscan_t scan_new(Result *);
void scan_delete(yyscan_t);
int scan_parse(yyscan_t);
void scan_finish(yyscan_t, Sexp *);
Sexp *scan_token(yyscan_t);
Table *scan_table(yyscan_t);
void scan_yyerror(yyscan_t, const char *);

#endif /* INCLUDE_GUARD_EB689973_FC12_413F_9E9E_C612BD832E1C */
