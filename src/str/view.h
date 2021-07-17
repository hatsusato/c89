#ifndef INCLUDE_GUARD_D25BBF12_114D_4DCE_BC2A_1ADD984F469C
#define INCLUDE_GUARD_D25BBF12_114D_4DCE_BC2A_1ADD984F469C

#include "util/type.h"

struct str_view;

void str_view_init(struct str_view *, const char *, index_t);
void str_view_set(struct str_view *, const char *);
const char *str_view_ptr(const struct str_view *);
index_t str_view_length(const struct str_view *);
void str_view_remove_prefix(struct str_view *, index_t);
void str_view_remove_suffix(struct str_view *, index_t);
int str_view_cmp(const struct str_view *, const struct str_view *);

#endif /* INCLUDE_GUARD_D25BBF12_114D_4DCE_BC2A_1ADD984F469C */
