#ifndef INCLUDE_GUARD_A6B027B6_CC3A_495C_994F_1210000639A6
#define INCLUDE_GUARD_A6B027B6_CC3A_495C_994F_1210000639A6

#include "yyscan_t.h"

struct json_factory;
struct set;

YYSCAN_EXTRA scanner_new(struct json_factory *, struct set *);
void scanner_delete(YYSCAN_EXTRA);
YYSCAN_TYPE scanner_json_str(YYSCAN_EXTRA, const char *);
YYSCAN_TYPE scanner_json_arr(YYSCAN_EXTRA);
YYSCAN_TYPE scanner_json_obj(YYSCAN_EXTRA);
YYSCAN_TYPE scanner_json_push(YYSCAN_TYPE, YYSCAN_TYPE);
void scanner_json_set(YYSCAN_TYPE, const char *, YYSCAN_TYPE);
void scanner_set_top(YYSCAN_EXTRA, YYSCAN_TYPE);

#endif /* INCLUDE_GUARD_A6B027B6_CC3A_495C_994F_1210000639A6 */
