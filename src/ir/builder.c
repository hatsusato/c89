#include "builder.h"

#include "utility.h"

struct struct_Builder {
  int reg;
};

Builder *builder_new(void) {
  Builder *builder = UTILITY_MALLOC(Builder);
  builder->reg = 0;
  return builder;
}
void builder_delete(Builder *builder) {
  UTILITY_FREE(builder);
}
