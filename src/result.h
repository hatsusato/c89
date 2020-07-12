#ifndef INCLUDE_GUARD_9C8CB4C0_BC4E_4938_931F_A41B8FE242C3
#define INCLUDE_GUARD_9C8CB4C0_BC4E_4938_931F_A41B8FE242C3

#include "typedef.h"

Result *result_new(void);
void result_delete(Result *);
int result_parse(Result *);
Set *result_get_symbols(Result *);
Table *result_get_table(Result *);
Sexp *result_set_sexp(Result *, Sexp *);
void result_push_scope(Result *);
void result_pop_scope(Result *);
void result_register(Result *, Sexp *);
Bool result_query(Result *, const char *);

#endif /* INCLUDE_GUARD_9C8CB4C0_BC4E_4938_931F_A41B8FE242C3 */
