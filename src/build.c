#include "build.h"

#include "block.h"
#include "function.h"
#include "instruction.h"
#include "value.h"

Function *build_function(Sexp *ast) {
  Instruction *instr;
  Block *block;
  Function *func;
  instr = instruction_new(INSTRUCTION_RET);
  instruction_insert(instr, value_new_integer(0));
  block = block_new();
  block_insert(block, instr);
  func = function_new();
  function_set_name(func, function_name(ast));
  function_insert(func, block);
  return func;
}
