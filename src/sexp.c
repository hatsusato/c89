#include "sexp.h"

#include <stdlib.h>

typedef enum { SEXP_PAIR } SexpKind;

struct struct_Sexp {
  SexpKind kind;
  union {
    struct {
      Sexp *car, *cdr;
    } pair;
  } data;
};

Sexp *sexp_cons(Sexp *car, Sexp *cdr) {
  Sexp *sexp = malloc(sizeof(Sexp));
  sexp->kind = SEXP_PAIR;
  sexp->data.pair.car = car;
  sexp->data.pair.cdr = cdr;
  return sexp;
}
