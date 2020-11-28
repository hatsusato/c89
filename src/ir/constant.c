#include "ir/constant.h"

#include "ir/value_type.h"

struct struct_Constant {
  ValueHeader header;
  const char* value;
};
