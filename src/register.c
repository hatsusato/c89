#include "register.h"

#include "sexp.h"

void register_foreach(Register *reg, Sexp *ast,
                      void (*map)(Register *, Sexp *)) {
  for (ast = sexp_cdr(ast); sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    map(reg, sexp_car(ast));
  }
}
