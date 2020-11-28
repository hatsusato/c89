#ifndef INCLUDE_GUARD_78E99201_C3B9_4B05_88E4_2BD5F30C2F6C
#define INCLUDE_GUARD_78E99201_C3B9_4B05_88E4_2BD5F30C2F6C

#include "ir/register_type.h"
#include "ir/value_kind.h"

struct struct_Value;
typedef struct struct_Value Value;

struct struct_ValueHeader {
  ValueKind kind;
  Register reg;
};
typedef struct struct_ValueHeader ValueHeader;

#endif /* INCLUDE_GUARD_78E99201_C3B9_4B05_88E4_2BD5F30C2F6C */
