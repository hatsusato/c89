#ifndef INCLUDE_GUARD_C6FD6DD6_BA8B_48CA_8964_FF358D6F9282
#define INCLUDE_GUARD_C6FD6DD6_BA8B_48CA_8964_FF358D6F9282

struct str;
struct str_view;

struct str *str_new(const struct str_view *);
void str_delete(struct str *);

#endif /* INCLUDE_GUARD_C6FD6DD6_BA8B_48CA_8964_FF358D6F9282 */
