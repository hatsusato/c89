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

static SexpKind sexp_kind(Sexp *sexp) {
  return sexp ? sexp->kind : SEXP_NIL;
}

Sexp *sexp_nil(void) {
  return nil;
}
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
Sexp *sexp_string(const char *text, int leng) {
  struct struct_Sexp *sexp = malloc(sizeof(Sexp));
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
