#ifndef INCLUDE_GUARD_9C8CB4C0_BC4E_4938_931F_A41B8FE242C3
#define INCLUDE_GUARD_9C8CB4C0_BC4E_4938_931F_A41B8FE242C3

#include "set.h"
#include "sexp.h"

struct struct_Result;
typedef struct struct_Result Result;

Result *result_new(void);
void result_delete(Result *);
int result_parse(Result *);
Set *result_get_symbols(Result *);
Sexp *result_set_sexp(Result *, Sexp *);

#endif /* INCLUDE_GUARD_9C8CB4C0_BC4E_4938_931F_A41B8FE242C3 */
