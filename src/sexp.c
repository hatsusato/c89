#include "sexp.h"

typedef enum { SEXP_PAIR } SexpKind;

struct struct_Sexp {
  SexpKind kind;
  union {
    struct {
      Sexp *car, *cdr;
    } pair;
  } data;
};
