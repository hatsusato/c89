#include "register.h"

#include "sexp.h"
#include "utility.h"

static Bool register_check_tag(Sexp *ast, const char *tag) {
  return sexp_is_pair(ast) && sexp_is_list(ast) && sexp_eq(sexp_car(ast), tag);
}

void register_foreach(Register *reg, Sexp *ast,
                      void (*map)(Register *, Sexp *)) {
  for (ast = sexp_cdr(ast); sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    map(reg, sexp_car(ast));
  }
}
void register_is_typedef(Register *reg, Sexp *ast) {
  assert(register_check_tag(ast, "storage-class-specifier") ||
         register_check_tag(ast, "type-specifier") ||
         register_check_tag(ast, "type-qualifier"));
  if (register_check_tag(ast, "storage-class-specifier") &&
      sexp_eq(sexp_at(ast, 1), "typedef")) {
    reg->flag = true;
  }
}
