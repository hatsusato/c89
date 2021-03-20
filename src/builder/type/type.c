#include "type.h"

#include "builder/builder.h"
#include "ir/module.h"
#include "ir/type/struct.h"
#include "utility/utility.h"

static Type type_integer(int size) {
  Type type;
  type.kind = TYPE_INTEGER;
  type.data.size = size;
  return type;
}

static Type *builder_new_type(Builder *builder, Type *type) {
  Module *module = builder_get_module(builder);
  return module_new_type(module, type);
}

Type *builder_type(Builder *builder, TypeSpec *spec) {
  Type type;
  type_init_spec(&type, spec);
  return builder_new_type(builder, &type);
}
Type *builder_type_void(Builder *builder) {
  Type type = type_integer(0);
  return builder_new_type(builder, &type);
}
Type *builder_type_bool(Builder *builder) {
  Type type = type_integer(1);
  return builder_new_type(builder, &type);
}
Type *builder_type_int(Builder *builder) {
  Type type = type_integer(32);
  return builder_new_type(builder, &type);
}
Type *builder_type_pointer(Builder *builder, Type *base) {
  Type type;
  type.kind = TYPE_POINTER;
  type.data.type = base;
  return builder_new_type(builder, &type);
}
Type *builder_type_label(Builder *builder) {
  Type type;
  type.kind = TYPE_LABEL;
  type.data.size = 0;
  return builder_new_type(builder, &type);
}
