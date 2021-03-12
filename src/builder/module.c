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
#include "set/set.h"
#include "utility/utility.h"
#include "vector/vector.h"

struct struct_Module {
  Vector *values;
  Set *types;
  Vector *prior, *global, *func;
};

static void module_delete_value(VectorElem value) {
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
  case VALUE_GLOBAL:
    global_delete(value);
    break;
  default:
    UTILITY_ASSERT(0);
    break;
  }
}
static void module_pretty_prior(Module *module) {
  VectorElem *begin = vector_begin(module->prior);
  VectorElem *end = vector_end(module->prior);
  while (begin < end) {
    Global *global = *begin++;
    global_pretty(global);
  }
}
static void module_pretty_global(Module *module) {
  VectorElem *begin = vector_begin(module->global);
  VectorElem *end = vector_end(module->global);
  while (begin < end) {
    Global *global = *begin++;
    if (!global_is_prior(global)) {
      global_pretty(global);
    }
  }
}
static void module_pretty_function(Module *module) {
  VectorElem *begin = vector_begin(module->func);
  VectorElem *end = vector_end(module->func);
  while (begin < end) {
    printf("\n");
    function_pretty(*begin++);
  }
}

Module *module_new(void) {
  Module *module = UTILITY_MALLOC(Module);
  module->values = vector_new(module_delete_value);
  module->types = type_set_new();
  module->prior = vector_new(NULL);
  module->global = vector_new(NULL);
  module->func = vector_new(NULL);
  return module;
}
void module_delete(Module *module) {
  vector_delete(module->func);
  vector_delete(module->global);
  vector_delete(module->prior);
  type_set_delete(module->types);
  vector_delete(module->values);
  UTILITY_FREE(module);
}
Type *module_find_type(Module *module, Type *type) {
  const CompareElem *found = set_find(module->types, type);
  return found ? (Type *)*found : NULL;
}
void module_insert_type(Module *module, Type *type) {
  set_insert(module->types, type);
}
Function *module_new_function(Module *module) {
  Function *func = function_new();
  vector_push(module->values, func);
  vector_push(module->func, func);
  return func;
}
Block *module_new_block(Module *module) {
  Block *block = block_new();
  vector_push(module->values, block);
  return block;
}
Instruction *module_new_instruction(Module *module) {
  Instruction *instr = instruction_new();
  vector_push(module->values, instr);
  return instr;
}
Constant *module_new_constant(Module *module) {
  Constant *constant = constant_new();
  vector_push(module->values, constant);
  return constant;
}
Global *module_new_global(Module *module) {
  Global *global = global_new();
  vector_push(module->values, global);
  vector_push(module->global, global);
  return global;
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
