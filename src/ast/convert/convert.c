#include "convert.h"

#include "ast/tag.h"
#include "sexp/sexp.h"
#include "utility/utility.h"

static Sexp *convert_list(Sexp *sexp) {
  Sexp *ret = sexp_nil();
  UTILITY_ASSERT(sexp_is_list(sexp));
  for (; sexp_is_pair(sexp); sexp = sexp_cdr(sexp)) {
    ret = sexp_snoc(ret, convert_ast(sexp_car(sexp)));
  }
  return ret;
}
static Sexp *convert_cons_tag(SyntaxTag tag, Sexp *cdr) {
  return sexp_pair(sexp_number(tag), cdr);
}
static Sexp *identifier_from_declarator(Sexp *sexp) {
  Size leng = sexp_length(sexp);
  switch (sexp_get_tag(sexp)) {
  case SYNTAX_IDENTIFIER:
    return sexp;
  case SYNTAX_DECLARATOR:
    UTILITY_ASSERT(2 == leng || 3 == leng);
    sexp = sexp_at(sexp, leng - 1);
    break;
  case SYNTAX_DIRECT_DECLARATOR:
    UTILITY_ASSERT(2 == leng || 4 == leng || 5 == leng);
    sexp = sexp_at(sexp, 4 == leng ? 2 : 1);
    break;
  default:
    UTILITY_ASSERT(0);
    break;
  }
  return identifier_from_declarator(sexp);
}
int count_return_statement(Sexp *sexp) {
  Size leng = sexp_length(sexp);
  int sum = 0;
  switch (sexp_get_tag(sexp)) {
  case SYNTAX_STATEMENT:
    return count_return_statement(sexp_at(sexp, 1));
  case SYNTAX_LABELED_STATEMENT:
    return count_return_statement(sexp_at(sexp, leng - 1));
  case SYNTAX_COMPOUND_STATEMENT:
    return count_return_statement(sexp_at(sexp, 3));
  case SYNTAX_DECLARATION_LIST:
    return 0;
  case SYNTAX_STATEMENT_LIST:
    for (sexp = sexp_cdr(sexp); sexp_is_pair(sexp); sexp = sexp_cdr(sexp)) {
      sum += count_return_statement(sexp_car(sexp));
    }
    return sum;
  case SYNTAX_EXPRESSION_STATEMENT:
    return 0;
  case SYNTAX_SELECTION_STATEMENT:
    UTILITY_ASSERT(6 == leng || 8 == leng);
    sum += count_return_statement(sexp_at(sexp, 5));
    if (8 == leng) {
      sum += count_return_statement(sexp_at(sexp, 7));
    }
    return sum;
  case SYNTAX_ITERATION_STATEMENT:
    UTILITY_ASSERT(6 == leng || 8 == leng || 10 == leng);
    return count_return_statement(sexp_at(sexp, 8 == leng ? 2 : leng - 1));
  case SYNTAX_JUMP_STATEMENT:
    return SYNTAX_RETURN == sexp_get_tag(sexp_at(sexp, 1)) ? 1 : 0;
  default:
    UTILITY_ASSERT(0);
    return 0;
  }
}

/* translation-unit ::=
   (external-declaration | function-definition)+ */
static Sexp *convert_translation_unit(Sexp *sexp) {
  SyntaxTag tag = ABSTRACT_TRANSLATION_UNIT;
  return convert_cons_tag(tag, convert_list(sexp_cdr(sexp)));
}
/* external-declaration ::=
   declaration */
static Sexp *convert_external_declaration(Sexp *sexp) {
  SyntaxTag tag = ABSTRACT_EXTERNAL_DECLARATION;
  return convert_cons_tag(tag, convert_ast(sexp_cdr(sexp)));
}
/* function-definition ::=
   declaration-specifiers
   declarator
   declaration-list.opt
   compound-statement
   identifier // function name
   <integer> // count of return statement
*/
static Sexp *convert_function_definition(Sexp *sexp) {
  SyntaxTag tag = ABSTRACT_FUNCTION_DEFINITION;
  Sexp *list = convert_ast(sexp_cdr(sexp));
  Sexp *ident, *count;
  if (sexp_length(sexp) == 4) {
    Sexp *type = sexp_number(SYNTAX_INT);
    type = convert_cons_tag(SYNTAX_TYPE_SPECIFIER, type);
    type = convert_cons_tag(SYNTAX_DECLARATION_SPECIFIERS, type);
    list = sexp_pair(type, list);
  } else {
    UTILITY_ASSERT(sexp_length(sexp) == 5);
  }
  ident = sexp_at(list, 1); /* declarator */
  ident = identifier_from_declarator(ident);
  ident = sexp_clone(ident);
  count = sexp_at(list, 3); /* compound-statement */
  count = sexp_number(count_return_statement(count));
  list = sexp_snoc(list, ident);
  list = sexp_snoc(list, count);
  return convert_cons_tag(tag, list);
}

Sexp *convert_ast(Sexp *sexp) {
  switch (sexp_get_tag(sexp)) {
  case SYNTAX_TRANSLATION_UNIT:
    return convert_translation_unit(sexp);
  case SYNTAX_EXTERNAL_DECLARATION:
    return convert_external_declaration(sexp);
  case SYNTAX_FUNCTION_DEFINITION:
    return convert_function_definition(sexp);
  default:
    return sexp_clone(sexp);
  }
}
