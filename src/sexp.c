#include "sexp.h"

#include <stdlib.h>
#include <string.h>

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
static void sexp_set_car(Sexp *pair, Sexp *car) {
  assert(sexp_is_pair(pair));
  ((MutableSexp *)pair)->data.pair.car = car;
}
static void sexp_set_cdr(Sexp *pair, Sexp *cdr) {
  assert(sexp_is_pair(pair));
  ((MutableSexp *)pair)->data.pair.cdr = cdr;
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
Sexp *sexp_car(Sexp *sexp) {
  assert(sexp_is_pair(sexp));
  return sexp->data.pair.car;
}
Sexp *sexp_cdr(Sexp *sexp) {
  assert(sexp_is_pair(sexp));
  return sexp->data.pair.cdr;
}
Bool sexp_eq(Sexp *sexp, const char *symbol) {
  assert(sexp_is_symbol(sexp));
  return 0 == strcmp(sexp->data.symbol, symbol);
}
const char *sexp_get_string(Sexp *sexp) {
  if (sexp_is_string(sexp)) {
    return string_begin((String *)sexp->data.string);
  } else if (sexp_is_symbol(sexp)) {
    return sexp->data.symbol;
  } else {
    assert(0);
    return nil;
  }
}
Sexp *sexp_snoc(Sexp *xs, Sexp *x) {
  if (sexp_is_pair(xs)) {
    Sexp *cdr = sexp_cdr(xs);
    if (sexp_is_pair(cdr)) {
      sexp_snoc(cdr, x);
    } else {
      sexp_set_cdr(xs, sexp_cons(x, cdr));
    }
    return xs;
  } else {
    return sexp_cons(x, xs);
  }
}
Sexp *sexp_list1(Sexp *sexp0) {
  return sexp_cons(sexp0, sexp_nil());
}
Sexp *sexp_list2(Sexp *sexp0, Sexp *sexp1) {
  return sexp_cons(sexp0, sexp_list1(sexp1));
}
Sexp *sexp_list3(Sexp *sexp0, Sexp *sexp1, Sexp *sexp2) {
  return sexp_cons(sexp0, sexp_list2(sexp1, sexp2));
}
Sexp *sexp_list4(Sexp *sexp0, Sexp *sexp1, Sexp *sexp2, Sexp *sexp3) {
  return sexp_cons(sexp0, sexp_list3(sexp1, sexp2, sexp3));
}
Sexp *sexp_list5(Sexp *sexp0, Sexp *sexp1, Sexp *sexp2, Sexp *sexp3,
                 Sexp *sexp4) {
  return sexp_cons(sexp0, sexp_list4(sexp1, sexp2, sexp3, sexp4));
}
