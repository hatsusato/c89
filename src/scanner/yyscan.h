#ifndef INCLUDE_GUARD_9CD5F173_4C3F_436C_9085_C797766F802E
#define INCLUDE_GUARD_9CD5F173_4C3F_436C_9085_C797766F802E

#include "yyscan_t.h"

#define YYSCAN_NULL() yyscan_json_null()
#define YYSCAN_TOKEN() yyscan_json_token(YYSCAN_PARAM)
#define YYSCAN_SYMBOL(symbol) yyscan_json_symbol(YYSCAN_PARAM, #symbol)
#define YYSCAN_ARR() yyscan_json_arr(YYSCAN_PARAM)
#define YYSCAN_PUSH(arr, val) yyscan_json_push(arr, val)
#define YYSCAN_OBJ() yyscan_json_obj(YYSCAN_PARAM)
#define YYSCAN_SET(obj, key, val) yyscan_json_insert(obj, #key, val)
#define YYSCAN_SET_TOP(top) yyscan_set_top(YYSCAN_PARAM, top)

void yyerror(yyscan_t, const char *);
yyscan_t yyscan_new(struct scanner *);
void yyscan_delete(yyscan_t);
void yyscan_parse(yyscan_t);
int yyscan_is_typedef(yyscan_t, const char *);
void yyscan_register_typedef(yyscan_t, const struct cell *);
void yyscan_set_ast(yyscan_t, const struct cell *);
const struct cell *yyscan_token(yyscan_t);
const struct cell *yyscan_symbol(yyscan_t, const char *);
const struct cell *yyscan_push(yyscan_t, const struct cell *,
                               const struct cell *);
const struct cell *yyscan_list(yyscan_t, int, ...);

struct json *yyscan_json_null(void);
struct json *yyscan_json_token(yyscan_t);
struct json *yyscan_json_symbol(yyscan_t, const char *);
struct json *yyscan_json_arr(yyscan_t);
struct json *yyscan_json_push(struct json *, struct json *);
struct json *yyscan_json_obj(yyscan_t);
void yyscan_json_insert(struct json *, const char *, struct json *);
void yyscan_set_top(yyscan_t, struct json *);

#endif /* INCLUDE_GUARD_9CD5F173_4C3F_436C_9085_C797766F802E */
