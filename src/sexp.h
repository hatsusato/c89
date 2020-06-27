#ifndef INCLUDE_GUARD_3397EB56_FB26_40B7_AD9E_F7B3DA519335
#define INCLUDE_GUARD_3397EB56_FB26_40B7_AD9E_F7B3DA519335

struct struct_Sexp;
typedef struct struct_Sexp const Sexp;

Sexp* sexp_cons(Sexp*, Sexp*);
Sexp* sexp_symbol(const char*);
Sexp* sexp_string(const char*, int);
void sexp_delete(Sexp*);

#endif /* INCLUDE_GUARD_3397EB56_FB26_40B7_AD9E_F7B3DA519335 */
