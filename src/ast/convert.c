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
static Sexp *ast_tag_cons(SyntaxTag tag, Sexp *cdr) {
  return sexp_pair(sexp_number(tag), cdr);
}
/* translation-unit ::=
   (external-declaration | function-definition)+ */
static Sexp *ast_convert_translation_unit(Sexp *sexp) {
  SyntaxTag tag = ABSTRACT_TRANSLATION_UNIT;
  return ast_tag_cons(tag, ast_convert_list(sexp_cdr(sexp)));
}
/* external-declaration ::=
   declaration */
static Sexp *ast_convert_external_declaration(Sexp *sexp) {
  SyntaxTag tag = ABSTRACT_EXTERNAL_DECLARATION;
  return ast_tag_cons(tag, ast_convert(sexp_cdr(sexp)));
}
/* function-definition ::=
   declaration-specifiers
   declarator
   declaration-list.opt
   compound-statement */
static Sexp *ast_convert_function_definition(Sexp *sexp) {
  SyntaxTag tag = ABSTRACT_FUNCTION_DEFINITION;
  Sexp *list = ast_convert(sexp_cdr(sexp));
  if (sexp_length(sexp) == 4) {
    Sexp *type = sexp_number(SYNTAX_INT);
    type = ast_tag_cons(SYNTAX_TYPE_SPECIFIER, type);
    type = ast_tag_cons(SYNTAX_DECLARATION_SPECIFIERS, type);
    list = sexp_pair(type, list);
  } else {
    UTILITY_ASSERT(sexp_length(sexp) == 5);
  }
  return ast_tag_cons(tag, list);
}

Sexp *ast_convert(Sexp *sexp) {
  switch (sexp_get_tag(sexp)) {
  case SYNTAX_TRANSLATION_UNIT:
    return ast_convert_translation_unit(sexp);
  case SYNTAX_EXTERNAL_DECLARATION:
    return ast_convert_external_declaration(sexp);
  case SYNTAX_FUNCTION_DEFINITION:
    return ast_convert_function_definition(sexp);
  default:
    return sexp_clone(sexp);
  }
}
