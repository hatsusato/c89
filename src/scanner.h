#ifndef INCLUDE_GUARD_EB689973_FC12_413F_9E9E_C612BD832E1C
#define INCLUDE_GUARD_EB689973_FC12_413F_9E9E_C612BD832E1C

#include "typedef.h"
#include "utility.h"

void yyerror(yyscan_t, const char *);
yyscan_t scanner_new(Result *);
void scanner_delete(yyscan_t);
int scanner_parse(yyscan_t);
void scanner_finish(yyscan_t, Sexp *);
const char *scanner_get_text(yyscan_t);
Sexp *scanner_token(yyscan_t);
void scanner_register_typedef(yyscan_t, Sexp *);
Bool scanner_query_typedef(yyscan_t, const char *);
void scanner_push_scope(yyscan_t);
void scanner_pop_scope(yyscan_t);

#endif /* INCLUDE_GUARD_EB689973_FC12_413F_9E9E_C612BD832E1C */
