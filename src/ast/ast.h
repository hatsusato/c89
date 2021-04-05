#ifndef INCLUDE_GUARD_A84E9F8A_C152_4807_9181_80EE16B4DFA5
#define INCLUDE_GUARD_A84E9F8A_C152_4807_9181_80EE16B4DFA5

#include "utility/types.h"

Ast *ast_new(void);
void ast_delete(Ast *);
Sexp *ast_get(Ast *);
void ast_set(Ast *, Sexp *);
const char *ast_symbol(Ast *, const char *, Size);
void ast_convert(Ast *);
void ast_print(Ast *, Printer *);

#endif /* INCLUDE_GUARD_A84E9F8A_C152_4807_9181_80EE16B4DFA5 */
