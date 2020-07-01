#ifndef INCLUDE_GUARD_EB689973_FC12_413F_9E9E_C612BD832E1C
#define INCLUDE_GUARD_EB689973_FC12_413F_9E9E_C612BD832E1C

#include "result.h"
#include "sexp.h"
#include "utility.h"

#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void *yyscan_t;
#endif

void yyerror(yyscan_t, const char *);
yyscan_t scanner_new(Result *);
void scanner_delete(yyscan_t);
int scanner_parse(yyscan_t);
void scanner_finish(yyscan_t, Sexp *);
const char *scanner_get_text(yyscan_t);
void scanner_insert_symbol(yyscan_t, const char *);
Bool scanner_contains_symbol(yyscan_t, const char *);
Sexp *scanner_token(yyscan_t);

#endif /* INCLUDE_GUARD_EB689973_FC12_413F_9E9E_C612BD832E1C */
