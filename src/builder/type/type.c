#include "type.h"

#include <stdio.h>

#include "struct.h"
#include "utility.h"

int type_cmp(ElemType lhs, ElemType rhs, CompareExtra extra) {
  Type *l = lhs, *r = rhs;
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
Type *type_new(void) {
  Type *type = UTILITY_MALLOC(Type);
  type->kind = TYPE_KIND_COUNT;
  type->data.size = 0;
  return type;
}
void type_delete(ElemType type) {
  UTILITY_FREE(type);
}
Bool type_is_void(Type *type) {
  return TYPE_VOID == type->kind;
}
void type_print(Type *type) {
  switch (type ? type->kind : TYPE_KIND_COUNT) {
  case TYPE_VOID:
    printf("void");
    break;
  case TYPE_INTEGER:
    printf("i%d", type->data.size);
    break;
  case TYPE_POINTER:
    type_print(type->data.type);
    printf("*");
    break;
  case TYPE_LABEL:
    printf("label");
    break;
  default:
    printf("null");
    break;
  }
}
void type_print_elem(Type *type) {
  if (TYPE_POINTER == type->kind) {
    type_print(type->data.type);
  }
}
