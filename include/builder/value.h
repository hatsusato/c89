#ifndef INCLUDE_GUARD_FE2AA6D9_B675_4B2E_839A_2B085264192A
#define INCLUDE_GUARD_FE2AA6D9_B675_4B2E_839A_2B085264192A

#include "builder/block/type.h"
#include "builder/constant/type.h"
#include "builder/function/type.h"
#include "builder/instruction/type.h"
#include "builder/value/kind.h"
#include "builder/value/type.h"

Value *function_as_value(Function *);
Value *block_as_value(Block *);
Value *instruction_as_value(Instruction *);
Value *constant_as_value(Constant *);
Function *value_as_function(Value *);
Block *value_as_block(Value *);
Instruction *value_as_instruction(Value *);
Constant *value_as_constant(Value *);
ValueKind value_kind(Value *);
void value_print(Value *);

#endif /* INCLUDE_GUARD_FE2AA6D9_B675_4B2E_839A_2B085264192A */
