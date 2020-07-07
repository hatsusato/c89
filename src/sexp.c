#include "sexp.h"

#include <stdlib.h>

#include "string.h"

typedef enum { SEXP_NIL, SEXP_PAIR, SEXP_SYMBOL, SEXP_STRING } SexpKind;

struct struct_Sexp {
  SexpKind kind;
  union {
    struct {
      Sexp *car, *cdr;
    } pair;
    const char *symbol;
    const String *string;
  } data;
};
typedef struct struct_Sexp MutableSexp;

static SexpKind sexp_kind(Sexp *sexp) {
  return sexp ? sexp->kind : SEXP_NIL;
}

Sexp *sexp_nil(void) {
  return nil;
}
Sexp *sexp_cons(Sexp *car, Sexp *cdr) {
  MutableSexp *sexp = malloc(sizeof(Sexp));
  sexp->kind = SEXP_PAIR;
  sexp->data.pair.car = car;
  sexp->data.pair.cdr = cdr;
  return sexp;
}
Sexp *sexp_snoc(Sexp *xs, Sexp *x) {
  Sexp *sexp = xs;
  assert(sexp_is_list(xs));
  while (sexp_is_pair(sexp)) {
    Sexp *cdr = sexp_cdr(sexp);
    if (sexp_is_nil(cdr)) {
      ((MutableSexp *)sexp)->data.pair.cdr = sexp_cons(x, cdr);
      return xs;
    }
    sexp = cdr;
  }
  assert(sexp_is_nil(sexp));
  return sexp_cons(x, xs);
}
Sexp *sexp_append(Sexp *lhs, Sexp *rhs) {
  Sexp *sexp = lhs;
  assert(sexp_is_list(lhs));
  while (sexp_is_pair(sexp)) {
    Sexp *cdr = sexp_cdr(sexp);
    if (sexp_is_nil(cdr)) {
      ((MutableSexp *)sexp)->data.pair.cdr = rhs;
      return lhs;
    }
    sexp = cdr;
  }
  assert(sexp_is_nil(sexp));
  return rhs;
}
Sexp *sexp_symbol(const char *symbol) {
  MutableSexp *sexp = malloc(sizeof(Sexp));
  sexp->kind = SEXP_SYMBOL;
  sexp->data.symbol = symbol;
  return sexp;
}
Sexp *sexp_string(const char *text, int leng) {
  MutableSexp *sexp = malloc(sizeof(Sexp));
  sexp->kind = SEXP_STRING;
  sexp->data.string = string_new_s(text, leng);
  return sexp;
}
void sexp_delete(Sexp *sexp) {
  switch (sexp_kind(sexp)) {
  case SEXP_NIL:
    return;
  case SEXP_PAIR:
    sexp_delete(sexp->data.pair.car);
    sexp_delete(sexp->data.pair.cdr);
    break;
  case SEXP_STRING:
    string_delete((String *)sexp->data.string);
    break;
  default:
    break;
  }
  free((void *)sexp);
}
Bool sexp_is_nil(Sexp *sexp) {
  return SEXP_NIL == sexp_kind(sexp);
}
Bool sexp_is_pair(Sexp *sexp) {
  return SEXP_PAIR == sexp_kind(sexp);
}
Bool sexp_is_symbol(Sexp *sexp) {
  return SEXP_SYMBOL == sexp_kind(sexp);
}
Bool sexp_is_string(Sexp *sexp) {
  return SEXP_STRING == sexp_kind(sexp);
}
Bool sexp_is_list(Sexp *list) {
  if (sexp_is_nil(list)) {
    return true;
  } else {
    return (sexp_is_pair(list) && sexp_is_list(sexp_cdr(list)));
  }
}
Bool sexp_eq(Sexp *sexp, const char *symbol) {
  return sexp_is_symbol(sexp) && utility_str_eq(sexp->data.symbol, symbol);
}
Sexp *sexp_car(Sexp *sexp) {
  assert(sexp_is_pair(sexp));
  return sexp->data.pair.car;
}
Sexp *sexp_cdr(Sexp *sexp) {
  assert(sexp_is_pair(sexp));
  return sexp->data.pair.cdr;
}
Sexp *sexp_at(Sexp *sexp, int index) {
  if (0 < index) {
    return sexp_at(sexp_cdr(sexp), index - 1);
  } else {
    return sexp_car(sexp);
  }
}
const char *sexp_get(Sexp *sexp) {
  if (sexp_is_string(sexp)) {
    return string_begin((String *)sexp->data.string);
  } else if (sexp_is_symbol(sexp)) {
    return sexp->data.symbol;
  } else {
    return nil;
  }
}
int sexp_length(Sexp *list) {
  if (sexp_is_pair(list)) {
    return 1 + sexp_length(sexp_cdr(list));
  } else {
    return 0;
  }
}
