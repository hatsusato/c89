#include "pretty.h"

#include "ast/tag.h"
#include "print.h"
#include "sexp.h"
#include "utility.h"

static Sexp *pretty_convert(Sexp *, int);
static AstTag get_tag(Sexp *ast) {
  if (sexp_is_number(ast)) {
    return sexp_get_number(ast);
  }
  return AST_NULL;
}
static Bool check_tag(Sexp *ast, AstTag tag) {
  return sexp_is_pair(ast) && get_tag(sexp_car(ast)) == tag;
}
static Sexp *pretty_prefix(Sexp *ast, int indent, AstTag prefix) {
  switch (prefix) {
  case AST_NULL:
    return ast;
  case AST_NEWLINE:
    for (; 0 < indent; --indent) {
      ast = sexp_pair(sexp_number(AST_INDENT), ast);
    }
    break;
  default:
    break;
  }
  return sexp_pair(sexp_number(prefix), ast);
}
static Sexp *pretty_suffix(Sexp *ast, AstTag suffix) {
  switch (suffix) {
  case AST_NULL:
    return ast;
  default:
    return sexp_snoc(ast, sexp_number(suffix));
  }
}
static Sexp *pretty_snoc(Sexp *pretty, Sexp *ast, int indent, AstTag prefix) {
  if (!sexp_is_nil(ast)) {
    ast = pretty_convert(ast, indent);
    ast = sexp_pair(ast, sexp_nil());
    ast = pretty_prefix(ast, indent, prefix);
    pretty = sexp_snoc(pretty, ast);
  }
  return pretty;
}
static Sexp *pretty_convert(Sexp *ast, int indent) {
  AstTag delims[10] = {AST_NULL};
  Sexp *pretty = NULL;
  int i = 0, indent_diff = 0;
  assert(delims[9] == AST_NULL);
  if (sexp_is_pair(ast)) {
    AstTag tag = get_tag(sexp_car(ast));
    ast = sexp_cdr(ast);
    switch (tag) {
    case AST_ARGUMENT_EXPRESSION_LIST:
    case AST_EXPRESSION:
    case AST_PARAMETER_LIST:
    case AST_IDENTIFIER_LIST:
    case AST_INITIALIZER_LIST:
      delims[1] = AST_SEPARATOR;
      goto case_join;
    case AST_UNARY_EXPRESSION:
      if (2 == sexp_length(ast) && check_tag(ast, AST_SIZEOF) &&
          !check_tag(sexp_cdr(ast), AST_PRIMARY_EXPRESSION)) {
        delims[1] = AST_SPACE;
      }
      goto case_list;
    case AST_MULTIPLICATIVE_EXPRESSION:
    case AST_ADDITIVE_EXPRESSION:
    case AST_SHIFT_EXPRESSION:
    case AST_RELATIONAL_EXPRESSION:
    case AST_EQUALITY_EXPRESSION:
    case AST_AND_EXPRESSION:
    case AST_EXCLUSIVE_OR_EXPRESSION:
    case AST_INCLUSIVE_OR_EXPRESSION:
    case AST_LOGICAL_AND_EXPRESSION:
    case AST_LOGICAL_OR_EXPRESSION:
    case AST_ASSIGNMENT_EXPRESSION:
    case AST_CONDITIONAL_EXPRESSION:
    case AST_DECLARATION_SPECIFIERS:
    case AST_SPECIFIER_QUALIFIER_LIST:
    case AST_PARAMETER_DECLARATION:
    case AST_TYPE_NAME:
      delims[1] = AST_SPACE;
      goto case_join;
    case AST_DECLARATION:
    case AST_STRUCT_DECLARATION:
    case AST_EXPRESSION_STATEMENT:
      delims[0] = AST_NEWLINE;
      goto case_join;
    case AST_INIT_DECLARATOR_LIST:
    case AST_STRUCT_DECLARATOR_LIST:
    case AST_ENUMERATOR_LIST:
      delims[1] = AST_COMMA;
      goto case_join;
    case AST_INIT_DECLARATOR:
    case AST_ENUMERATOR:
      delims[0] = delims[1] = AST_SPACE;
      goto case_join;
    case AST_STRUCT_OR_UNION_SPECIFIER:
      delims[1] = delims[2] = AST_SPACE;
      delims[4] = AST_NEWLINE;
      goto case_list;
    case AST_STRUCT_DECLARATION_LIST:
    case AST_DECLARATION_LIST:
    case AST_STATEMENT_LIST:
      indent_diff = 1;
      goto case_join;
    case AST_STRUCT_DECLARATOR:
      delims[0] = delims[1] = delims[2] = AST_SPACE;
      goto case_list;
    case AST_ENUM_SPECIFIER:
      delims[1] = delims[2] = delims[4] = AST_SPACE;
      goto case_list;
    case AST_TYPE_QUALIFIER_LIST:
      delims[1] = AST_SPACE;
      delims[2] = sexp_is_nil(ast) ? AST_NULL : AST_SPACE;
      goto case_join;
    case AST_LABELED_STATEMENT:
      delims[1] = check_tag(ast, AST_CASE) ? AST_SPACE : AST_NULL;
      indent_diff = -1;
      goto case_list_newline;
    case AST_COMPOUND_STATEMENT:
      delims[0] = AST_SPACE;
      delims[3] = AST_NEWLINE;
      goto case_list;
    case AST_SELECTION_STATEMENT:
      delims[1] = delims[5] = AST_SPACE;
      goto case_list_newline;
    case AST_ITERATION_STATEMENT:
      switch (get_tag(sexp_car(ast))) {
      case AST_WHILE:
        delims[1] = AST_SPACE;
        break;
      case AST_DO:
        delims[2] = delims[3] = AST_SPACE;
        break;
      case AST_FOR:
        delims[1] = delims[4] = delims[6] = AST_SPACE;
        break;
      default:
        break;
      }
      goto case_list_newline;
    case AST_JUMP_STATEMENT:
      switch (get_tag(sexp_car(ast))) {
      case AST_GOTO:
      case AST_RETURN:
        delims[1] = AST_SPACE;
      default:
        goto case_list_newline;
      }
    case AST_FUNCTION_DEFINITION:
      delims[1] = AST_SPACE;
      goto case_list_newline;
    default:
      goto case_join;
    case_list_newline:
      delims[9] = AST_NEWLINE;
      goto case_list;
    case_list:
      for (pretty = sexp_nil(), i = 0; sexp_is_pair(ast);
           ast = sexp_cdr(ast), ++i) {
        assert(i < 9);
        pretty = pretty_snoc(pretty, sexp_car(ast), indent, delims[i]);
      }
      return pretty_prefix(pretty, indent + indent_diff, delims[9]);
    case_join:
      for (pretty = sexp_nil(), i = 0; sexp_is_pair(ast);
           ast = sexp_cdr(ast), i = 1) {
        pretty =
            pretty_snoc(pretty, sexp_car(ast), indent + indent_diff, delims[i]);
      }
      return pretty_suffix(pretty, delims[2]);
    }
  } else {
    return sexp_clone(ast);
  }
}
static void pretty_print_sexp(FILE *fp, Sexp *sexp) {
  if (sexp_is_pair(sexp)) {
    assert(sexp_is_list(sexp));
    pretty_print_sexp(fp, sexp_car(sexp));
    pretty_print_sexp(fp, sexp_cdr(sexp));
  } else {
    print_symbol(fp, sexp);
  }
}

void pretty_print(FILE *fp, Sexp *ast) {
  Sexp *pretty = pretty_convert(ast, 0);
  pretty_print_sexp(fp, pretty);
  print_newline(fp);
  sexp_delete(pretty);
}
