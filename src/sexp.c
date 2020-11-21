#include "sexp.h"

#include "str.h"
#include "utility.h"

typedef enum {
  SEXP_NIL,
  SEXP_PAIR,
  SEXP_STRING,
  SEXP_SYMBOL,
  SEXP_NUMBER
} SexpKind;

struct struct_Sexp {
  SexpKind kind;
  union {
    const void *nil;
    struct {
      Sexp *car, *cdr;
    } pair;
    const Str *string;
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
  UTILITY_FREE(sexp);
}
static Sexp *sexp_set_cdr(Sexp *sexp, Sexp *cdr) {
  Sexp *tmp = sexp_cdr(sexp);
  ((MutableSexp *)sexp)->data.pair.cdr = cdr;
  return tmp;
}

void sexp_delete(Sexp *sexp) {
  if (sexp_is_pair(sexp)) {
    sexp_delete(sexp->data.pair.car);
    sexp_delete(sexp->data.pair.cdr);
  } else if (sexp_is_string(sexp)) {
    str_delete((Str *)sexp->data.string);
  }
  if (!sexp_is_nil(sexp)) {
    sexp_free((MutableSexp *)sexp);
  }
}
Sexp *sexp_clone(Sexp *sexp) {
  switch (sexp_kind(sexp)) {
  case SEXP_PAIR:
    return sexp_pair(sexp_clone(sexp_car(sexp)), sexp_clone(sexp_cdr(sexp)));
  case SEXP_STRING:
    return sexp_string(str_begin(sexp->data.string),
                       str_length(sexp->data.string));
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
Sexp *sexp_string(const char *text, Size leng) {
  MutableSexp *sexp = sexp_new(SEXP_STRING);
  sexp->data.string = str_new(text, leng);
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
Bool sexp_is_nil(Sexp *sexp) {
  return SEXP_NIL == sexp_kind(sexp);
}
Bool sexp_is_pair(Sexp *sexp) {
  return SEXP_PAIR == sexp_kind(sexp);
}
Bool sexp_is_string(Sexp *sexp) {
  return SEXP_STRING == sexp_kind(sexp);
}
Bool sexp_is_symbol(Sexp *sexp) {
  return SEXP_SYMBOL == sexp_kind(sexp);
}
Bool sexp_is_number(Sexp *sexp) {
  return SEXP_NUMBER == sexp_kind(sexp);
}
Bool sexp_is_list(Sexp *list) {
  if (sexp_is_nil(list)) {
    return true;
  } else {
    return sexp_is_pair(list) && sexp_is_list(sexp_cdr(list));
  }
}
Sexp *sexp_car(Sexp *sexp) {
  assert(sexp_is_pair(sexp));
  return sexp->data.pair.car;
}
Sexp *sexp_cdr(Sexp *sexp) {
  assert(sexp_is_pair(sexp));
  return sexp->data.pair.cdr;
}
Sexp *sexp_snoc(Sexp *xs, Sexp *x) {
  Sexp *it;
  for (it = xs; sexp_is_pair(it); it = sexp_cdr(it)) {
    if (!sexp_is_pair(sexp_cdr(it))) {
      sexp_set_cdr(it, sexp_pair(x, sexp_cdr(it)));
      return xs;
    }
  }
  return sexp_pair(x, xs);
}
Sexp *sexp_at(Sexp *sexp, Index index) {
  assert(sexp_is_pair(sexp));
  if (0 < index) {
    return sexp_at(sexp_cdr(sexp), index - 1);
  } else {
    return sexp_car(sexp);
  }
}
const char *sexp_get_string(Sexp *sexp) {
  return sexp_is_string(sexp)   ? str_begin(sexp->data.string)
         : sexp_is_symbol(sexp) ? sexp->data.symbol
                                : NULL;
}
int sexp_get_number(Sexp *sexp) {
  if (sexp_is_number(sexp)) {
    return sexp->data.number;
  }
  return 0;
}
int sexp_length(Sexp *list) {
  if (sexp_is_pair(list)) {
    return 1 + sexp_length(sexp_cdr(list));
  } else {
    return 0;
  }
}
