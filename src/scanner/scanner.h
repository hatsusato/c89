#ifndef INCLUDE_GUARD_A6B027B6_CC3A_495C_994F_1210000639A6
#define INCLUDE_GUARD_A6B027B6_CC3A_495C_994F_1210000639A6

#include "yyscan_t.h"

struct json_factory;

YYSCAN_EXTRA scanner_new(struct json_factory *);
void scanner_del(YYSCAN_EXTRA);
YYSCAN_TYPE scanner_json_token(YYSCAN_EXTRA, const char *);
YYSCAN_TYPE scanner_get_comma(YYSCAN_EXTRA);
YYSCAN_TYPE scanner_get_top(YYSCAN_EXTRA);
void scanner_set_top(YYSCAN_EXTRA, YYSCAN_TYPE);
int scanner_is_typedef(YYSCAN_EXTRA, const char *);
void scanner_register_typedef(YYSCAN_EXTRA, YYSCAN_TYPE);

#endif /* INCLUDE_GUARD_A6B027B6_CC3A_495C_994F_1210000639A6 */
