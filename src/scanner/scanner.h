#ifndef INCLUDE_GUARD_29982745_2BB0_454B_9528_9FABEC206FF9
#define INCLUDE_GUARD_29982745_2BB0_454B_9528_9FABEC206FF9

#include "ast/types.h"
#include "scanner/yyscan.h"

yyscan_t scanner_new(void);
void scanner_delete(yyscan_t);
int scanner_parse(yyscan_t);
Ast *scanner_get(yyscan_t);

#endif /* INCLUDE_GUARD_29982745_2BB0_454B_9528_9FABEC206FF9 */
