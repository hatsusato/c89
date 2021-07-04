#ifndef INCLUDE_GUARD_B04970AB_F75D_4E4A_B3A9_B765648D10EE
#define INCLUDE_GUARD_B04970AB_F75D_4E4A_B3A9_B765648D10EE

#include "util/type.h"

struct box {
  void *ptr;
  size_t size;
};

void box_new(struct box *, size_t);
void box_delete(struct box *);
void *box_ptr(const struct box *);
size_t box_size(const struct box *);

#endif /* INCLUDE_GUARD_B04970AB_F75D_4E4A_B3A9_B765648D10EE */
