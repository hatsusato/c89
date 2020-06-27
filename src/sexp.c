#include "sexp.h"

#include <stdlib.h>

typedef enum { SEXP_PAIR, SEXP_SYMBOL } SexpKind;

struct struct_Sexp {
  SexpKind kind;
  union {
    struct {
      Sexp *car, *cdr;
    } pair;
    const char *symbol;
  } data;
};

Sexp *sexp_cons(Sexp *car, Sexp *cdr) {
  struct struct_Sexp *sexp = malloc(sizeof(Sexp));
  sexp->kind = SEXP_PAIR;
  sexp->data.pair.car = car;
  sexp->data.pair.cdr = cdr;
  return sexp;
}
Sexp *sexp_symbol(const char *symbol) {
  struct struct_Sexp *sexp = malloc(sizeof(Sexp));
  sexp->kind = SEXP_SYMBOL;
  sexp->data.symbol = symbol;
  return sexp;
}
