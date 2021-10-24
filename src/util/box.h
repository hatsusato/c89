#ifndef INCLUDE_GUARD_B04970AB_F75D_4E4A_B3A9_B765648D10EE
#define INCLUDE_GUARD_B04970AB_F75D_4E4A_B3A9_B765648D10EE

#include "util/type.h"

struct box;
struct buffer;

void box_init(struct box *, align_t, index_t);
void box_finish(struct box *);
struct box *box_new(align_t, index_t);
void box_delete(struct box *);
void box_buffer(struct box *, struct buffer *);
void *box_get(const struct box *);
void *box_ptr(const struct box *);
void box_release(void *);
size_t box_size(const struct box *);

#endif /* INCLUDE_GUARD_B04970AB_F75D_4E4A_B3A9_B765648D10EE */
