#ifndef INCLUDE_GUARD_77726E87_251A_41CB_9277_CB6E6EBFAA3A
#define INCLUDE_GUARD_77726E87_251A_41CB_9277_CB6E6EBFAA3A

struct json_any;

struct json_any *json_any_new(void *);
void json_any_delete(struct json_any *);
void *json_any_get(struct json_any *);
void json_any_set(struct json_any *, void *);

#endif /* INCLUDE_GUARD_77726E87_251A_41CB_9277_CB6E6EBFAA3A */
