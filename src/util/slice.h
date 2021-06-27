#ifndef INCLUDE_GUARD_1070D04D_4250_4AE0_B426_C897597C75CD
#define INCLUDE_GUARD_1070D04D_4250_4AE0_B426_C897597C75CD

#include "type.h"

struct range;

struct slice {
  align_t align;
  const byte_t *ptr;
  index_t len;
};

void slice_init(struct slice *, align_t, const void *, index_t);
void slice_resize(struct slice *, index_t);
bool_t slice_is_null(const struct slice *);
align_t slice_align(const struct slice *);
index_t slice_length(const struct slice *);
size_t slice_size(const struct slice *);
const void *slice_ptr(const struct slice *);
const void *slice_at(const struct slice *, index_t);

#endif /* INCLUDE_GUARD_1070D04D_4250_4AE0_B426_C897597C75CD */
