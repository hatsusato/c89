#ifndef INCLUDE_GUARD_08A15673_FD7A_4FF2_A832_8E821FC95753
#define INCLUDE_GUARD_08A15673_FD7A_4FF2_A832_8E821FC95753

#include "type.h"

struct range {
  index_t begin, end;
};

void range_init(struct range *, index_t, index_t);
bool_t range_is_valid(const struct range *);

#endif /* INCLUDE_GUARD_08A15673_FD7A_4FF2_A832_8E821FC95753 */
