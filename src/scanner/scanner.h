#ifndef INCLUDE_GUARD_A6B027B6_CC3A_495C_994F_1210000639A6
#define INCLUDE_GUARD_A6B027B6_CC3A_495C_994F_1210000639A6

struct cell;
struct json_factory;
struct pool;
struct set;

const struct cell *scanner_parse(struct json_factory *, struct pool *,
                                 struct set *);

#endif /* INCLUDE_GUARD_A6B027B6_CC3A_495C_994F_1210000639A6 */
