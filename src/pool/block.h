#ifndef INCLUDE_GUARD_2234C8F0_274D_4287_A43D_9D9C08D851B7
#define INCLUDE_GUARD_2234C8F0_274D_4287_A43D_9D9C08D851B7

#include "util/buffer.h"

struct pool_block {
  struct buffer buf;
  size_t offset;
};

void pool_block_malloc(struct pool_block *);
void pool_block_free(struct pool_block *);

#endif /* INCLUDE_GUARD_2234C8F0_274D_4287_A43D_9D9C08D851B7 */
