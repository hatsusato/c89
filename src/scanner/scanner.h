#ifndef INCLUDE_GUARD_29982745_2BB0_454B_9528_9FABEC206FF9
#define INCLUDE_GUARD_29982745_2BB0_454B_9528_9FABEC206FF9

#include "scanner/yyscan.h"
#include "utility/types.h"

Scanner *scanner_new(void);
void scanner_delete(Scanner *);
int scanner_parse(yyscan_t);
Ast *scanner_get(yyscan_t);
yyscan_t scanner_yyscan(Scanner *);

#endif /* INCLUDE_GUARD_29982745_2BB0_454B_9528_9FABEC206FF9 */
