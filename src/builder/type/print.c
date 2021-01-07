#include "print.h"

#include <stdio.h>

#include "struct.h"

void type_print(Type *type) {
  if (!type) {
    return;
  }
  switch (type->kind) {
  case TYPE_INTEGER:
    if (0 == type->data.size) {
      printf("void");
    } else {
      printf("i%d", type->data.size);
    }
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
