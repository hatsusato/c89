#include "ir/block.h"

#include "ir/block_type.h"
#include "ir/instruction.h"
#include "ir/register.h"
#include "ir/register_type.h"
#include "ir/value.h"
#include "ir/value_kind.h"
#include "ir/value_type.h"
#include "utility.h"
#include "vector.h"

struct struct_Block {
  ValueHeader header;
  Vector *instrs;
};
