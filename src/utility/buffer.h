#ifndef INCLUDE_GUARD_2505370A_1954_47A8_BF38_6BC8B1F6BF30
#define INCLUDE_GUARD_2505370A_1954_47A8_BF38_6BC8B1F6BF30

#include "type.h"

#define BUFFER_INIT(buf, ptr) buffer_init((buf), (ptr), sizeof(*(ptr)))
#define BUFFER_MALLOC(buf, type) buffer_malloc((buf), sizeof(type))

struct buffer {
  byte_t *ptr;
  size_t size;
};

void buffer_init(struct buffer *, void *, size_t);
void buffer_malloc(struct buffer *, size_t);
void buffer_free(struct buffer *);
void buffer_memcpy(struct buffer *, const struct buffer *);
void buffer_memmove(struct buffer *, const struct buffer *);

#endif /* INCLUDE_GUARD_2505370A_1954_47A8_BF38_6BC8B1F6BF30 */
