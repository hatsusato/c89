#ifndef INCLUDE_GUARD_7ABBD975_1225_4AF5_BCA9_04D58DC44EF3
#define INCLUDE_GUARD_7ABBD975_1225_4AF5_BCA9_04D58DC44EF3

struct json;

void convert_function_init(struct json *);
void convert_function_finish(struct json *);
struct json *convert_function_get_blocks(struct json *);
void convert_function_set_name(struct json *, struct json *);
void convert_function_definition(struct json *, struct json *);

#endif /* INCLUDE_GUARD_7ABBD975_1225_4AF5_BCA9_04D58DC44EF3 */
