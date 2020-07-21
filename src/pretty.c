#include "pretty.h"

#include "ast.h"
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
  if (AST_NULL == prefix) {
    return ast;
  } else if (AST_NEWLINE == prefix) {
    for (; 0 < indent; --indent) {
      ast = sexp_cons(sexp_number(AST_INDENT), ast);
    }
  }
  return sexp_cons(sexp_number(prefix), ast);
}
static Sexp *pretty_snoc(Sexp *pretty, Sexp *ast, int indent, AstTag prefix) {
  ast = sexp_car(ast);
  if (!sexp_is_nil(ast)) {
    ast = pretty_convert(ast, indent);
    ast = sexp_cons(ast, sexp_nil());
    ast = pretty_prefix(ast, indent, prefix);
    pretty = sexp_snoc(pretty, ast);
  }
  return pretty;
}
static Sexp *pretty_convert_list(Sexp *ast, int indent, AstTag delims[]) {
  Sexp *pretty = sexp_nil();
  int i = 0;
  for (; sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    pretty = pretty_snoc(pretty, ast, indent, delims[i++]);
  }
  return pretty;
}
static Sexp *pretty_convert_join(Sexp *ast, int indent, AstTag delim) {
  Sexp *pretty = sexp_nil();
  AstTag prefix = 0;
  for (; sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    pretty = pretty_snoc(pretty, ast, indent, prefix);
    prefix = delim;
  }
  return pretty;
}
static Sexp *pretty_convert(Sexp *ast, int indent) {
  AstTag delims[10];
  int i;
  for (i = 0; i < 10; ++i) {
    delims[i] = AST_NULL;
  }
  if (sexp_is_pair(ast)) {
    int tag = sexp_get_number(sexp_car(ast));
    ast = sexp_cdr(ast);
    switch (tag) {
    case AST_ARGUMENT_EXPRESSION_LIST:
    case AST_EXPRESSION:
    case AST_PARAMETER_LIST:
    case AST_IDENTIFIER_LIST:
    case AST_INITIALIZER_LIST:
      return pretty_convert_join(ast, indent, AST_SEPARATOR);
    case AST_UNARY_EXPRESSION:
      if (2 == sexp_length(ast) && check_tag(ast, AST_SIZEOF) &&
          !check_tag(sexp_cdr(ast), AST_PRIMARY_EXPRESSION)) {
        delims[1] = AST_SPACE;
      }
      return pretty_convert_list(ast, indent, delims);
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
      return pretty_convert_join(ast, indent, AST_SPACE);
    case AST_DECLARATION:
    case AST_STRUCT_DECLARATION:
    case AST_EXPRESSION_STATEMENT:
      ast = pretty_convert_join(ast, indent, AST_NULL);
      return pretty_prefix(ast, indent, AST_NEWLINE);
    case AST_INIT_DECLARATOR_LIST:
    case AST_STRUCT_DECLARATOR_LIST:
    case AST_ENUMERATOR_LIST:
      return pretty_convert_join(ast, indent, AST_COMMA);
    case AST_INIT_DECLARATOR:
    case AST_ENUMERATOR:
      ast = pretty_convert_join(ast, indent, AST_SPACE);
      return pretty_prefix(ast, indent, AST_SPACE);
    case AST_STRUCT_OR_UNION_SPECIFIER:
      delims[1] = delims[2] = AST_SPACE;
      delims[4] = AST_NEWLINE;
      return pretty_convert_list(ast, indent, delims);
    case AST_STRUCT_DECLARATION_LIST:
    case AST_DECLARATION_LIST:
    case AST_STATEMENT_LIST:
      return pretty_convert_join(ast, indent + 1, AST_NULL);
    case AST_STRUCT_DECLARATOR:
      delims[0] = delims[1] = delims[2] = AST_SPACE;
      return pretty_convert_list(ast, indent, delims);
    case AST_ENUM_SPECIFIER:
      delims[1] = delims[2] = delims[4] = AST_SPACE;
      return pretty_convert_list(ast, indent, delims);
    case AST_TYPE_QUALIFIER_LIST:
      ast = pretty_convert_join(ast, indent, AST_SPACE);
      return sexp_is_nil(ast) ? ast : sexp_snoc(ast, sexp_number(AST_SPACE));
    case AST_LABELED_STATEMENT:
      delims[1] = check_tag(ast, AST_CASE) ? AST_SPACE : AST_NULL;
      ast = pretty_convert_list(ast, indent, delims);
      --indent;
      return pretty_prefix(ast, indent, AST_NEWLINE);
    case AST_COMPOUND_STATEMENT:
      delims[0] = AST_SPACE;
      delims[3] = AST_NEWLINE;
      return pretty_convert_list(ast, indent, delims);
    case AST_SELECTION_STATEMENT:
      delims[1] = delims[5] = AST_SPACE;
      ast = pretty_convert_list(ast, indent, delims);
      return pretty_prefix(ast, indent, AST_NEWLINE);
    case AST_ITERATION_STATEMENT:
      if (check_tag(ast, AST_WHILE)) {
        delims[1] = AST_SPACE;
      } else if (check_tag(ast, AST_DO)) {
        delims[2] = delims[3] = AST_SPACE;
      } else if (check_tag(ast, AST_FOR)) {
        delims[1] = delims[4] = delims[6] = AST_SPACE;
      }
      ast = pretty_convert_list(ast, indent, delims);
      return pretty_prefix(ast, indent, AST_NEWLINE);
    case AST_JUMP_STATEMENT:
      if (check_tag(ast, AST_GOTO) || check_tag(ast, AST_RETURN)) {
        delims[1] = AST_SPACE;
      }
      ast = pretty_convert_list(ast, indent, delims);
      return pretty_prefix(ast, indent, AST_NEWLINE);
    case AST_FUNCTION_DEFINITION:
      delims[1] = AST_SPACE;
      ast = pretty_convert_list(ast, indent, delims);
      return pretty_prefix(ast, indent, AST_NEWLINE);
    default:
      return pretty_convert_join(ast, indent, AST_NULL);
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
