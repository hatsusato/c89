#ifndef INCLUDE_GUARD_AD2E6BDC_1852_434E_87C9_94003CD02072
#define INCLUDE_GUARD_AD2E6BDC_1852_434E_87C9_94003CD02072

#include "utility/types.h"
#include "yyscan_t.h"

#define YYSCAN_TOKEN() yyscan_token(yyscanner)
#define YYSCAN_FINISH(ast) yyscan_finish(ast, yyscanner)
#define YYSCAN_DECLARATION(ast) yyscan_declaration(ast, yyscanner)

void yyerror(yyscan_t, const char *);
int yyscan_parse(Scanner *);
Sexp *yyscan_token(yyscan_t);
Bool yyscan_query(const char *, yyscan_t);
void yyscan_finish(Sexp *, yyscan_t);
void yyscan_declaration(Sexp *, yyscan_t);

#endif /* INCLUDE_GUARD_AD2E6BDC_1852_434E_87C9_94003CD02072 */
