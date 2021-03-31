#ifndef INCLUDE_GUARD_AD2E6BDC_1852_434E_87C9_94003CD02072
#define INCLUDE_GUARD_AD2E6BDC_1852_434E_87C9_94003CD02072

#include "utility/types.h"
#include "yyscan_t.h"

#define YYSCAN_NIL() sexp_nil()
#define YYSCAN_CONS(x, xs) sexp_pair(x, xs)
#define YYSCAN_SNOC(xs, x) sexp_snoc(xs, x)
#define YYSCAN_LIST(x) YYSCAN_CONS(x, YYSCAN_NIL())
#define YYSCAN_SYMBOL(tag) sexp_number(tag)
#define YYSCAN_TAG(tag) YYSCAN_LIST(YYSCAN_SYMBOL(tag))
#define YYSCAN_APPEND(xs, ys) sexp_append(xs, ys);
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
