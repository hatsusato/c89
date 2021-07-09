#ifndef INCLUDE_GUARD_1070D04D_4250_4AE0_B426_C897597C75CD
#define INCLUDE_GUARD_1070D04D_4250_4AE0_B426_C897597C75CD

#include "util/type.h"

struct buffer;
struct slice;

void slice_init(struct slice *, align_t, const void *, index_t);
void slice_resize(struct slice *, index_t);
void slice_buffer(struct slice *, struct buffer *);
align_t slice_align(const struct slice *);
index_t slice_length(const struct slice *);
size_t slice_size(const struct slice *);
const void *slice_ptr(const struct slice *);
const void *slice_at(const struct slice *, index_t);
void slice_map(const struct slice *, void (*)(const void *));

#endif /* INCLUDE_GUARD_1070D04D_4250_4AE0_B426_C897597C75CD */
