#ifndef INCLUDE_GUARD_3397EB56_FB26_40B7_AD9E_F7B3DA519335
#define INCLUDE_GUARD_3397EB56_FB26_40B7_AD9E_F7B3DA519335

#include "sexp_type.h"
#include "types.h"

Sexp *sexp_nil(void);
Sexp *sexp_pair(Sexp *, Sexp *);
Sexp *sexp_snoc(Sexp *, Sexp *);
Sexp *sexp_string(const char *, int);
Sexp *sexp_number(int);
Sexp *sexp_clone(Sexp *);
void sexp_delete(Sexp *);
Bool sexp_is_nil(Sexp *);
Bool sexp_is_pair(Sexp *);
Bool sexp_is_string(Sexp *);
Bool sexp_is_number(Sexp *);
Bool sexp_is_list(Sexp *);
Sexp *sexp_car(Sexp *);
Sexp *sexp_cdr(Sexp *);
Sexp *sexp_at(Sexp *, int);
const char *sexp_get_string(Sexp *);
int sexp_get_number(Sexp *);
int sexp_length(Sexp *);

#endif /* INCLUDE_GUARD_3397EB56_FB26_40B7_AD9E_F7B3DA519335 */
