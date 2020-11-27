#include "ir/register.h"

#include "utility.h"
#include "vector.h"

struct struct_Register {
  int id;
};

static void register_delete(Register *reg) {
  UTILITY_FREE(reg);
}

Vector *register_pool_new(void) {
  return vector_new((Destructor)register_delete);
}
void register_pool_delete(Vector *pool) {
  vector_delete(pool);
}
