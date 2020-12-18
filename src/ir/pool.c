#include "ir/pool.h"

#include "ir/block.h"
#include "ir/function.h"
#include "ir/value.h"
#include "types.h"
#include "utility.h"
#include "vector.h"

struct struct_Pool {
  Vector *pool, *function, *block;
};

static void pool_function_delete(ElemType func) {
  function_delete(func);
}
static void pool_block_delete(ElemType block) {
  block_delete(block);
}

Pool *pool_new(void) {
  Pool *pool = UTILITY_MALLOC(Pool);
  pool->pool = vector_new((Destructor)value_delete);
  pool->function = vector_new(pool_function_delete);
  pool->block = vector_new(pool_block_delete);
  return pool;
}
void pool_delete(Pool *pool) {
  vector_delete(pool->block);
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
void pool_insert_block(Pool *pool, Block *block) {
  vector_push(pool->block, block);
}
