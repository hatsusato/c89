#ifndef INCLUDE_GUARD_9CD5F173_4C3F_436C_9085_C797766F802E
#define INCLUDE_GUARD_9CD5F173_4C3F_436C_9085_C797766F802E

#include "yyscan_t.h"

void yyerror(yyscan_t, const char *);
yyscan_t yyscan_new(struct scanner *);
void yyscan_delete(yyscan_t);
int yyscan_parse(yyscan_t);
int yyscan_is_typedef(yyscan_t, const char *);
const struct cell *yyscan_nil(void);
const struct cell *yyscan_token(yyscan_t, const char *);
const struct cell *yyscan_pair(yyscan_t, const struct cell *,
                               const struct cell *);

#endif /* INCLUDE_GUARD_9CD5F173_4C3F_436C_9085_C797766F802E */
