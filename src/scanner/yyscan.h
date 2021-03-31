#ifndef INCLUDE_GUARD_AD2E6BDC_1852_434E_87C9_94003CD02072
#define INCLUDE_GUARD_AD2E6BDC_1852_434E_87C9_94003CD02072

#include "scanner/yyscan_t.h"
#include "sexp/opaque.h"

#define YYSCAN_FINISH(ast) yyscan_finish(ast, yyscanner)
#define YYSCAN_DECLARATION(ast) yyscan_declaration(ast, yyscanner)

void yyerror(yyscan_t, const char *);
Sexp *yyscan_token(yyscan_t);
void yyscan_finish(Sexp *, yyscan_t);
void yyscan_declaration(Sexp *, yyscan_t);

#endif /* INCLUDE_GUARD_AD2E6BDC_1852_434E_87C9_94003CD02072 */
