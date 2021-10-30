#ifndef INCLUDE_GUARD_A6B027B6_CC3A_495C_994F_1210000639A6
#define INCLUDE_GUARD_A6B027B6_CC3A_495C_994F_1210000639A6

#include "yyscan_t.h"

struct json_factory;
struct pool;
struct set;

void scanner_init(YYSCAN_EXTRA, struct json_factory *, struct pool *,
                  struct set *);
void scanner_finish(YYSCAN_EXTRA);

#endif /* INCLUDE_GUARD_A6B027B6_CC3A_495C_994F_1210000639A6 */
