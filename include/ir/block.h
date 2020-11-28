#ifndef INCLUDE_GUARD_99995B0B_7C53_460D_87DC_0574B8F3FBB1
#define INCLUDE_GUARD_99995B0B_7C53_460D_87DC_0574B8F3FBB1

#include "ir/block_type.h"
#include "ir/builder_type.h"
#include "ir/value_type.h"

Block *block_new(void);
void block_delete(Block *);
void block_insert(Block *, Value *);
void block_set_id(Builder *, Block *);

#endif /* INCLUDE_GUARD_99995B0B_7C53_460D_87DC_0574B8F3FBB1 */
