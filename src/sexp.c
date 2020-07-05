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
  if (sexp_is_pair(xs)) {
    Sexp *cdr = xs->data.pair.cdr;
    if (sexp_is_pair(cdr)) {
      sexp_snoc(cdr, x);
    } else {
      ((MutableSexp *)xs)->data.pair.cdr = sexp_cons(x, cdr);
    }
    return xs;
  } else {
    return sexp_cons(x, xs);
  }
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
Bool sexp_is_list(Sexp *list) {
  if (sexp_is_nil(list)) {
    return true;
  } else {
    return (sexp_is_pair(list) && sexp_is_list(sexp_cdr(list)));
  }
}
int sexp_length(Sexp *list) {
  if (sexp_is_pair(list)) {
    return 1 + sexp_length(sexp_cdr(list));
  } else {
    return 0;
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
Sexp *sexp_at(Sexp *sexp, int index) {
  if (0 < index) {
    return sexp_at(sexp_cdr(sexp), index - 1);
  } else {
    return sexp_car(sexp);
  }
}
Sexp *sexp_last(Sexp *sexp) {
  for (; sexp_is_pair(sexp); sexp = sexp_cdr(sexp)) {
    if (sexp_is_nil(sexp_cdr(sexp))) {
      return sexp_car(sexp);
    }
  }
  return sexp_nil();
}
Bool sexp_eq(Sexp *sexp, const char *symbol) {
  assert(sexp_is_symbol(sexp));
  return utility_str_eq(sexp->data.symbol, symbol);
}
const char *sexp_get_string(Sexp *sexp) {
  if (sexp_is_string(sexp)) {
    return string_begin((String *)sexp->data.string);
  } else if (sexp_is_symbol(sexp)) {
    return sexp->data.symbol;
  } else {
    return nil;
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
Sexp *sexp_list6(Sexp *sexp0, Sexp *sexp1, Sexp *sexp2, Sexp *sexp3,
                 Sexp *sexp4, Sexp *sexp5) {
  return sexp_cons(sexp0, sexp_list5(sexp1, sexp2, sexp3, sexp4, sexp5));
}
Sexp *sexp_list7(Sexp *sexp0, Sexp *sexp1, Sexp *sexp2, Sexp *sexp3,
                 Sexp *sexp4, Sexp *sexp5, Sexp *sexp6) {
  return sexp_cons(sexp0, sexp_list6(sexp1, sexp2, sexp3, sexp4, sexp5, sexp6));
}
Sexp *sexp_list8(Sexp *sexp0, Sexp *sexp1, Sexp *sexp2, Sexp *sexp3,
                 Sexp *sexp4, Sexp *sexp5, Sexp *sexp6, Sexp *sexp7) {
  return sexp_cons(sexp0,
                   sexp_list7(sexp1, sexp2, sexp3, sexp4, sexp5, sexp6, sexp7));
}
Sexp *sexp_list9(Sexp *sexp0, Sexp *sexp1, Sexp *sexp2, Sexp *sexp3,
                 Sexp *sexp4, Sexp *sexp5, Sexp *sexp6, Sexp *sexp7,
                 Sexp *sexp8) {
  return sexp_cons(sexp0, sexp_list8(sexp1, sexp2, sexp3, sexp4, sexp5, sexp6,
                                     sexp7, sexp8));
}
