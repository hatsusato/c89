#ifndef INCLUDE_GUARD_29982745_2BB0_454B_9528_9FABEC206FF9
#define INCLUDE_GUARD_29982745_2BB0_454B_9528_9FABEC206FF9

#include "utility/types.h"

int scanner_parse(Ast *);
const char *scanner_symbol(Scanner *, const char *, Size);
Bool scanner_exists(Scanner *, const char *);
void scanner_register(Scanner *, const char *);
void scanner_finish(Scanner *, Sexp *);

#endif /* INCLUDE_GUARD_29982745_2BB0_454B_9528_9FABEC206FF9 */
