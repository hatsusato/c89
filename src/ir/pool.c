#include "ir/pool.h"

#include "ir/block.h"
#include "ir/constant.h"
#include "ir/function.h"
#include "ir/instruction.h"
#include "types.h"
#include "utility.h"
#include "vector.h"

struct struct_Pool {
  Vector *function, *block, *instruction, *constant;
};

static void pool_function_delete(ElemType func) {
  function_delete(func);
}
static void pool_block_delete(ElemType block) {
  block_delete(block);
}
static void pool_instruction_delete(ElemType instr) {
  instruction_delete(instr);
}
static void pool_constant_delete(ElemType constant) {
  constant_delete(constant);
}

Pool *pool_new(void) {
  Pool *pool = UTILITY_MALLOC(Pool);
  pool->function = vector_new(pool_function_delete);
  pool->block = vector_new(pool_block_delete);
  pool->instruction = vector_new(pool_instruction_delete);
  pool->constant = vector_new(pool_constant_delete);
  return pool;
}
void pool_delete(Pool *pool) {
  vector_delete(pool->constant);
  vector_delete(pool->instruction);
  vector_delete(pool->block);
  vector_delete(pool->function);
  UTILITY_FREE(pool);
}
