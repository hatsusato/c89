#include "pretty.h"

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
static Sexp *pretty_convert_join(Sexp *ast, int indent, const char *prefix,
                                 const char *delims[], const char *suffix) {
  Sexp *pretty = sexp_nil();
  int i = 0;
  pretty = pretty_snoc_symbol(pretty, indent, prefix);
  if (sexp_is_pair(ast)) {
    pretty = pretty_snoc(pretty, ast, indent, delims[i]);
    ast = sexp_cdr(ast);
    ++i;
  }
  for (; sexp_is_pair(ast); ast = sexp_cdr(ast), ++i) {
    pretty = pretty_snoc(pretty, ast, indent, delims[i]);
  }
  pretty = pretty_snoc_symbol(pretty, indent, suffix);
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
static Bool pretty_check_sizeof(Sexp *ast) {
  if (2 == sexp_length(ast)) {
    Sexp *first = sexp_at(ast, 0), *second = sexp_at(ast, 1);
    if (sexp_eq(first, "sizeof")) {
      return !(sexp_is_pair(second) &&
               sexp_eq(sexp_car(second), "primary-expression"));
    }
  }
  return false;
}
static Bool pretty_check_binary_expression(const char *tag) {
  return (utility_str_eq(tag, "multiplicative-expression") ||
          utility_str_eq(tag, "additive-expression") ||
          utility_str_eq(tag, "shift-expression") ||
          utility_str_eq(tag, "relational-expression") ||
          utility_str_eq(tag, "equality-expression") ||
          utility_str_eq(tag, "and-expression") ||
          utility_str_eq(tag, "exclusive-or-expression") ||
          utility_str_eq(tag, "inclusive-or-expression") ||
          utility_str_eq(tag, "logical-and-expression") ||
          utility_str_eq(tag, "logical-or-expression") ||
          utility_str_eq(tag, "assignment-expression"));
}
static Sexp *pretty_convert(Sexp *ast, int indent) {
  if (sexp_is_pair(ast)) {
    const char *delims[10] = {0};
    const char *tag = sexp_get(sexp_car(ast));
    ast = sexp_cdr(ast);
    if (utility_str_eq(tag, "argument-expression-list") ||
        utility_str_eq(tag, "expression") ||
        utility_str_eq(tag, "parameter-list") ||
        utility_str_eq(tag, "identifier-list") ||
        utility_str_eq(tag, "initializer-list")) {
      return pretty_convert_list(ast, indent, ", ");
    } else if (utility_str_eq(tag, "unary-expression")) {
      const char *delim = pretty_check_sizeof(ast) ? " " : nil;
      return pretty_convert_list(ast, indent, delim);
    } else if (pretty_check_binary_expression(tag) ||
               utility_str_eq(tag, "conditional-expression") ||
               utility_str_eq(tag, "declaration-specifiers") ||
               utility_str_eq(tag, "specifier-qualifier-list") ||
               utility_str_eq(tag, "parameter-declaration") ||
               utility_str_eq(tag, "type-name")) {
      return pretty_convert_list(ast, indent, " ");
    } else if (utility_str_eq(tag, "declaration") ||
               utility_str_eq(tag, "struct-declaration")) {
      ast = pretty_convert_list(ast, indent, nil);
      return pretty_indent(indent, ast);
    } else if (utility_str_eq(tag, "init-declarator-list") ||
               utility_str_eq(tag, "struct-declarator-list") ||
               utility_str_eq(tag, "enumerator-list")) {
      return pretty_convert_list(ast, indent, ",");
    } else if (utility_str_eq(tag, "init-declarator") ||
               utility_str_eq(tag, "enumerator")) {
      ast = pretty_convert_list(ast, indent, " ");
      return pretty_prefix(ast, " ");
    } else if (utility_str_eq(tag, "struct-or-union-specifier")) {
      delims[1] = delims[2] = " ";
      delims[4] = "\n";
      return pretty_convert_join(ast, indent, nil, delims, nil);
    } else if (utility_str_eq(tag, "struct-declaration-list")) {
      return pretty_convert_list(ast, indent + 1, nil);
    } else if (utility_str_eq(tag, "struct-declarator")) {
      delims[0] = delims[1] = delims[2] = " ";
      return pretty_convert_join(ast, indent, nil, delims, nil);
    } else if (utility_str_eq(tag, "enum-specifier")) {
      delims[1] = delims[2] = delims[4] = " ";
      return pretty_convert_join(ast, indent, nil, delims, nil);
    } else if (utility_str_eq(tag, "type-qualifier-list")) {
      ast = pretty_convert_list(ast, indent, " ");
      return pretty_suffix(ast, sexp_is_nil(ast) ? nil : " ");
    } else if (utility_str_eq(tag, "labeled-statement")) {
      delims[1] = pretty_check_tag(ast, "case") ? " " : nil;
      ast = pretty_convert_join(ast, indent, nil, delims, nil);
      indent = pretty_check_tag(sexp_car(ast), "identifier") ? 0 : indent - 1;
      return pretty_indent(indent, ast);
    } else if (utility_str_eq(tag, "compound-statement")) {
      delims[0] = " ";
      delims[3] = "\n";
      return pretty_convert_join(ast, indent, nil, delims, nil);
    } else if (utility_str_eq(tag, "declaration-list") ||
               utility_str_eq(tag, "statement-list")) {
      return pretty_convert_list(ast, indent + 1, nil);
    } else if (utility_str_eq(tag, "expression-statement")) {
      ast = pretty_convert_list(ast, indent, nil);
      return pretty_indent(indent, ast);
    } else if (utility_str_eq(tag, "selection-statement")) {
      delims[1] = delims[5] = " ";
      ast = pretty_convert_join(ast, indent, nil, delims, nil);
      return pretty_indent(indent, ast);
    } else if (utility_str_eq(tag, "iteration-statement")) {
      if (pretty_check_tag(ast, "while")) {
        delims[1] = " ";
      } else if (pretty_check_tag(ast, "do")) {
        delims[2] = delims[3] = " ";
      } else if (pretty_check_tag(ast, "for")) {
        delims[1] = delims[4] = delims[6] = " ";
      }
      ast = pretty_convert_join(ast, indent, nil, delims, nil);
      return pretty_indent(indent, ast);
    } else if (utility_str_eq(tag, "jump-statement")) {
      if (pretty_check_tag(ast, "goto") || pretty_check_tag(ast, "return")) {
        delims[1] = " ";
      }
      ast = pretty_convert_join(ast, indent, nil, delims, nil);
      return pretty_indent(indent, ast);
    } else if (utility_str_eq(tag, "translation-unit")) {
      ast = pretty_convert_list(ast, indent, nil);
      return pretty_suffix(ast, "\n");
    } else if (utility_str_eq(tag, "function-definition")) {
      delims[1] = " ";
      ast = pretty_convert_join(ast, indent, nil, delims, nil);
      return pretty_indent(indent, ast);
    } else {
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
