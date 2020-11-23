#ifndef INCLUDE_GUARD_29982745_2BB0_454B_9528_9FABEC206FF9
#define INCLUDE_GUARD_29982745_2BB0_454B_9528_9FABEC206FF9

#include "ast.h"
#include "scanner/scanner_type.h"

Scanner *scanner_new(void);
void scanner_delete(Scanner *);
int scanner_parse(Scanner *);
Ast *scanner_ast(Scanner *);

#endif /* INCLUDE_GUARD_29982745_2BB0_454B_9528_9FABEC206FF9 */
