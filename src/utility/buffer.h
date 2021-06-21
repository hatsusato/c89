#ifndef INCLUDE_GUARD_2505370A_1954_47A8_BF38_6BC8B1F6BF30
#define INCLUDE_GUARD_2505370A_1954_47A8_BF38_6BC8B1F6BF30

#include "type.h"

struct buffer {
  byte_t *ptr;
  size_t size;
};

void buffer_malloc(struct buffer *);
void buffer_free(struct buffer *);
void buffer_memcpy(struct buffer *, const struct buffer *);

#endif /* INCLUDE_GUARD_2505370A_1954_47A8_BF38_6BC8B1F6BF30 */
