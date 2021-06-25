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
void *buffer_at(const struct buffer *, size_t);
size_t buffer_size(const struct buffer *);
void *buffer_malloc(struct buffer *, size_t);
void buffer_free(struct buffer *);
bool_t buffer_is_null(const struct buffer *);
void buffer_memcpy(struct buffer *, const struct buffer *);
void buffer_memmove(struct buffer *, const struct buffer *);
void buffer_slice(struct buffer *, size_t, size_t);
void buffer_slide(struct buffer *, size_t, size_t, size_t);
void buffer_sort(struct buffer *, index_t, align_t, cmp_t);

#endif /* INCLUDE_GUARD_2505370A_1954_47A8_BF38_6BC8B1F6BF30 */
