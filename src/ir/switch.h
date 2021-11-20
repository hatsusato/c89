#ifndef INCLUDE_GUARD_B29EC253_65D8_4238_9360_4737B629305C
#define INCLUDE_GUARD_B29EC253_65D8_4238_9360_4737B629305C

struct json;

struct json *ir_switch_new(struct json *);
void ir_switch_del(struct json *);
void ir_switch_insert_default(struct json *, struct json *);
void ir_switch_insert_case(struct json *, struct json *, struct json *);

#endif /* INCLUDE_GUARD_B29EC253_65D8_4238_9360_4737B629305C */
