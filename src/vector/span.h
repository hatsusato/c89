#ifndef INCLUDE_GUARD_55419819_A196_4816_9A82_349ADA502BAA
#define INCLUDE_GUARD_55419819_A196_4816_9A82_349ADA502BAA

#include "utility/type.h"

struct vector_buffer;
struct vector_span {
  byte_t *begin, *end;
  size_t size;
};

void vector_span_init(struct vector_span *, byte_t *, size_t);
size_t vector_span_length(struct vector_span *);
void vector_span_push_back(struct vector_span *, const struct vector_buffer *);
byte_t *vector_span_pop_back(struct vector_span *);
void vector_span_push_front(struct vector_span *, const struct vector_buffer *);
byte_t *vector_span_pop_front(struct vector_span *);

#endif /* INCLUDE_GUARD_55419819_A196_4816_9A82_349ADA502BAA */
