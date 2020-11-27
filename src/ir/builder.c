#include "builder.h"

#include "sexp.h"
#include "utility.h"

struct struct_Builder {
  int reg, last;
};

static AstTag get_tag(Sexp *ast) {
  assert(sexp_is_pair(ast));
  ast = sexp_car(ast);
  assert(sexp_is_number(ast));
  return sexp_get_number(ast);
}

Builder *builder_new(void) {
  Builder *builder = UTILITY_MALLOC(Builder);
  builder->reg = builder->last = 0;
  return builder;
}
void builder_delete(Builder *builder) {
  UTILITY_FREE(builder);
}
