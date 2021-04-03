#include "convert.h"

#include "sexp/sexp.h"
Sexp *ast_convert(Sexp *sexp) {
  switch (sexp_get_tag(sexp)) {
  default:
    return sexp_clone(sexp);
  }
}
