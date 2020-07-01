#ifndef INCLUDE_GUARD_3397EB56_FB26_40B7_AD9E_F7B3DA519335
#define INCLUDE_GUARD_3397EB56_FB26_40B7_AD9E_F7B3DA519335

#include "utility.h"

struct struct_Sexp;
typedef struct struct_Sexp const Sexp;

Sexp* sexp_nil(void);
Sexp* sexp_cons(Sexp*, Sexp*);
Sexp* sexp_symbol(const char*);
Sexp* sexp_string(const char*, int);
void sexp_delete(Sexp*);
Bool sexp_is_nil(Sexp*);
Bool sexp_is_pair(Sexp*);
Bool sexp_is_symbol(Sexp*);
Bool sexp_is_string(Sexp*);
Sexp* sexp_car(Sexp*);
Sexp* sexp_cdr(Sexp*);
Sexp* sexp_at(Sexp*, int);
Bool sexp_eq(Sexp*, const char*);
const char* sexp_get_string(Sexp*);
Sexp* sexp_snoc(Sexp*, Sexp*);
Sexp* sexp_list1(Sexp*);
Sexp* sexp_list2(Sexp*, Sexp*);
Sexp* sexp_list3(Sexp*, Sexp*, Sexp*);
Sexp* sexp_list4(Sexp*, Sexp*, Sexp*, Sexp*);
Sexp* sexp_list5(Sexp*, Sexp*, Sexp*, Sexp*, Sexp*);
Sexp* sexp_list6(Sexp*, Sexp*, Sexp*, Sexp*, Sexp*, Sexp*);
Sexp* sexp_list7(Sexp*, Sexp*, Sexp*, Sexp*, Sexp*, Sexp*, Sexp*);
Sexp* sexp_list8(Sexp*, Sexp*, Sexp*, Sexp*, Sexp*, Sexp*, Sexp*, Sexp*);
Sexp* sexp_list9(Sexp*, Sexp*, Sexp*, Sexp*, Sexp*, Sexp*, Sexp*, Sexp*, Sexp*);

#endif /* INCLUDE_GUARD_3397EB56_FB26_40B7_AD9E_F7B3DA519335 */
