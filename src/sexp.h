#ifndef INCLUDE_GUARD_3397EB56_FB26_40B7_AD9E_F7B3DA519335
#define INCLUDE_GUARD_3397EB56_FB26_40B7_AD9E_F7B3DA519335

#include "utility.h"

struct struct_Sexp;
typedef struct struct_Sexp const Sexp;

Sexp *sexp_nil(void);
Sexp *sexp_cons(Sexp *, Sexp *);
Sexp *sexp_snoc(Sexp *, Sexp *);
Sexp *sexp_append(Sexp *, Sexp *);
Sexp *sexp_symbol(const char *);
Sexp *sexp_string(const char *, int);
void sexp_delete(Sexp *);
Bool sexp_is_nil(Sexp *);
Bool sexp_is_pair(Sexp *);
Bool sexp_is_symbol(Sexp *);
Bool sexp_is_string(Sexp *);
Bool sexp_is_list(Sexp *);
Bool sexp_eq(Sexp *, const char *);
Sexp *sexp_car(Sexp *);
Sexp *sexp_cdr(Sexp *);
Sexp *sexp_at(Sexp *, int);
const char *sexp_get(Sexp *);
int sexp_length(Sexp *);

#endif /* INCLUDE_GUARD_3397EB56_FB26_40B7_AD9E_F7B3DA519335 */
