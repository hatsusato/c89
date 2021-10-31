#ifndef INCLUDE_GUARD_20801795_2D19_46F1_86E4_7C2726AB7AEF
#define INCLUDE_GUARD_20801795_2D19_46F1_86E4_7C2726AB7AEF

struct json_str;

struct json_str *json_str_new(const char *);
void json_str_delete(struct json_str *);
const char *json_json_str_get(struct json_str *);
void json_str_set(struct json_str *, const char *);

#endif /* INCLUDE_GUARD_20801795_2D19_46F1_86E4_7C2726AB7AEF */
