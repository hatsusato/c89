#ifndef INCLUDE_GUARD_7ABBD975_1225_4AF5_BCA9_04D58DC44EF3
#define INCLUDE_GUARD_7ABBD975_1225_4AF5_BCA9_04D58DC44EF3

struct convert;

void convert_function_init(struct convert *);
void convert_function_finish(struct convert *);
struct json *convert_function_get(struct convert *);
void convert_function_set_name(struct convert *, struct json *);

#endif /* INCLUDE_GUARD_7ABBD975_1225_4AF5_BCA9_04D58DC44EF3 */
