#include "statement.h"

#include "ast/convert/convert.h"
#include "sexp/sexp.h"
#include "utility/utility.h"

Sexp* convert_statement(Sexp* sexp) {
  sexp = sexp_cdr(sexp);
  sexp = sexp_car(sexp);
  return convert_ast(sexp);
}

Sexp* ast_get_declaration_list(Sexp* sexp) {
  UTILITY_ASSERT(SYNTAX_COMPOUND_STATEMENT == sexp_get_tag(sexp));
  UTILITY_ASSERT(5 == sexp_length(sexp));
  return sexp_at(sexp, 2);
}
Sexp* ast_get_statement_list(Sexp* sexp) {
  UTILITY_ASSERT(SYNTAX_COMPOUND_STATEMENT == sexp_get_tag(sexp));
  UTILITY_ASSERT(5 == sexp_length(sexp));
  return sexp_at(sexp, 3);
}
