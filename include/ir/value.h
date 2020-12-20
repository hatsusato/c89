#ifndef INCLUDE_GUARD_FE2AA6D9_B675_4B2E_839A_2B085264192A
#define INCLUDE_GUARD_FE2AA6D9_B675_4B2E_839A_2B085264192A

#include "ir/block_type.h"
#include "ir/constant_type.h"
#include "ir/function_type.h"
#include "ir/instruction_type.h"
#include "ir/value_type.h"

Function *value_as_function(Value *);
Block *value_as_block(Value *);
Instruction *value_as_instruction(Value *);
Constant *value_as_constant(Value *);
void value_print(Value *);

#endif /* INCLUDE_GUARD_FE2AA6D9_B675_4B2E_839A_2B085264192A */
