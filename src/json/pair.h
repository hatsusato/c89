#ifndef INCLUDE_GUARD_54000380_76D7_43D0_9E05_623E2AD81955
#define INCLUDE_GUARD_54000380_76D7_43D0_9E05_623E2AD81955

struct json;

struct json_pair {
  const char *key;
  struct json *val;
};

const char *json_pair_key(struct json_pair *);
struct json *json_pair_val(struct json_pair *);
void json_pair_set(struct json_pair *, const char *, struct json *);

#endif /* INCLUDE_GUARD_54000380_76D7_43D0_9E05_623E2AD81955 */
