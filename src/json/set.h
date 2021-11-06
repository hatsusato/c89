#ifndef INCLUDE_GUARD_0A2DDE84_20A0_4C2B_92E9_4482494817FF
#define INCLUDE_GUARD_0A2DDE84_20A0_4C2B_92E9_4482494817FF

struct json_set;

struct json_set *json_set_new(void);
void json_set_del(struct json_set *);
const char *json_set_insert(struct json_set *, const char *);

#endif /* INCLUDE_GUARD_0A2DDE84_20A0_4C2B_92E9_4482494817FF */
