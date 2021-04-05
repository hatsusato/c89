#include "definition.h"

#include "ast/convert/convert.h"
#include "ast/get.h"
#include "ast/tag.h"
#include "sexp/sexp.h"
#include "utility/utility.h"

static Sexp *name_of_declarator(Sexp *sexp) {
  Size leng = sexp_length(sexp);
  switch (sexp_get_tag(sexp)) {
  case SYNTAX_IDENTIFIER:
    sexp = sexp_at(sexp, 1);
    UTILITY_ASSERT(sexp_is_symbol(sexp));
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
  return name_of_declarator(sexp);
}
static int count_return_statement(Sexp *sexp) {
  Size leng = sexp_length(sexp);
  int sum = 0;
  switch (sexp_get_tag(sexp)) {
  case SYNTAX_STATEMENT:
    return count_return_statement(sexp_at(sexp, 1));
  case SYNTAX_LABELED_STATEMENT:
    return count_return_statement(sexp_at(sexp, leng - 1));
  case ABSTRACT_COMPOUND_STATEMENT:
    sexp = ast_get_statement_list(sexp);
    for (; sexp_is_pair(sexp); sexp = sexp_cdr(sexp)) {
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
Sexp *convert_translation_unit(Sexp *sexp) {
  SyntaxTag tag = ABSTRACT_TRANSLATION_UNIT;
  return convert_cons_tag(tag, convert_list(sexp_cdr(sexp)));
}
/* external-declaration ::=
   declaration */
Sexp *convert_external_declaration(Sexp *sexp) {
  SyntaxTag tag = ABSTRACT_EXTERNAL_DECLARATION;
  return convert_cons_tag(tag, convert_ast(sexp_cdr(sexp)));
}
/* function-definition ::=
   declaration-specifiers
   declarator
   declaration-list.opt
   compound-statement
   <function name>:symbol
   <has multiple return statement>:bool
*/
Sexp *convert_function_definition(Sexp *sexp) {
  SyntaxTag tag = ABSTRACT_FUNCTION_DEFINITION;
  Sexp *list = convert_ast(sexp_cdr(sexp));
  Sexp *decl = sexp_at(list, 1);
  Sexp *body = sexp_at(list, 3);
  if (sexp_length(sexp) == 4) {
    Sexp *type = sexp_number(SYNTAX_INT);
    type = convert_cons_tag(SYNTAX_TYPE_SPECIFIER, type);
    type = convert_cons_tag(SYNTAX_DECLARATION_SPECIFIERS, type);
    list = sexp_pair(type, list);
  } else {
    UTILITY_ASSERT(sexp_length(sexp) == 5);
  }
  list = sexp_snoc(list, name_of_declarator(decl));
  list = sexp_snoc(list, sexp_bool(1 < count_return_statement(body)));
  return convert_cons_tag(tag, list);
}

Sexp *ast_get_function_name(Sexp *sexp) {
  UTILITY_ASSERT(ABSTRACT_FUNCTION_DEFINITION == sexp_get_tag(sexp));
  UTILITY_ASSERT(7 == sexp_length(sexp));
  return sexp_at(sexp, 5);
}
Sexp *ast_get_function_return_count(Sexp *sexp) {
  UTILITY_ASSERT(ABSTRACT_FUNCTION_DEFINITION == sexp_get_tag(sexp));
  UTILITY_ASSERT(7 == sexp_length(sexp));
  return sexp_at(sexp, 6);
}
