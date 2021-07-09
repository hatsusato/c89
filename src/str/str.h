#ifndef INCLUDE_GUARD_D25BBF12_114D_4DCE_BC2A_1ADD984F469C
#define INCLUDE_GUARD_D25BBF12_114D_4DCE_BC2A_1ADD984F469C

#include "util/type.h"

struct str;

void str_init(struct str *, const char *, index_t);
void str_set(struct str *, const char *);
const char *str_ptr(const struct str *);
index_t str_length(const struct str *);
void str_remove_prefix(struct str *, index_t);
void str_remove_suffix(struct str *, index_t);
int str_cmp(const struct str *, const struct str *);

#endif /* INCLUDE_GUARD_D25BBF12_114D_4DCE_BC2A_1ADD984F469C */
