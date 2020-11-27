#include "ir/value.h"

typedef enum { VALUE_REGISTER, VALUE_INTEGER_CONSTANT } ValueKind;
struct struct_Value {
  ValueKind kind;
};
