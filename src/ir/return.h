#ifndef INCLUDE_GUARD_99FA06CA_902D_4A07_88BC_495FE02CD181
#define INCLUDE_GUARD_99FA06CA_902D_4A07_88BC_495FE02CD181

struct json;
struct json_map;

struct json *ir_return_new(struct json *);
int ir_return_get_count(struct json *);
void ir_return_increment(struct json *);
void ir_return_skip(struct json *);
void ir_return_finish_map(struct json_map *);

#endif /* INCLUDE_GUARD_99FA06CA_902D_4A07_88BC_495FE02CD181 */
