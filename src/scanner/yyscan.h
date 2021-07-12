#ifndef INCLUDE_GUARD_9CD5F173_4C3F_436C_9085_C797766F802E
#define INCLUDE_GUARD_9CD5F173_4C3F_436C_9085_C797766F802E

#include "yyscan_t.h"

#define YYSCAN_SYMBOL() yyscan_symbol(YYSCAN_PARAM)
#define YYSCAN_PUSH(xs, x) yyscan_push(YYSCAN_PARAM, xs, x)
#define YYSCAN_PUSH_SYMBOL(xs) YYSCAN_PUSH(xs, YYSCAN_SYMBOL())
#define YYSCAN_TOKEN(token) yyscan_token(YYSCAN_PARAM, #token)
#define YYSCAN_TAG(token) YYSCAN_PUSH(yyscan_nil(), YYSCAN_TOKEN(token))

void yyerror(yyscan_t, const char *);
yyscan_t yyscan_new(struct scanner *);
void yyscan_delete(yyscan_t);
int yyscan_parse(yyscan_t);
int yyscan_is_typedef(yyscan_t, const char *);
void yyscan_set_ast(yyscan_t, const struct cell *);
const struct cell *yyscan_nil(void);
const struct cell *yyscan_symbol(yyscan_t);
const struct cell *yyscan_token(yyscan_t, const char *);
const struct cell *yyscan_pair(yyscan_t, const struct cell *,
                               const struct cell *);
const struct cell *yyscan_push(yyscan_t, const struct cell *,
                               const struct cell *);

#endif /* INCLUDE_GUARD_9CD5F173_4C3F_436C_9085_C797766F802E */
