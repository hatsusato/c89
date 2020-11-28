#include "ir/register.h"

#include "ir/value_kind.h"
#include "utility.h"

struct struct_Register {
  ValueKind kind;
  int id;
};
typedef struct struct_Register Register;
