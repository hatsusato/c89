#ifndef INCLUDE_GUARD_15A786EB_987B_4284_9538_D41F3B730C9C
#define INCLUDE_GUARD_15A786EB_987B_4284_9538_D41F3B730C9C

struct json;
struct json_closure;

typedef void (*json_closure_t)(struct json *);

struct json_closure *json_closure_new(json_closure_t);
void json_closure_delete(struct json_closure *);
struct json *json_closure_args(struct json_closure *);
struct json *json_closure_get(struct json_closure *, const char *);
void json_closure_insert(struct json_closure *, const char *, struct json *);
void json_closure_apply(struct json_closure *);

#endif /* INCLUDE_GUARD_15A786EB_987B_4284_9538_D41F3B730C9C */
