#ifndef INCLUDE_GUARD_38FED8DC_D1CD_4F59_8215_A5B3F0F735FF
#define INCLUDE_GUARD_38FED8DC_D1CD_4F59_8215_A5B3F0F735FF

struct json;
struct printer;

struct json *generate_global_get(struct json *);
void generate_global(struct printer *, struct json *);
void generate_global_name(struct printer *, struct json *);

#endif /* INCLUDE_GUARD_38FED8DC_D1CD_4F59_8215_A5B3F0F735FF */
