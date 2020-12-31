#include "module.h"

#include <stdio.h>

#include "builder/block.h"
#include "builder/builder.h"
#include "builder/constant.h"
#include "builder/function.h"
#include "builder/global.h"
#include "builder/instruction.h"
#include "builder/type.h"
#include "builder/value.h"
#include "utility.h"
#include "vector.h"

struct struct_Module {
  ValuePool *value;
  TypePool *type;
  Vector *prior, *global, *func;
};

static void module_pretty_prior(Module *module) {
  ElemType *begin = vector_begin(module->prior);
  ElemType *end = vector_end(module->prior);
  while (begin < end) {
    Global *global = *begin++;
    global_pretty(global);
  }
}
static void module_pretty_global(Module *module) {
  ElemType *begin = vector_begin(module->global);
  ElemType *end = vector_end(module->global);
  while (begin < end) {
    Global *global = *begin++;
    if (!global_is_prior(global)) {
      global_pretty(global);
    }
  }
}
static void module_pretty_function(Module *module) {
  ElemType *begin = vector_begin(module->func);
  ElemType *end = vector_end(module->func);
  while (begin < end) {
    printf("\n");
    function_pretty(*begin++);
  }
}

Module *module_new(void) {
  Module *module = UTILITY_MALLOC(Module);
  module->value = value_pool_new();
  module->type = type_pool_new();
  module->prior = vector_new(NULL);
  module->global = vector_new(NULL);
  module->func = vector_new(NULL);
  return module;
}
void module_delete(Module *module) {
  vector_delete(module->func);
  vector_delete(module->global);
  vector_delete(module->prior);
  type_pool_delete(module->type);
  value_pool_delete(module->value);
  UTILITY_FREE(module);
}
TypePool *module_get_type(Module *module) {
  return module->type;
}
Function *module_new_function(Module *module) {
  Function *func = function_new();
  value_pool_insert(module->value, function_as_value(func));
  vector_push(module->func, func);
  return func;
}
Block *module_new_block(Module *module) {
  Block *block = block_new();
  value_pool_insert(module->value, block_as_value(block));
  return block;
}
Instruction *module_new_instruction(Module *module) {
  Instruction *instr = instruction_new();
  value_pool_insert(module->value, instruction_as_value(instr));
  return instr;
}
Constant *module_new_constant(Module *module) {
  Constant *constant = constant_new();
  value_pool_insert(module->value, constant_as_value(constant));
  return constant;
}
Global *module_new_global(Module *module) {
  Global *global = global_new();
  value_pool_insert(module->value, global_as_value(global));
  vector_push(module->global, global);
  return global;
}
Type *module_new_type_integer(Module *module, int size) {
  return type_pool_integer(module->type, size);
}
void module_insert_prior(Module *module, Global *global) {
  if (!global_is_prior(global)) {
    vector_push(module->prior, global);
    global_set_prior(global);
  }
}
void module_build(Module *module, Sexp *ast) {
  Builder *builder = builder_new(module);
  builder_ast(builder, ast);
  builder_delete(builder);
}
void module_pretty(Module *module) {
  printf("target triple = \"x86_64-unknown-linux-gnu\"\n");
  if (!vector_empty(module->global)) {
    printf("\n");
    module_pretty_prior(module);
    module_pretty_global(module);
  }
  module_pretty_function(module);
}
