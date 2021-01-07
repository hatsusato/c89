#ifndef INCLUDE_GUARD_FE2AA6D9_B675_4B2E_839A_2B085264192A
#define INCLUDE_GUARD_FE2AA6D9_B675_4B2E_839A_2B085264192A

#include "builder/types.h"

typedef enum {
  VALUE_FUNCTION,
  VALUE_BLOCK,
  VALUE_INSTRUCTION,
  VALUE_CONSTANT,
  VALUE_GLOBAL,
  VALUE_KIND_END
} ValueKind;

Value *function_as_value(Function *);
Value *block_as_value(Block *);
Value *instruction_as_value(Instruction *);
Value *constant_as_value(Constant *);
Value *global_as_value(Global *);
Function *value_as_function(Value *);
Block *value_as_block(Value *);
Instruction *value_as_instruction(Value *);
Constant *value_as_constant(Value *);
Global *value_as_global(Value *);
ValueKind value_kind(Value *);
Type *value_type(Value *);
void value_print(Value *, Bool);
void value_print_type(Value *);
void value_print_with_type(Value *, Bool);

#endif /* INCLUDE_GUARD_FE2AA6D9_B675_4B2E_839A_2B085264192A */
