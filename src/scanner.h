#ifndef INCLUDE_GUARD_EB689973_FC12_413F_9E9E_C612BD832E1C
#define INCLUDE_GUARD_EB689973_FC12_413F_9E9E_C612BD832E1C

#include "ast.h"
#include "result.h"

#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void *yyscan_t;
#endif

void yyerror(const char *, yyscan_t);
yyscan_t scanner_new(Result *);
void scanner_delete(yyscan_t);
List *scanner_get_ast(yyscan_t);
void scanner_set_ast(yyscan_t, AstList);
const char *scanner_get_text(yyscan_t);

#endif /* INCLUDE_GUARD_EB689973_FC12_413F_9E9E_C612BD832E1C */
