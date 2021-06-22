#ifndef INCLUDE_GUARD_55419819_A196_4816_9A82_349ADA502BAA
#define INCLUDE_GUARD_55419819_A196_4816_9A82_349ADA502BAA

#include "utility/type.h"

struct buffer;
struct vector_span {
  byte_t *begin, *end;
  align_t align;
};

void vector_span_init(struct vector_span *, byte_t *);
size_t vector_span_length(const struct vector_span *);
byte_t *vector_span_at(const struct vector_span *, index_t);
void vector_span_push_back(struct vector_span *, size_t, const struct buffer *);
void vector_span_pop_back(struct vector_span *, size_t, struct buffer *);
void vector_span_push_front(struct vector_span *, size_t,
                            const struct buffer *);
void vector_span_pop_front(struct vector_span *, size_t, struct buffer *);

#endif /* INCLUDE_GUARD_55419819_A196_4816_9A82_349ADA502BAA */
