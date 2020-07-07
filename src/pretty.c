#include "pretty.h"

#include "ast.h"
#include "print.h"
#include "utility.h"

static Sexp *pretty_convert(Sexp *, int);
static Bool pretty_check_tag(Sexp *ast, const char *tag) {
  return sexp_is_pair(ast) && sexp_eq(sexp_car(ast), tag);
}
static Sexp *pretty_indent(int indent, Sexp *ast) {
  for (; 0 < indent; --indent) {
    ast = sexp_cons(sexp_symbol("  "), ast);
  }
  return sexp_cons(sexp_symbol("\n"), ast);
}
static Sexp *pretty_prefix(Sexp *ast, const char *symbol) {
  if (symbol) {
    ast = sexp_cons(sexp_symbol(symbol), ast);
  }
  return ast;
}
static Sexp *pretty_suffix(Sexp *ast, const char *symbol) {
  if (symbol) {
    ast = sexp_snoc(ast, sexp_symbol(symbol));
  }
  return ast;
}
static Sexp *pretty_snoc_symbol(Sexp *pretty, int indent, const char *symbol) {
  if (utility_str_eq(symbol, "\n")) {
    return sexp_snoc(pretty, pretty_indent(indent, sexp_nil()));
  } else if (symbol) {
    return sexp_snoc(pretty, sexp_symbol(symbol));
  }
  return pretty;
}
static Sexp *pretty_snoc(Sexp *pretty, Sexp *ast, int indent,
                         const char *prefix) {
  if (sexp_is_pair(ast)) {
    Sexp *car = sexp_car(ast);
    if (!sexp_is_nil(car)) {
      pretty = pretty_snoc_symbol(pretty, indent, prefix);
      pretty = sexp_snoc(pretty, pretty_convert(car, indent));
    }
  } else {
    assert(0);
  }
  return pretty;
}
static Sexp *pretty_convert_join(Sexp *ast, int indent, const char *delims[]) {
  Sexp *pretty = sexp_nil();
  int i = 0;
  if (sexp_is_pair(ast)) {
    pretty = pretty_snoc(pretty, ast, indent, delims[i]);
    ast = sexp_cdr(ast);
    ++i;
  }
  for (; sexp_is_pair(ast); ast = sexp_cdr(ast), ++i) {
    pretty = pretty_snoc(pretty, ast, indent, delims[i]);
  }
  return pretty;
}
static Sexp *pretty_convert_list(Sexp *ast, int indent, const char *delim) {
  Sexp *pretty = sexp_nil();
  if (sexp_is_pair(ast)) {
    pretty = pretty_snoc(pretty, ast, indent, nil);
    ast = sexp_cdr(ast);
  }
  for (; sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    pretty = pretty_snoc(pretty, ast, indent, delim);
  }
  return pretty;
}
static Sexp *pretty_convert(Sexp *ast, int indent) {
  if (sexp_is_pair(ast)) {
    const char *delims[10] = {0};
    int tag = ast_to_int(sexp_get(sexp_car(ast)));
    ast = sexp_cdr(ast);
    switch (tag) {
    case AST_ARGUMENT_EXPRESSION_LIST:
    case AST_EXPRESSION:
    case AST_PARAMETER_LIST:
    case AST_IDENTIFIER_LIST:
    case AST_INITIALIZER_LIST:
      return pretty_convert_list(ast, indent, ", ");
    case AST_UNARY_EXPRESSION:
      if (pretty_check_tag(ast, "sizeof") &&
          !(pretty_check_tag(sexp_cdr(ast), "primary-expression"))) {
        delims[1] = " ";
      }
      return pretty_convert_join(ast, indent, delims);
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
      return pretty_convert_list(ast, indent, " ");
    case AST_DECLARATION:
    case AST_STRUCT_DECLARATION:
      ast = pretty_convert_list(ast, indent, nil);
      return pretty_indent(indent, ast);
    case AST_INIT_DECLARATOR_LIST:
    case AST_STRUCT_DECLARATOR_LIST:
    case AST_ENUMERATOR_LIST:
      return pretty_convert_list(ast, indent, ",");
    case AST_INIT_DECLARATOR:
    case AST_ENUMERATOR:
      ast = pretty_convert_list(ast, indent, " ");
      return pretty_prefix(ast, " ");
    case AST_STRUCT_OR_UNION_SPECIFIER:
      delims[1] = delims[2] = " ";
      delims[4] = "\n";
      return pretty_convert_join(ast, indent, delims);
    case AST_STRUCT_DECLARATION_LIST:
      return pretty_convert_list(ast, indent + 1, nil);
    case AST_STRUCT_DECLARATOR:
      delims[0] = delims[1] = delims[2] = " ";
      return pretty_convert_join(ast, indent, delims);
    case AST_ENUM_SPECIFIER:
      delims[1] = delims[2] = delims[4] = " ";
      return pretty_convert_join(ast, indent, delims);
    case AST_TYPE_QUALIFIER_LIST:
      ast = pretty_convert_list(ast, indent, " ");
      return pretty_suffix(ast, sexp_is_nil(ast) ? nil : " ");
    case AST_LABELED_STATEMENT:
      delims[1] = pretty_check_tag(ast, "case") ? " " : nil;
      ast = pretty_convert_join(ast, indent, delims);
      indent = pretty_check_tag(sexp_car(ast), "identifier") ? 0 : indent - 1;
      return pretty_indent(indent, ast);
    case AST_COMPOUND_STATEMENT:
      delims[0] = " ";
      delims[3] = "\n";
      return pretty_convert_join(ast, indent, delims);
    case AST_DECLARATION_LIST:
    case AST_STATEMENT_LIST:
      return pretty_convert_list(ast, indent + 1, nil);
    case AST_EXPRESSION_STATEMENT:
      ast = pretty_convert_list(ast, indent, nil);
      return pretty_indent(indent, ast);
    case AST_SELECTION_STATEMENT:
      delims[1] = delims[5] = " ";
      ast = pretty_convert_join(ast, indent, delims);
      return pretty_indent(indent, ast);
    case AST_ITERATION_STATEMENT:
      if (pretty_check_tag(ast, "while")) {
        delims[1] = " ";
      } else if (pretty_check_tag(ast, "do")) {
        delims[2] = delims[3] = " ";
      } else if (pretty_check_tag(ast, "for")) {
        delims[1] = delims[4] = delims[6] = " ";
      }
      ast = pretty_convert_join(ast, indent, delims);
      return pretty_indent(indent, ast);
    case AST_JUMP_STATEMENT:
      if (pretty_check_tag(ast, "goto") || pretty_check_tag(ast, "return")) {
        delims[1] = " ";
      }
      ast = pretty_convert_join(ast, indent, delims);
      return pretty_indent(indent, ast);
    case AST_TRANSLATION_UNIT:
      ast = pretty_convert_list(ast, indent, nil);
      return pretty_suffix(ast, "\n");
    case AST_FUNCTION_DEFINITION:
      delims[1] = " ";
      ast = pretty_convert_join(ast, indent, delims);
      return pretty_indent(indent, ast);
    default:
      return pretty_convert_list(ast, indent, nil);
    }
  } else {
    const char *symbol = sexp_get(ast);
    return symbol ? sexp_symbol(symbol) : sexp_nil();
  }
}
static void pretty_print_sexp(Sexp *sexp) {
  if (sexp_is_pair(sexp)) {
    assert(sexp_is_list(sexp));
    pretty_print_sexp(sexp_car(sexp));
    pretty_print_sexp(sexp_cdr(sexp));
  } else {
    print_symbol(stdout, sexp);
  }
}

void pretty_print(Sexp *ast) {
  Sexp *pretty = pretty_convert(ast, 0);
  pretty_print_sexp(pretty);
  sexp_delete(pretty);
}
