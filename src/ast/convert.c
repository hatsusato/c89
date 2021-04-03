#include "convert.h"

#include "ast/tag.h"
#include "sexp/sexp.h"
#include "utility/utility.h"

static Sexp *ast_convert_list(Sexp *sexp) {
  Sexp *ret = sexp_nil();
  UTILITY_ASSERT(sexp_is_list(sexp));
  for (; sexp_is_pair(sexp); sexp = sexp_cdr(sexp)) {
    ret = sexp_snoc(ret, ast_convert(sexp_car(sexp)));
  }
  return ret;
}
/* translation-unit ::=
   (external-declaration | function-definition)+ */
static Sexp *ast_convert_translation_unit(Sexp *sexp) {
  SyntaxTag tag = ABSTRACT_TRANSLATION_UNIT;
  return sexp_pair(sexp_number(tag), ast_convert_list(sexp_cdr(sexp)));
}

Sexp *ast_convert(Sexp *sexp) {
  switch (sexp_get_tag(sexp)) {
  case SYNTAX_TRANSLATION_UNIT:
    return ast_convert_translation_unit(sexp);
  default:
    return sexp_clone(sexp);
  }
}
