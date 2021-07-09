#ifndef INCLUDE_GUARD_B04970AB_F75D_4E4A_B3A9_B765648D10EE
#define INCLUDE_GUARD_B04970AB_F75D_4E4A_B3A9_B765648D10EE

#include "util/type.h"

struct box_data;
struct buffer;

struct box_data *box_data_new(size_t);
void box_data_delete(struct box_data *);
void box_data_buffer(struct box_data *, struct buffer *);
void *box_data_ptr(const struct box_data *);
size_t box_data_size(const struct box_data *);

#endif /* INCLUDE_GUARD_B04970AB_F75D_4E4A_B3A9_B765648D10EE */
