#ifndef INCLUDE_GUARD_D25BBF12_114D_4DCE_BC2A_1ADD984F469C
#define INCLUDE_GUARD_D25BBF12_114D_4DCE_BC2A_1ADD984F469C

#include "util/type.h"

struct str {
  const char *ptr;
  index_t len;
};

void str_init(struct str *, const char *);

#endif /* INCLUDE_GUARD_D25BBF12_114D_4DCE_BC2A_1ADD984F469C */
