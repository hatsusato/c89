#ifndef INCLUDE_GUARD_1F1337DE_895F_45EE_959F_A1D190BEC347
#define INCLUDE_GUARD_1F1337DE_895F_45EE_959F_A1D190BEC347

struct json;
struct json_factory;

struct json *convert_get_identifier(struct json *json);
void convert(struct json_factory *, struct json *);

#endif /* INCLUDE_GUARD_1F1337DE_895F_45EE_959F_A1D190BEC347 */
