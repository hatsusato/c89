#ifndef INCLUDE_GUARD_29982745_2BB0_454B_9528_9FABEC206FF9
#define INCLUDE_GUARD_29982745_2BB0_454B_9528_9FABEC206FF9

#include "scanner_type.h"
#include "sexp_type.h"
#include "types.h"

Scanner *scanner_new(void);
void scanner_delete(Scanner *);
int scanner_parse(Scanner *);
Sexp *scanner_ast(Scanner *);
void scanner_finish(Scanner *, Sexp *);
Sexp *scanner_token(Scanner *);
void scanner_register(Scanner *, const char *);
Bool scanner_query(Scanner *, const char *);

#endif /* INCLUDE_GUARD_29982745_2BB0_454B_9528_9FABEC206FF9 */
