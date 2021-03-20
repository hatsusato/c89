#include "module.h"

#include <stdio.h>

#include "builder/builder.h"
#include "compare/compare.h"
#include "ir/block.h"
#include "ir/constant.h"
#include "ir/function.h"
#include "ir/global.h"
#include "ir/instruction.h"
#include "ir/type.h"
#include "ir/type/struct.h"
#include "ir/value.h"
#include "set/set.h"
#include "utility/utility.h"
#include "vector/vector.h"

struct struct_Module {
  Vector *values;
  Compare *type_cmp;
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
static Type *type_new(void) {
  Type *type = UTILITY_MALLOC(Type);
  type->kind = TYPE_INTEGER;
  type->data.size = 0;
  return type;
}
static Type type_integer(int size) {
  Type type;
  type.kind = TYPE_INTEGER;
  type.data.size = size;
  return type;
}

Module *module_new(void) {
  Module *module = UTILITY_MALLOC(Module);
  module->values = vector_new(module_delete_value);
  module->type_cmp = type_compare_new();
  module->types = type_set_new(module->type_cmp);
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
  compare_delete(module->type_cmp);
  vector_delete(module->values);
  UTILITY_FREE(module);
}
Type *module_new_type(Module *module, Type *type) {
  Type *found = module_find_type(module, type);
  if (!found) {
    found = type_new();
    *found = *type;
    module_insert_type(module, found);
  }
  return found;
}
Type *module_type_void(Module *module) {
  Type type = type_integer(0);
  return module_new_type(module, &type);
}
Type *module_type_bool(Module *module) {
  Type type = type_integer(1);
  return module_new_type(module, &type);
}
Type *module_type_int(Module *module) {
  Type type = type_integer(32);
  return module_new_type(module, &type);
}
Type *module_type_pointer(Module *module, Type *base) {
  Type type;
  type.kind = TYPE_POINTER;
  type.data.type = base;
  return module_new_type(module, &type);
}
Type *module_type_label(Module *module) {
  Type type;
  type.kind = TYPE_LABEL;
  type.data.size = 0;
  return module_new_type(module, &type);
}
Type *module_find_type(Module *module, Type *type) {
  return (Type *)set_find(module->types, type);
}
void module_insert_type(Module *module, Type *type) {
  set_insert(module->types, type);
}
void module_insert_value(Module *module, Value *value) {
  vector_push(module->values, value);
  switch (value_kind(value)) {
  case VALUE_FUNCTION:
    vector_push(module->func, value);
    break;
  case VALUE_GLOBAL:
    vector_push(module->global, value);
  default:
    break;
  }
}
void module_insert_prior(Module *module, Global *global) {
  if (!global_is_prior(global)) {
    vector_push(module->prior, global);
    global_set_prior(global);
  }
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
