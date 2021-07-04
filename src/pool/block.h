#ifndef INCLUDE_GUARD_2234C8F0_274D_4287_A43D_9D9C08D851B7
#define INCLUDE_GUARD_2234C8F0_274D_4287_A43D_9D9C08D851B7

#include "util/box.h"
#include "util/buffer.h"

#define POOL_BLOCK_SIZE (4096)

struct pool_block {
  struct buffer buf;
  struct box box;
  size_t offset;
};

void pool_block_new(struct pool_block *);
void pool_block_delete(struct pool_block *);
const void *pool_block_insert(struct pool_block *, const struct buffer *);

#endif /* INCLUDE_GUARD_2234C8F0_274D_4287_A43D_9D9C08D851B7 */
