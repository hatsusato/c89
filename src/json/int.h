#ifndef INCLUDE_GUARD_D056FAB2_6588_4A0F_9DF2_D1FDBC097051
#define INCLUDE_GUARD_D056FAB2_6588_4A0F_9DF2_D1FDBC097051

struct json_int;

struct json_int *json_int_new(int);
void json_int_del(struct json_int *);
int json_int_get(struct json_int *);
void json_int_set(struct json_int *, int);

#endif /* INCLUDE_GUARD_D056FAB2_6588_4A0F_9DF2_D1FDBC097051 */
