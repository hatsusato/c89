#include "pretty.h"

#include <string.h>

#include "print.h"
#include "utility.h"

static Sexp *pretty_convert(Sexp *ast);
static Sexp *pretty_snoc_symbol(Sexp *pretty, const char *symbol) {
  if (symbol) {
    pretty = sexp_snoc(pretty, sexp_symbol(symbol));
  }
  return pretty;
}
static Sexp *pretty_snoc(Sexp *pretty, Sexp *ast, const char *prefix) {
  if (sexp_is_pair(ast)) {
    Sexp *car = sexp_car(ast);
    if (!sexp_is_nil(car)) {
      pretty = pretty_snoc_symbol(pretty, prefix);
      pretty = sexp_snoc(pretty, pretty_convert(car));
    }
  } else {
    assert(0);
  }
  return pretty;
}
static Sexp *pretty_convert_join(Sexp *ast, const char *prefix,
                                 const char *delims[], const char *suffix) {
  Sexp *pretty = sexp_nil();
  int i = 0;
  pretty = pretty_snoc_symbol(pretty, prefix);
  if (sexp_is_pair(ast)) {
    pretty = pretty_snoc(pretty, ast, nil);
    ast = sexp_cdr(ast);
  }
  for (; sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    pretty = pretty_snoc(pretty, ast, delims[i++]);
  }
  pretty = pretty_snoc_symbol(pretty, suffix);
  return pretty;
}
static Sexp *pretty_convert_list(Sexp *ast, const char *prefix,
                                 const char *delim, const char *suffix) {
  Sexp *pretty = sexp_nil();
  pretty = pretty_snoc_symbol(pretty, prefix);
  if (sexp_is_pair(ast)) {
    pretty = pretty_snoc(pretty, ast, nil);
    ast = sexp_cdr(ast);
  }
  for (; sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    pretty = pretty_snoc(pretty, ast, delim);
  }
  pretty = pretty_snoc_symbol(pretty, suffix);
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
static Sexp *pretty_convert(Sexp *ast) {
  if (sexp_is_pair(ast)) {
    const char *delims[10] = {0};
    const char *tag = sexp_get(sexp_car(ast));
    ast = sexp_cdr(ast);
    if (utility_str_eq(tag, "argument-expression-list") ||
        utility_str_eq(tag, "expression") ||
        utility_str_eq(tag, "parameter-list") ||
        utility_str_eq(tag, "identifier-list") ||
        utility_str_eq(tag, "initializer-list")) {
      return pretty_convert_list(ast, nil, ", ", nil);
    } else if (utility_str_eq(tag, "unary-expression")) {
      const char *delim = pretty_check_sizeof(ast) ? " " : nil;
      return pretty_convert_list(ast, nil, delim, nil);
    } else if (pretty_check_binary_expression(tag) ||
               utility_str_eq(tag, "conditional-expression") ||
               utility_str_eq(tag, "declaration-specifiers") ||
               utility_str_eq(tag, "specifier-qualifier-list") ||
               utility_str_eq(tag, "parameter-declaration") ||
               utility_str_eq(tag, "type-name")) {
      return pretty_convert_list(ast, nil, " ", nil);
    } else if (utility_str_eq(tag, "declaration") ||
               utility_str_eq(tag, "struct-declaration")) {
      return pretty_convert_list(ast, nil, nil, "\n");
    } else if (utility_str_eq(tag, "init-declarator-list") ||
               utility_str_eq(tag, "struct-declarator-list") ||
               utility_str_eq(tag, "enumerator-list")) {
      return pretty_convert_list(ast, nil, ",", nil);
    } else if (utility_str_eq(tag, "init-declarator") ||
               utility_str_eq(tag, "enumerator")) {
      return pretty_convert_list(ast, " ", " ", nil);
    } else if (utility_str_eq(tag, "struct-or-union-specifier")) {
      delims[0] = delims[1] = " ";
      delims[2] = "\n";
      return pretty_convert_join(ast, nil, delims, nil);
    } else if (utility_str_eq(tag, "struct-declarator")) {
      const char *prefix = sexp_is_nil(sexp_car(ast)) ? nil : " ";
      const char *delim = 3 == sexp_length(ast) ? " " : nil;
      return pretty_convert_list(ast, prefix, delim, nil);
    } else if (utility_str_eq(tag, "enum-specifier")) {
      delims[0] = delims[1] = delims[3] = " ";
      return pretty_convert_join(ast, nil, delims, nil);
    } else if (utility_str_eq(tag, "type-qualifier-list")) {
      const char *suffix = sexp_is_nil(ast) ? nil : " ";
      return pretty_convert_list(ast, nil, " ", suffix);
    } else {
      return pretty_convert_list(ast, nil, nil, nil);
    }
  } else {
    const char *symbol = sexp_get(ast);
    return symbol ? sexp_symbol(symbol) : sexp_nil();
  }
}

static Bool pretty_equal(const char *lhs, const char *rhs) {
  return 0 == strcmp(lhs, rhs);
}
static Sexp *pretty_sexp_push_symbol(Sexp *pretty, const char *symbol) {
  return sexp_snoc(pretty, sexp_symbol(symbol));
}
static Sexp *pretty_sexp_push(Sexp *pretty, Sexp *ast) {
  assert(sexp_is_pair(ast));
  return sexp_snoc(pretty, pretty_sexp(sexp_car(ast)));
}
static Sexp *pretty_sexp_skip(Sexp *ast) {
  assert(sexp_is_pair(ast));
  return sexp_cdr(ast);
}
static Sexp *pretty_sexp_with_space(Sexp *pretty, Sexp *ast) {
  assert(sexp_is_pair(ast));
  if (!sexp_is_nil(sexp_car(ast))) {
    pretty = pretty_sexp_push(pretty, ast);
    pretty = pretty_sexp_push_symbol(pretty, " ");
  }
  return pretty;
}
static Sexp *pretty_sexp_list(Sexp *pretty, Sexp *ast, const char *between) {
  assert(sexp_is_list(ast));
  if (sexp_is_pair(ast)) {
    pretty = pretty_sexp_push(pretty, ast);
    ast = pretty_sexp_skip(ast);
    while (sexp_is_pair(ast)) {
      if (between) {
        pretty = pretty_sexp_push_symbol(pretty, between);
      }
      pretty = pretty_sexp_push(pretty, ast);
      ast = pretty_sexp_skip(ast);
    }
  }
  return pretty;
}

Sexp *pretty_sexp(Sexp *ast) {
  Sexp *pretty = sexp_nil();
  if (sexp_is_pair(ast)) {
    const char *tag = sexp_get(sexp_car(ast));
    ast = pretty_sexp_skip(ast);
    if (pretty_equal(tag, "argument-expression-list") ||
        pretty_equal(tag, "expression") ||
        pretty_equal(tag, "enumerator-list") ||
        pretty_equal(tag, "parameter-list") ||
        pretty_equal(tag, "identifier-list")) {
      pretty = pretty_sexp_list(pretty, ast, ", ");
    } else if (pretty_equal(tag, "multiplicative-expression") ||
               pretty_equal(tag, "additive-expression") ||
               pretty_equal(tag, "shift-expression") ||
               pretty_equal(tag, "relational-expression") ||
               pretty_equal(tag, "equality-expression") ||
               pretty_equal(tag, "and-expression") ||
               pretty_equal(tag, "exclusive-or-expression") ||
               pretty_equal(tag, "inclusive-or-expression") ||
               pretty_equal(tag, "logical-and-expression") ||
               pretty_equal(tag, "logical-or-expression") ||
               pretty_equal(tag, "conditional-expression") ||
               pretty_equal(tag, "assignment-expression") ||
               pretty_equal(tag, "declaration-specifiers") ||
               pretty_equal(tag, "specifier-qualifier-list") ||
               pretty_equal(tag, "enumerator")) {
      pretty = pretty_sexp_list(pretty, ast, " ");
    } else if (pretty_equal(tag, "declaration") ||
               pretty_equal(tag, "struct-declaration")) {
      pretty = pretty_sexp_list(pretty, ast, nil);
      pretty = pretty_sexp_push_symbol(pretty, "\n");
    } else if (pretty_equal(tag, "init-declarator-list") ||
               pretty_equal(tag, "struct-declarator-list")) {
      pretty = pretty_sexp_list(pretty, ast, ",");
    } else if (pretty_equal(tag, "init-declarator")) {
      pretty = pretty_sexp_push_symbol(pretty, " ");
      pretty = pretty_sexp_list(pretty, ast, " ");
    } else if (pretty_equal(tag, "struct-or-union-specifier")) {
      pretty = pretty_sexp_with_space(pretty, ast);
      ast = pretty_sexp_skip(ast);
      pretty = pretty_sexp_with_space(pretty, ast);
      ast = pretty_sexp_skip(ast);
      if (!sexp_is_nil(sexp_car(ast))) {
        pretty = pretty_sexp_push(pretty, ast);
        ast = pretty_sexp_skip(ast);
        pretty = pretty_sexp_push_symbol(pretty, "\n");
        pretty = pretty_sexp_push(pretty, ast);
        ast = pretty_sexp_skip(ast);
        pretty = pretty_sexp_push(pretty, ast);
        ast = pretty_sexp_skip(ast);
      }
    } else if (pretty_equal(tag, "struct-declarator")) {
      pretty = pretty_sexp_push_symbol(pretty, " ");
      if (1 == sexp_length(ast)) {
        pretty = pretty_sexp_push(pretty, ast);
        ast = pretty_sexp_skip(ast);
      } else {
        pretty = pretty_sexp_with_space(pretty, ast);
        ast = pretty_sexp_skip(ast);
        pretty = pretty_sexp_with_space(pretty, ast);
        ast = pretty_sexp_skip(ast);
        pretty = pretty_sexp_push(pretty, ast);
        ast = pretty_sexp_skip(ast);
      }
    } else if (pretty_equal(tag, "enum-specifier")) {
      pretty = pretty_sexp_with_space(pretty, ast);
      ast = pretty_sexp_skip(ast);
      pretty = pretty_sexp_with_space(pretty, ast);
      ast = pretty_sexp_skip(ast);
      pretty = pretty_sexp_list(pretty, ast, " ");
    } else if (pretty_equal(tag, "type-qualifier-list")) {
      pretty = pretty_sexp_list(pretty, ast, " ");
      if (!sexp_is_nil(ast)) {
        pretty = pretty_sexp_push_symbol(pretty, " ");
      }
    } else if (pretty_equal(tag, "parameter-declaration")) {
      pretty = pretty_sexp_push(pretty, ast);
      ast = pretty_sexp_skip(ast);
      if (!sexp_is_nil(ast)) {
        pretty = pretty_sexp_push_symbol(pretty, " ");
        pretty = pretty_sexp_push(pretty, ast);
        ast = pretty_sexp_skip(ast);
      }
    } else {
      pretty = pretty_sexp_list(pretty, ast, nil);
    }
  } else if (!sexp_is_nil(ast)) {
    pretty = sexp_symbol(sexp_get(ast));
  }
  return pretty;
}
void pretty_print_sexp(Sexp *sexp) {
  if (sexp_is_pair(sexp)) {
    assert(sexp_is_list(sexp));
    pretty_print_sexp(sexp_car(sexp));
    pretty_print_sexp(sexp_cdr(sexp));
  } else {
    print_symbol(stdout, sexp);
  }
}
void pretty_print(Sexp *ast) {
  Sexp *pretty = pretty_convert(ast);
  pretty_print_sexp(pretty);
  sexp_delete(pretty);
}
