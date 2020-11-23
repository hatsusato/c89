#ifndef INCLUDE_GUARD_29982745_2BB0_454B_9528_9FABEC206FF9
#define INCLUDE_GUARD_29982745_2BB0_454B_9528_9FABEC206FF9

#include "sexp_type.h"
#include "types.h"

struct struct_Scanner;
typedef struct struct_Scanner Scanner;

Scanner *scanner_new(void);
void scanner_delete(Scanner *);
int scanner_parse(Scanner *);
Sexp *scanner_ast(Scanner *);

#endif /* INCLUDE_GUARD_29982745_2BB0_454B_9528_9FABEC206FF9 */
