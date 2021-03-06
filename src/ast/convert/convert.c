#include "convert.h"

#include "ast/convert/definition.h"
#include "ast/convert/statement.h"
#include "ast/tag.h"
#include "sexp/sexp.h"
#include "utility/utility.h"

Sexp *convert_list(Sexp *sexp) {
  Sexp *ret = sexp_nil();
  UTILITY_ASSERT(sexp_is_list(sexp));
  for (; sexp_is_pair(sexp); sexp = sexp_cdr(sexp)) {
    ret = sexp_snoc(ret, convert_ast(sexp_car(sexp)));
  }
  return ret;
}
Sexp *convert_cons_tag(SyntaxTag tag, Sexp *cdr) {
  return sexp_pair(sexp_number(tag), cdr);
}

Sexp *convert_ast(Sexp *sexp) {
  if (!sexp_is_pair(sexp)) {
    return sexp_clone(sexp);
  }
  switch (sexp_get_tag(sexp)) {
  case SYNTAX_STATEMENT:
    return convert_statement(sexp);
  case SYNTAX_LABELED_STATEMENT:
    return convert_labeled_statement(sexp);
  case SYNTAX_COMPOUND_STATEMENT:
    return convert_compound_statement(sexp);
  case SYNTAX_DECLARATION_LIST:
  case SYNTAX_STATEMENT_LIST:
    UTILITY_ASSERT(0);
    break;
  case SYNTAX_TRANSLATION_UNIT:
    return convert_translation_unit(sexp);
  case SYNTAX_EXTERNAL_DECLARATION:
    return convert_external_declaration(sexp);
  case SYNTAX_FUNCTION_DEFINITION:
    return convert_function_definition(sexp);
  default:
    return convert_list(sexp);
  }
}
