#include "module.h"

#include "ir/block.h"
#include "ir/constant.h"
#include "ir/function.h"
#include "ir/global.h"
#include "ir/instruction.h"
#include "ir/type.h"
#include "ir/type/struct.h"
#include "ir/value.h"
#include "printer/printer.h"
#include "utility/utility.h"
#include "vector/vector.h"

struct struct_Module {
  Vector *values;
  TypePool *types;
  Vector *prior, *global, *func;
};

static void module_delete_value(Generic value) {
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
static void module_pretty_prior(Module *module, Printer *printer) {
  VectorElem *begin = vector_begin(module->prior);
  VectorElem *end = vector_end(module->prior);
  while (begin < end) {
    Global *global = *begin++;
    global_pretty(global, printer);
  }
}
static void module_pretty_global(Module *module, Printer *printer) {
  VectorElem *begin = vector_begin(module->global);
  VectorElem *end = vector_end(module->global);
  while (begin < end) {
    Global *global = *begin++;
    if (!global_is_prior(global)) {
      global_pretty(global, printer);
    }
  }
}
static void module_pretty_function(Module *module, Printer *printer) {
  VectorElem *begin = vector_begin(module->func);
  VectorElem *end = vector_end(module->func);
  while (begin < end) {
    printer_newline(printer);
    function_pretty(*begin++, printer);
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
  module->types = type_pool_new();
  module->prior = vector_new(NULL);
  module->global = vector_new(NULL);
  module->func = vector_new(NULL);
  return module;
}
void module_delete(Module *module) {
  vector_delete(module->func);
  vector_delete(module->global);
  vector_delete(module->prior);
  type_pool_delete(module->types);
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
  return type_pool_find(module->types, type);
}
void module_insert_type(Module *module, Type *type) {
  type_pool_insert(module->types, type);
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
void module_pretty(Module *module, Printer *printer) {
  printer_print(printer, "target triple = \"x86_64-unknown-linux-gnu\"");
  printer_newline(printer);
  if (!vector_empty(module->global)) {
    printer_newline(printer);
    module_pretty_prior(module, printer);
    module_pretty_global(module, printer);
  }
  module_pretty_function(module, printer);
}
