#ifndef INCLUDE_GUARD_2505370A_1954_47A8_BF38_6BC8B1F6BF30
#define INCLUDE_GUARD_2505370A_1954_47A8_BF38_6BC8B1F6BF30

#include "utility/type.h"

struct vector_buffer {
  byte_t *ptr;
  size_t size;
};

void vector_buffer_malloc(struct vector_buffer *);
void vector_buffer_free(struct vector_buffer *);

#endif /* INCLUDE_GUARD_2505370A_1954_47A8_BF38_6BC8B1F6BF30 */
