#ifndef INCLUDE_GUARD_9CD5F173_4C3F_436C_9085_C797766F802E
#define INCLUDE_GUARD_9CD5F173_4C3F_436C_9085_C797766F802E

#include "scanner.h"
#include "util/symbol.h"
#include "yyscan_t.h"

#define YYSCAN_TOKEN() yyscan_json_token(YYSCAN_PARAM)
#define YYSCAN_NULL() yyscan_json_null()
#define YYSCAN_ARR() yyscan_json_arr()
#define YYSCAN_OBJ() yyscan_json_obj()
#define YYSCAN_SINGLE(val) YYSCAN_PUSH(YYSCAN_ARR(), val)
#define YYSCAN_PUSH(arr, val) yyscan_json_push(arr, val)
#define YYSCAN_INSERT(obj, key, val) yyscan_json_set(obj, key, val)
#define YYSCAN_EXPR(key) yyscan_json_expr(key)
#define YYSCAN_REGISTER(decl) \
  scanner_register_typedef(yyget_extra(YYSCAN_PARAM), decl)
#define YYSCAN_SET_TOP(top) scanner_set_top(yyget_extra(YYSCAN_PARAM), top)

void yyerror(yyscan_t, const char *);
void yyscan_parse(YYSCAN_EXTRA);
int yyscan_is_typedef(yyscan_t, const char *);
YYSCAN_TYPE yyscan_json_token(yyscan_t);
YYSCAN_TYPE yyscan_json_null(void);
YYSCAN_TYPE yyscan_json_arr(void);
YYSCAN_TYPE yyscan_json_obj(void);
YYSCAN_TYPE yyscan_json_push(YYSCAN_TYPE, YYSCAN_TYPE);
YYSCAN_TYPE yyscan_json_set(YYSCAN_TYPE, const char *, YYSCAN_TYPE);
YYSCAN_TYPE yyscan_json_expr(const char *);

#endif /* INCLUDE_GUARD_9CD5F173_4C3F_436C_9085_C797766F802E */
