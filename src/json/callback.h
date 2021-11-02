#ifndef INCLUDE_GUARD_15A786EB_987B_4284_9538_D41F3B730C9C
#define INCLUDE_GUARD_15A786EB_987B_4284_9538_D41F3B730C9C

struct json;
struct json_callback;
struct json_obj;

typedef void (*json_callback_t)(struct json_obj *);

struct json_callback *json_callback_new(json_callback_t);
void json_callback_delete(struct json_callback *);
void json_callback_insert(struct json_callback *, const char *, struct json *);
void json_callback_apply(struct json_callback *);

#endif /* INCLUDE_GUARD_15A786EB_987B_4284_9538_D41F3B730C9C */
