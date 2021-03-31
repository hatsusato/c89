#ifndef INCLUDE_GUARD_AD2E6BDC_1852_434E_87C9_94003CD02072
#define INCLUDE_GUARD_AD2E6BDC_1852_434E_87C9_94003CD02072

#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void *yyscan_t;
#endif

#include "sexp/opaque.h"

void yyerror(yyscan_t, const char *);
void yyscan_finish(Sexp *, yyscan_t);
void yyscan_declaration(Sexp *, yyscan_t);

#endif /* INCLUDE_GUARD_AD2E6BDC_1852_434E_87C9_94003CD02072 */
