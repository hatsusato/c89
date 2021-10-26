#ifndef INCLUDE_GUARD_AD2E6BDC_1852_434E_87C9_94003CD02072
#define INCLUDE_GUARD_AD2E6BDC_1852_434E_87C9_94003CD02072

#include "ast/tag.h"
#include "utility/types.h"
#include "yyscan_t.h"

void yyerror(yyscan_t, const char *);
int yyscan_parse(Scanner *);
Sexp *yyscan_nil(void);
Sexp *yyscan_push(Sexp *, Sexp *);
Sexp *yyscan_symbol(SyntaxTag);
Sexp *yyscan_tag(SyntaxTag);
Sexp *yyscan_append(Sexp *, Sexp *);
Sexp *yyscan_token(yyscan_t);
Bool yyscan_query(const char *, yyscan_t);
void yyscan_finish(Sexp *, yyscan_t);
void yyscan_declaration(Sexp *, yyscan_t);

#endif /* INCLUDE_GUARD_AD2E6BDC_1852_434E_87C9_94003CD02072 */
