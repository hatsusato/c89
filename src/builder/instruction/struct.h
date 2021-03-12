#ifndef INCLUDE_GUARD_5AB8E8B0_FFC8_4467_A473_DBE7945B905D
#define INCLUDE_GUARD_5AB8E8B0_FFC8_4467_A473_DBE7945B905D

#include "../value.h"

typedef enum {
#define DO_HANDLE(name, str) name,
#include "instruction.def"
#undef DO_HANDLE
  INSTRUCTION_KIND_COUNT
} InstructionKind;

enum { INSTRUCTION_OPERAND_COUNT = 3 };
struct struct_Instruction {
  ValueKind kind;
  Type *type;
  InstructionKind ikind;
  int id;
  Value *operands[INSTRUCTION_OPERAND_COUNT];
};

#endif /* INCLUDE_GUARD_5AB8E8B0_FFC8_4467_A473_DBE7945B905D */
