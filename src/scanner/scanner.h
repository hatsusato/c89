#ifndef INCLUDE_GUARD_29982745_2BB0_454B_9528_9FABEC206FF9
#define INCLUDE_GUARD_29982745_2BB0_454B_9528_9FABEC206FF9

#include "scanner/yyscan_t.h"
#include "utility/types.h"

Ast *scanner_ast(yyscan_t);
Set *scanner_typedefs(yyscan_t);

int scanner_parse(Ast *);
Ast *scanner_get(Scanner *);
const char *scanner_symbol(Scanner *, const char *, Size);
Bool scanner_find(Scanner *, const char *);
void scanner_insert(Scanner *, const char *);
void scanner_finish(Scanner *, Sexp *);

#endif /* INCLUDE_GUARD_29982745_2BB0_454B_9528_9FABEC206FF9 */
