#include "statement.h"

#include "ast/convert/convert.h"
#include "sexp/sexp.h"
#include "utility/utility.h"

Sexp* convert_statement(Sexp* sexp) {
  sexp = sexp_cdr(sexp);
  sexp = sexp_car(sexp);
  return convert_ast(sexp);
}
Sexp* convert_labeled_statement(Sexp* sexp) {
  sexp = sexp_cdr(sexp);
  switch (sexp_get_tag(sexp)) {
  case SYNTAX_IDENTIFIER:
  case SYNTAX_CASE:
  case SYNTAX_DEFAULT:
    sexp = convert_ast(sexp);
    break;
  default:
    UTILITY_ASSERT(0);
    break;
  }
  return convert_cons_tag(SYNTAX_LABELED_STATEMENT, sexp);
}
/* compound-statement ::=
   declaration-list
   statement-list */
Sexp* convert_compound_statement(Sexp* sexp) {
  SyntaxTag tag = ABSTRACT_COMPOUND_STATEMENT;
  Sexp* decls = sexp_at(sexp, 2);
  Sexp* stats = sexp_at(sexp, 3);
  Sexp* list = sexp_nil();
  UTILITY_ASSERT(SYNTAX_DECLARATION_LIST == sexp_get_tag(decls));
  UTILITY_ASSERT(SYNTAX_STATEMENT_LIST == sexp_get_tag(stats));
  decls = sexp_cdr(decls);
  stats = sexp_cdr(stats);
  list = sexp_snoc(list, convert_list(decls));
  list = sexp_snoc(list, convert_list(stats));
  return convert_cons_tag(tag, list);
}

Sexp* ast_get_label_goto(Sexp* sexp) {
  UTILITY_ASSERT(SYNTAX_LABELED_STATEMENT == sexp_get_tag(sexp));
  sexp = sexp_cdr(sexp);
  UTILITY_ASSERT(SYNTAX_IDENTIFIER == sexp_get_tag(sexp));
  sexp = sexp_car(sexp);
  UTILITY_ASSERT(SYNTAX_IDENTIFIER == sexp_get_tag(sexp));
  sexp = sexp_at(sexp, 1);
  UTILITY_ASSERT(sexp_is_symbol(sexp));
  return sexp;
}
Sexp* ast_get_label_case(Sexp* sexp) {
  UTILITY_ASSERT(SYNTAX_LABELED_STATEMENT == sexp_get_tag(sexp));
  sexp = sexp_cdr(sexp);
  UTILITY_ASSERT(SYNTAX_CASE == sexp_get_tag(sexp));
  return sexp_at(sexp, 1);
}
Sexp* ast_get_label_statement(Sexp* sexp) {
  UTILITY_ASSERT(SYNTAX_LABELED_STATEMENT == sexp_get_tag(sexp));
  sexp = sexp_cdr(sexp);
  switch (sexp_get_tag(sexp)) {
  case SYNTAX_IDENTIFIER:
    return sexp_at(sexp, 2);
  case SYNTAX_CASE:
    return sexp_at(sexp, 3);
  case SYNTAX_DEFAULT:
    return sexp_at(sexp, 2);
  default:
    UTILITY_ASSERT(0);
    return NULL;
  }
}
Sexp* ast_get_declaration_list(Sexp* sexp) {
  UTILITY_ASSERT(ABSTRACT_COMPOUND_STATEMENT == sexp_get_tag(sexp));
  UTILITY_ASSERT(3 == sexp_length(sexp));
  return sexp_at(sexp, 1);
}
Sexp* ast_get_statement_list(Sexp* sexp) {
  UTILITY_ASSERT(ABSTRACT_COMPOUND_STATEMENT == sexp_get_tag(sexp));
  UTILITY_ASSERT(3 == sexp_length(sexp));
  return sexp_at(sexp, 2);
}
