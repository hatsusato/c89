#ifndef INCLUDE_GUARD_163637DD_0D83_468B_88CC_AEFD8917410E
#define INCLUDE_GUARD_163637DD_0D83_468B_88CC_AEFD8917410E

#include "type.h"

struct vec_ptr {
  struct vec vec;
};

struct vec_ptr *vec_ptr_new(void);
void vec_ptr_delete(struct vec_ptr *);
index_t vec_ptr_capacity(struct vec_ptr *);
index_t vec_ptr_length(struct vec_ptr *);

#endif /* INCLUDE_GUARD_163637DD_0D83_468B_88CC_AEFD8917410E */
