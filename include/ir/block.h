#ifndef INCLUDE_GUARD_158B0FE3_07C7_4187_B41D_C9D59FB58195
#define INCLUDE_GUARD_158B0FE3_07C7_4187_B41D_C9D59FB58195

#include "builder_type.h"
#include "ir/block_type.h"
#include "ir/instruction_type.h"
#include "ir/value_type.h"
#include "types.h"

Block *block_new(void);
void block_delete(Block *);
void block_insert(Block *, Instruction *);
void block_insert_switch(Block *, Value *, Block *);
void block_append(Block *, Block *);
Bool block_empty(Block *);
Bool block_is_terminated(Block *);
int block_set_id(Block *, int);
void block_print(Block *);
void block_print_label(Block *);
void block_pretty(Block *);
void block_pretty_switch(Block *);

Block *stack_new_block(Builder *);

#endif /* INCLUDE_GUARD_158B0FE3_07C7_4187_B41D_C9D59FB58195 */
