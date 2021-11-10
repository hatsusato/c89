#ifndef INCLUDE_GUARD_359EE31B_6995_430C_8D7C_6BE05E2817E2
#define INCLUDE_GUARD_359EE31B_6995_430C_8D7C_6BE05E2817E2

struct json;

void ir_global_init(struct json *);
void ir_global_finish(struct json *);
struct json *ir_global_get(struct json *);
const char *ir_global_value_name(struct json *);

#endif /* INCLUDE_GUARD_359EE31B_6995_430C_8D7C_6BE05E2817E2 */
