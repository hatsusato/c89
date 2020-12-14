#ifndef INCLUDE_GUARD_3397EB56_FB26_40B7_AD9E_F7B3DA519335
#define INCLUDE_GUARD_3397EB56_FB26_40B7_AD9E_F7B3DA519335

#include "sexp_type.h"
#include "types.h"

typedef void (*SexpMap)(Sexp *, void *);

void sexp_delete(Sexp *);
Sexp *sexp_clone(Sexp *);
Sexp *sexp_nil(void);
Sexp *sexp_pair(Sexp *, Sexp *);
Sexp *sexp_symbol(const char *);
Sexp *sexp_number(int);
Bool sexp_is_nil(Sexp *);
Bool sexp_is_pair(Sexp *);
Bool sexp_is_symbol(Sexp *);
Bool sexp_is_number(Sexp *);
Bool sexp_is_list(Sexp *);
Sexp *sexp_car(Sexp *);
Sexp *sexp_cdr(Sexp *);
Sexp *sexp_snoc(Sexp *, Sexp *);
Sexp *sexp_at(Sexp *, Index);
const char *sexp_get_symbol(Sexp *);
int sexp_get_number(Sexp *);
int sexp_length(Sexp *);
void sexp_list_map(Sexp *, void *, SexpMap);
int sexp_get_tag(Sexp *);

#endif /* INCLUDE_GUARD_3397EB56_FB26_40B7_AD9E_F7B3DA519335 */