#include "convert.h"

#include "sexp/sexp.h"
#include "utility/utility.h"

Sexp *ast_convert_list(Sexp *sexp) {
  Sexp *ret = sexp_nil();
  UTILITY_ASSERT(sexp_is_list(sexp));
  for (; sexp_is_pair(sexp); sexp = sexp_cdr(sexp)) {
    ret = sexp_snoc(ret, ast_convert(sexp_car(sexp)));
  }
  return ret;
}

Sexp *ast_convert(Sexp *sexp) {
  switch (sexp_get_tag(sexp)) {
  default:
    return sexp_clone(sexp);
  }
}
