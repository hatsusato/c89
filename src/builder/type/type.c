#include "type.h"

#include <stdio.h>

#include "struct.h"

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
