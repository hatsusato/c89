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
static Sexp *pretty_convert_join(Sexp *ast, const char *delims[]) {
  Sexp *pretty = sexp_nil();
  int i = 0;
  pretty = pretty_snoc_symbol(pretty, delims[i++]);
  if (sexp_is_pair(ast)) {
    pretty = pretty_snoc(pretty, ast, nil);
    ast = sexp_cdr(ast);
  }
  for (; sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    pretty = pretty_snoc(pretty, ast, delims[i++]);
  }
  pretty = pretty_snoc_symbol(pretty, delims[i++]);
  return pretty;
}
static Sexp *pretty_convert_list(Sexp *ast, const char *delims[]) {
  Sexp *pretty = sexp_nil();
  pretty = pretty_snoc_symbol(pretty, delims[0]);
  if (sexp_is_pair(ast)) {
    pretty = pretty_snoc(pretty, ast, nil);
    ast = sexp_cdr(ast);
  }
  for (; sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    pretty = pretty_snoc(pretty, ast, delims[1]);
  }
  pretty = pretty_snoc_symbol(pretty, delims[2]);
  return pretty;
}
static Sexp *pretty_convert(Sexp *ast) {
  if (sexp_is_pair(ast)) {
    const char *delims[3] = {0};
    const char *tag = sexp_get(sexp_car(ast));
    ast = sexp_cdr(ast);
    return pretty_convert_list(ast, delims);
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
