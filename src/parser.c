#include "parser.h"

Sexp *parser_sexp_push(Sexp *list, Sexp *sexp) {
  sexp_snoc(sexp_at(list, 1), sexp);
  return list;
}
