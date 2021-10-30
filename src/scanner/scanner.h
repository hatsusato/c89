#ifndef INCLUDE_GUARD_A6B027B6_CC3A_495C_994F_1210000639A6
#define INCLUDE_GUARD_A6B027B6_CC3A_495C_994F_1210000639A6

#include "yyscan_t.h"

struct json_factory;
struct set;

YYSCAN_EXTRA scanner_new(struct json_factory *, struct set *);
void scanner_delete(YYSCAN_EXTRA);

#endif /* INCLUDE_GUARD_A6B027B6_CC3A_495C_994F_1210000639A6 */
