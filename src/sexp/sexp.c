#include "sexp.h"

#include "utility/utility.h"

typedef enum { SEXP_NIL, SEXP_PAIR, SEXP_SYMBOL, SEXP_NUMBER } SexpKind;

struct struct_Sexp {
  SexpKind kind;
  union {
    const void *nil;
    struct {
      Sexp *car, *cdr;
    } pair;
    const char *symbol;
    int number;
  } data;
};
typedef struct struct_Sexp MutableSexp;

static SexpKind sexp_kind(Sexp *sexp) {
  assert(sexp);
  return sexp->kind;
}
static MutableSexp *sexp_new(SexpKind kind) {
  MutableSexp *sexp = UTILITY_MALLOC(MutableSexp);
  sexp->kind = kind;
  return sexp;
}
static void sexp_free(MutableSexp *sexp) {
  if (sexp_nil() != sexp) {
    UTILITY_FREE(sexp);
  }
}
static void sexp_set_cdr(Sexp *sexp, Sexp *cdr) {
  UTILITY_ASSERT(sexp_is_pair(sexp));
  ((MutableSexp *)sexp)->data.pair.cdr = cdr;
}
static void sexp_set_cdar(Sexp *sexp, Sexp *cdar) {
  UTILITY_ASSERT(sexp_is_pair(sexp));
  sexp_set_cdr(sexp, sexp_pair(cdar, sexp_cdr(sexp)));
}

void sexp_delete(Sexp *sexp) {
  if (sexp_is_pair(sexp)) {
    sexp_delete(sexp->data.pair.car);
    sexp_delete(sexp->data.pair.cdr);
  }
  sexp_free((MutableSexp *)sexp);
}
Sexp *sexp_clone(Sexp *sexp) {
  switch (sexp_kind(sexp)) {
  case SEXP_PAIR:
    return sexp_pair(sexp_clone(sexp_car(sexp)), sexp_clone(sexp_cdr(sexp)));
  case SEXP_SYMBOL:
    return sexp_symbol(sexp->data.symbol);
  case SEXP_NUMBER:
    return sexp_number(sexp->data.number);
  default:
    assert(sexp_is_nil(sexp));
    return sexp_nil();
  }
}
Sexp *sexp_nil(void) {
  static MutableSexp sexp = {SEXP_NIL, {NULL}};
  return &sexp;
}
Sexp *sexp_pair(Sexp *car, Sexp *cdr) {
  MutableSexp *sexp = sexp_new(SEXP_PAIR);
  sexp->data.pair.car = car;
  sexp->data.pair.cdr = cdr;
  return sexp;
}
Sexp *sexp_symbol(const char *symbol) {
  MutableSexp *sexp = sexp_new(SEXP_SYMBOL);
  sexp->data.symbol = symbol;
  return sexp;
}
Sexp *sexp_number(int number) {
  MutableSexp *sexp = sexp_new(SEXP_NUMBER);
  sexp->data.number = number;
  return sexp;
}
Sexp *sexp_bool(Bool bool) {
  return bool ? sexp_symbol("t") : sexp_nil();
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
Bool sexp_is_number(Sexp *sexp) {
  return SEXP_NUMBER == sexp_kind(sexp);
}
Bool sexp_is_true(Sexp *sexp) {
  return !sexp_is_nil(sexp);
}
Bool sexp_is_list(Sexp *list) {
  while (sexp_is_pair(list)) {
    list = sexp_cdr(list);
  }
  return sexp_is_nil(list);
}
Sexp *sexp_append(Sexp *xs, Sexp *ys) {
  UTILITY_ASSERT(sexp_is_list(xs));
  if (sexp_is_pair(xs)) {
    Sexp *it = xs;
    while (sexp_is_pair(sexp_cdr(it))) {
      it = sexp_cdr(it);
    }
    UTILITY_ASSERT(sexp_is_nil(sexp_cdr(it)));
    sexp_set_cdr(it, ys);
    return xs;
  } else {
    UTILITY_ASSERT(sexp_is_nil(xs));
    return ys;
  }
}
Sexp *sexp_snoc(Sexp *xs, Sexp *x) {
  if (sexp_is_pair(xs)) {
    Sexp *it = xs;
    while (sexp_is_pair(sexp_cdr(it))) {
      it = sexp_cdr(it);
    }
    sexp_set_cdar(it, x);
  } else {
    xs = sexp_pair(x, xs);
  }
  return xs;
}
Sexp *sexp_car(Sexp *sexp) {
  assert(sexp_is_pair(sexp));
  return sexp->data.pair.car;
}
Sexp *sexp_cdr(Sexp *sexp) {
  assert(sexp_is_pair(sexp));
  return sexp->data.pair.cdr;
}
Sexp *sexp_at(Sexp *sexp, Index index) {
  assert(sexp_is_pair(sexp));
  for (; 0 < index; --index) {
    assert(sexp_is_pair(sexp));
    sexp = sexp_cdr(sexp);
  }
  return sexp_car(sexp);
}
const char *sexp_get_symbol(Sexp *sexp) {
  return sexp_is_symbol(sexp) ? sexp->data.symbol : NULL;
}
int sexp_get_number(Sexp *sexp) {
  return sexp_is_number(sexp) ? sexp->data.number : 0;
}
int sexp_length(Sexp *list) {
  int i = 0;
  for (; sexp_is_pair(list); ++i) {
    list = sexp_cdr(list);
  }
  return i;
}
int sexp_get_tag(Sexp *sexp) {
  if (sexp_is_pair(sexp)) {
    return sexp_get_tag(sexp_car(sexp));
  } else {
    assert(sexp_is_number(sexp));
    return sexp_get_number(sexp);
  }
}
