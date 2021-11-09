#ifndef INCLUDE_GUARD_6A3F1D69_8D3A_4F64_8B75_5A257F7F2C7F
#define INCLUDE_GUARD_6A3F1D69_8D3A_4F64_8B75_5A257F7F2C7F

struct json;

void convert_global_init(struct json *);
struct json *convert_global_new_value(struct json *);
void convert_global_push(struct json *, struct json *);

#endif /* INCLUDE_GUARD_6A3F1D69_8D3A_4F64_8B75_5A257F7F2C7F */
