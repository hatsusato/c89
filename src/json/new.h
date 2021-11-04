#ifndef INCLUDE_GUARD_ECF85374_1D53_4EC2_A2A3_98ADD3780551
#define INCLUDE_GUARD_ECF85374_1D53_4EC2_A2A3_98ADD3780551

struct json *json_new_int(int);
struct json *json_new_str(const char *);
struct json *json_new_arr(void);
struct json *json_new_obj(void);
void json_del(struct json *);

#endif /* INCLUDE_GUARD_ECF85374_1D53_4EC2_A2A3_98ADD3780551 */
