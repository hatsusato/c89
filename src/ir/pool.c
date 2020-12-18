#include "ir/pool.h"

#include "ir/function.h"
#include "ir/value.h"
#include "types.h"
#include "utility.h"
#include "vector.h"

struct struct_Pool {
  Vector *pool, *function;
};

static void pool_function_delete(ElemType func) {
  function_delete(func);
}

Pool *pool_new(void) {
  Pool *pool = UTILITY_MALLOC(Pool);
  pool->pool = vector_new((Destructor)value_delete);
  pool->function = vector_new(pool_function_delete);
  return pool;
}
void pool_delete(Pool *pool) {
  vector_delete(pool->function);
  vector_delete(pool->pool);
  UTILITY_FREE(pool);
}
void pool_insert(Pool *pool, Value *value) {
  vector_push(pool->pool, value);
}
void pool_insert_function(Pool *pool, Function *func) {
  vector_push(pool->function, func);
}
