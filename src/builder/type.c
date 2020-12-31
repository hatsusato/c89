#include "type.h"

#include "utility.h"

struct struct_Type {
  int size;
};

Type *type_new(void) {
  Type *type = UTILITY_MALLOC(Type);
  type->size = 0;
  return type;
}
void type_delete(Type *type) {
  UTILITY_FREE(type);
}
