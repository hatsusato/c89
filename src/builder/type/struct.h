#ifndef INCLUDE_GUARD_6A25DBB4_9C67_4CE8_A791_2C8EBEAEA471
#define INCLUDE_GUARD_6A25DBB4_9C67_4CE8_A791_2C8EBEAEA471

#include "utility/types.h"

typedef enum {
  TYPE_INTEGER,
  TYPE_POINTER,
  TYPE_LABEL,
  TYPE_KIND_COUNT
} TypeKind;

struct struct_Type {
  TypeKind kind;
  union {
    int size;
    Type *type;
  } data;
};

#endif /* INCLUDE_GUARD_6A25DBB4_9C67_4CE8_A791_2C8EBEAEA471 */
