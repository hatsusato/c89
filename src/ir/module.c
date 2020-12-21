#include "ir/module.h"

#include <stdio.h>

#include "ir/block.h"
#include "ir/constant.h"
#include "ir/function.h"
#include "ir/instruction.h"
#include "ir/value.h"
#include "utility.h"
#include "vector.h"

struct struct_Module {
  Vector *pool, *vec;
};

static void module_value_delete(ElemType value) {
  switch (value_kind(value)) {
  case VALUE_FUNCTION:
    function_delete(value);
    break;
  case VALUE_BLOCK:
    block_delete(value);
    break;
  case VALUE_INSTRUCTION:
    instruction_delete(value);
    break;
  case VALUE_CONSTANT:
    constant_delete(value);
    break;
  default:
    assert(0);
    break;
  }
}

Module *module_new(void) {
  Module *module = UTILITY_MALLOC(Module);
  module->pool = vector_new(module_value_delete);
  module->vec = vector_new(NULL);
  return module;
}
void module_delete(Module *module) {
  vector_delete(module->vec);
  vector_delete(module->pool);
  UTILITY_FREE(module);
}
Function *module_new_function(Module *module) {
  Function *func = function_new();
  vector_push(module->pool, func);
  vector_push(module->vec, func);
  return func;
}
Block *module_new_block(Module *module) {
  Block *block = block_new();
  vector_push(module->pool, block);
  return block;
}
Instruction *module_new_instruction(Module *module) {
  Instruction *instr = instruction_new();
  vector_push(module->pool, instr);
  return instr;
}
Constant *module_new_constant(Module *module) {
  Constant *constant = constant_new();
  vector_push(module->pool, constant);
  return constant;
}
void module_pretty(Module *module) {
  ElemType *begin = vector_begin(module->vec);
  ElemType *end = vector_end(module->vec);
  puts("target triple = \"x86_64-unknown-linux-gnu\"");
  while (begin < end) {
    puts("");
    function_pretty(*begin++);
  }
}
