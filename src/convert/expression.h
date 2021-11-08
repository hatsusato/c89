#ifndef INCLUDE_GUARD_82559F89_31B8_4EF5_B42E_0882525D7E61
#define INCLUDE_GUARD_82559F89_31B8_4EF5_B42E_0882525D7E61

struct convert_extra;
struct json;

struct json *convert_lvalue(struct convert_extra *, struct json *);
struct json *convert_rvalue(struct convert_extra *, struct json *);

#endif /* INCLUDE_GUARD_82559F89_31B8_4EF5_B42E_0882525D7E61 */
