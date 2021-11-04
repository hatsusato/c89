#ifndef INCLUDE_GUARD_158B0FE3_07C7_4187_B41D_C9D59FB58195
#define INCLUDE_GUARD_158B0FE3_07C7_4187_B41D_C9D59FB58195

#include "utility/types.h"

Block *block_new(Module *);
void block_delete(Block *);
void block_insert(Block *, Instruction *);
void block_insert_switch(Block *, Value *, Block *);
void block_append(Block *, Block *);
Bool block_empty(Block *);
Instruction *block_last(Block *);
int block_set_id(Block *, int);
void block_print(Block *, Printer *);
void block_print_label(Block *, Printer *);
void block_pretty(Block *, Printer *);
void block_pretty_switch(Block *, Printer *);

#endif /* INCLUDE_GUARD_158B0FE3_07C7_4187_B41D_C9D59FB58195 */
