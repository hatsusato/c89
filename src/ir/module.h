#ifndef INCLUDE_GUARD_6DEB3F5D_8CE8_4C31_B2A0_7C9C1EFC5B08
#define INCLUDE_GUARD_6DEB3F5D_8CE8_4C31_B2A0_7C9C1EFC5B08

struct json;

struct json *ir_module_new(void);
void ir_module_push_global(struct json *, struct json *);

#endif /* INCLUDE_GUARD_6DEB3F5D_8CE8_4C31_B2A0_7C9C1EFC5B08 */
