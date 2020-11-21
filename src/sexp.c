#include "sexp.h"

#include "str.h"
#include "utility.h"

typedef enum { SEXP_NIL, SEXP_PAIR, SEXP_STRING, SEXP_NUMBER } SexpKind;

struct struct_Sexp {
  SexpKind kind;
  union {
    const void *nil;
    struct {
      Sexp *car, *cdr;
    } pair;
    const Str *string;
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

Sexp *sexp_nil(void) {
  static MutableSexp sexp = {SEXP_NIL, {NULL}};
  return &sexp;
}
Sexp *sexp_cons(Sexp *car, Sexp *cdr) {
  MutableSexp *sexp = sexp_new(SEXP_PAIR);
  sexp->data.pair.car = car;
  sexp->data.pair.cdr = cdr;
  return sexp;
}
Sexp *sexp_snoc(Sexp *xs, Sexp *x) {
  Sexp *sexp = xs;
  assert(sexp_is_list(xs));
  for (; sexp_is_pair(sexp); sexp = sexp_cdr(sexp)) {
    if (sexp_is_nil(sexp_cdr(sexp))) {
      sexp_set_cdr(sexp, sexp_cons(x, sexp_cdr(sexp)));
      return xs;
    }
  }
  assert(sexp_is_nil(xs));
  return sexp_cons(x, xs);
}
Sexp *sexp_append(Sexp *lhs, Sexp *rhs) {
  Sexp *sexp = lhs;
  assert(sexp_is_list(lhs));
  for (; sexp_is_pair(sexp); sexp = sexp_cdr(sexp)) {
    if (sexp_is_nil(sexp_cdr(sexp))) {
      sexp_set_cdr(sexp, rhs);
      return lhs;
    }
  }
  assert(sexp_is_nil(lhs));
  return rhs;
}
Sexp *sexp_string(const char *text, int leng) {
  MutableSexp *sexp = sexp_new(SEXP_STRING);
  sexp->data.string = str_new(text, leng);
  return sexp;
}
Sexp *sexp_number(int i) {
  MutableSexp *sexp = sexp_new(SEXP_NUMBER);
  sexp->data.number = i;
  return sexp;
}
Sexp *sexp_clone(Sexp *sexp) {
  if (sexp_is_string(sexp)) {
    return sexp_string(str_begin(sexp->data.string),
                       str_length(sexp->data.string));
  } else if (sexp_is_number(sexp)) {
    return sexp_number(sexp->data.number);
  } else {
    return sexp_nil();
  }
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
    str_delete((Str *)sexp->data.string);
    break;
  default:
    break;
  }
  sexp_free((MutableSexp *)sexp);
}
Sexp *sexp_set_car(Sexp *sexp, Sexp *car) {
  Sexp *tmp = sexp_car(sexp);
  ((MutableSexp *)sexp)->data.pair.car = car;
  return tmp;
}
Sexp *sexp_set_cdr(Sexp *sexp, Sexp *cdr) {
  Sexp *tmp = sexp_cdr(sexp);
  ((MutableSexp *)sexp)->data.pair.cdr = cdr;
  return tmp;
}
void sexp_set_caar(Sexp *sexp, Sexp *caar) {
  assert(sexp_is_pair(sexp));
  sexp_set_car(sexp, sexp_cons(caar, sexp_car(sexp)));
}
void sexp_set_cadr(Sexp *sexp, Sexp *cadr) {
  assert(sexp_is_pair(sexp));
  sexp_set_car(sexp, sexp_cons(sexp_car(sexp), cadr));
}
void sexp_set_cdar(Sexp *sexp, Sexp *cdar) {
  assert(sexp_is_pair(sexp));
  sexp_set_cdr(sexp, sexp_cons(cdar, sexp_cdr(sexp)));
}
void sexp_set_cddr(Sexp *sexp, Sexp *cddr) {
  assert(sexp_is_pair(sexp));
  sexp_set_cdr(sexp, sexp_cons(sexp_cdr(sexp), cddr));
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
Bool sexp_is_number(Sexp *sexp) {
  return SEXP_NUMBER == sexp_kind(sexp);
}
Bool sexp_is_list(Sexp *list) {
  if (sexp_is_nil(list)) {
    return true;
  } else {
    return (sexp_is_pair(list) && sexp_is_list(sexp_cdr(list)));
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
Sexp *sexp_at(Sexp *sexp, int index) {
  if (0 < index) {
    return sexp_at(sexp_cdr(sexp), index - 1);
  } else {
    return sexp_car(sexp);
  }
}
Sexp *sexp_next(Sexp *sexp, int n) {
  Sexp *tmp = sexp;
  assert(sexp_is_pair(sexp));
  sexp = sexp_car(sexp);
  assert(sexp_is_number(sexp));
  assert(sexp_get_number(sexp) == n);
  return sexp_cdr(tmp);
}
const char *sexp_get_string(Sexp *sexp) {
  return sexp_is_string(sexp) ? str_begin(sexp->data.string) : NULL;
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
