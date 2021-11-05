#ifndef INCLUDE_GUARD_9CD5F173_4C3F_436C_9085_C797766F802E
#define INCLUDE_GUARD_9CD5F173_4C3F_436C_9085_C797766F802E

#include "scanner.h"
#include "util/symbol.h"
#include "yyscan_t.h"

#define YYSCAN_TOKEN() yyscan_json_token(YYSCAN_PARAM)
#define YYSCAN_STR(symbol) scanner_json_str(yyget_extra(YYSCAN_PARAM), symbol)
#define YYSCAN_ARR() scanner_json_arr(yyget_extra(YYSCAN_PARAM))
#define YYSCAN_OBJ() scanner_json_obj(yyget_extra(YYSCAN_PARAM))
#define YYSCAN_PUSH(arr, val) scanner_json_push(arr, val)
#define YYSCAN_SET(obj, key, val) scanner_json_set(obj, key, val)
#define YYSCAN_TAG(key, val) YYSCAN_SET(YYSCAN_OBJ(), key, val)
#define YYSCAN_BINOP(lhs, op, rhs) \
  scanner_json_binop(yyget_extra(YYSCAN_PARAM), lhs, op, rhs)
#define YYSCAN_REGISTER(decl) \
  scanner_register_typedef(yyget_extra(YYSCAN_PARAM), decl)
#define YYSCAN_SET_TOP(top) scanner_set_top(yyget_extra(YYSCAN_PARAM), top)

void yyerror(yyscan_t, const char *);
void yyscan_parse(YYSCAN_EXTRA);
int yyscan_is_typedef(yyscan_t, const char *);
YYSCAN_TYPE yyscan_json_token(yyscan_t);

#endif /* INCLUDE_GUARD_9CD5F173_4C3F_436C_9085_C797766F802E */
