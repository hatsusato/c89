#ifndef INCLUDE_GUARD_20801795_2D19_46F1_86E4_7C2726AB7AEF
#define INCLUDE_GUARD_20801795_2D19_46F1_86E4_7C2726AB7AEF

struct json;
struct json_str;

struct json_str *json_str_new(const char *);
void json_str_del(struct json *);
const char *json_str_get(struct json *);
void json_str_set(struct json *, const char *);

#endif /* INCLUDE_GUARD_20801795_2D19_46F1_86E4_7C2726AB7AEF */
