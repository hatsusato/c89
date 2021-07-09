#ifndef INCLUDE_GUARD_2505370A_1954_47A8_BF38_6BC8B1F6BF30
#define INCLUDE_GUARD_2505370A_1954_47A8_BF38_6BC8B1F6BF30

#include "type.h"

struct buffer {
  byte_t *ptr;
  size_t size;
};

void buffer_init(struct buffer *, void *, size_t);
void *buffer_at(const struct buffer *, size_t);
size_t buffer_size(const struct buffer *);
void buffer_copy(struct buffer *, size_t, const struct buffer *);
void buffer_slide(struct buffer *, size_t, size_t, size_t);

#endif /* INCLUDE_GUARD_2505370A_1954_47A8_BF38_6BC8B1F6BF30 */
