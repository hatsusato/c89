#include "type.h"

#include "builder.h"
#include "compare/compare.h"
#include "set/set.h"
#include "type/struct.h"
#include "utility/utility.h"

static int type_cmp(CompareElem lhs, CompareElem rhs, CompareExtra extra) {
  const Type *l = lhs, *r = rhs;
  if (l->kind != r->kind) {
    return (l->kind < r->kind) ? -1 : 1;
  }
  switch (l->kind) {
  case TYPE_INTEGER:
    return utility_intcmp(l->data.size, r->data.size);
  case TYPE_POINTER:
    return type_cmp(l->data.type, r->data.type, extra);
  default:
    return 0;
  }
}
static Type *type_new(void) {
  Type *type = UTILITY_MALLOC(Type);
  type->kind = TYPE_INTEGER;
  type->data.size = 0;
  return type;
}
static void type_delete(VectorElem type) {
  UTILITY_FREE(type);
}
static Type type_integer(int size) {
  Type type;
  type.kind = TYPE_INTEGER;
  type.data.size = size;
  return type;
}

Compare *type_compare_new(void) {
  return compare_new(type_cmp, NULL);
}
Set *type_set_new(Compare *cmp) {
  Set *set = set_new(type_delete, cmp);
  return set;
}
void type_set_delete(Set *set) {
  set_delete(set);
}

Bool type_equals(Type *lhs, Type *rhs) {
  return 0 == type_cmp(lhs, rhs, NULL);
}
Bool type_is_void(Type *type) {
  return TYPE_INTEGER == type->kind && 0 == type->data.size;
}
int type_sizeof(Type *type) {
  return TYPE_INTEGER == type->kind ? type->data.size : 0;
}

static Type *builder_new_type(Builder *builder, Type *type) {
  Module *module = builder_get_module(builder);
  Type *found = module_find_type(module, type);
  if (!found) {
    found = type_new();
    *found = *type;
    module_insert_type(module, found);
  }
  return found;
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
