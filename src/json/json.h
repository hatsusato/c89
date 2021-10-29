#ifndef INCLUDE_GUARD_5E299705_D2B2_4EFA_AD2B_575DB876526E
#define INCLUDE_GUARD_5E299705_D2B2_4EFA_AD2B_575DB876526E

struct json;

struct json *json_null(void);
struct json *json_obj_get(struct json *, const char *);
void json_obj_set(struct json *, const char *, struct json *);

#endif /* INCLUDE_GUARD_5E299705_D2B2_4EFA_AD2B_575DB876526E */
