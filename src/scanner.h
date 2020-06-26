#ifndef INCLUDE_GUARD_EB689973_FC12_413F_9E9E_C612BD832E1C
#define INCLUDE_GUARD_EB689973_FC12_413F_9E9E_C612BD832E1C

#include "list.h"
#include "parser.tab.h"

void yyerror(const char *, yyscan_t);
yyscan_t scanner_new(void);
void scanner_delete(yyscan_t);
List *scanner_get_ast(yyscan_t);
void scanner_set_ast(yyscan_t, YYSTYPE);

#endif /* INCLUDE_GUARD_EB689973_FC12_413F_9E9E_C612BD832E1C */