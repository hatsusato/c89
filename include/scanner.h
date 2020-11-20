#ifndef INCLUDE_GUARD_29982745_2BB0_454B_9528_9FABEC206FF9
#define INCLUDE_GUARD_29982745_2BB0_454B_9528_9FABEC206FF9

#include "scanner_type.h"
#include "sexp_type.h"
#include "table_type.h"

Scanner *scanner_new(void);
void scanner_delete(Scanner *);
int scanner_parse(Scanner *);
void scanner_set_ast(Scanner *, Sexp *);
Sexp *scanner_get_ast(Scanner *);
void scanner_finish(Scanner *, Sexp *);
Sexp *scanner_token(Scanner *);
Table *scanner_table(Scanner *);

#endif /* INCLUDE_GUARD_29982745_2BB0_454B_9528_9FABEC206FF9 */
