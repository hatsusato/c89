#ifndef INCLUDE_GUARD_9C8CB4C0_BC4E_4938_931F_A41B8FE242C3
#define INCLUDE_GUARD_9C8CB4C0_BC4E_4938_931F_A41B8FE242C3

#include "typedef.h"

Result *result_new(void);
void result_delete(Result *);
int result_parse(Result *);
Table *result_get_table(Result *);
Sexp *result_get_sexp(Result *);
void result_set_sexp(Result *, Sexp *);

#endif /* INCLUDE_GUARD_9C8CB4C0_BC4E_4938_931F_A41B8FE242C3 */
