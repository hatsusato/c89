#ifndef INCLUDE_GUARD_9DB08462_C244_4BCE_B291_9362A493469F
#define INCLUDE_GUARD_9DB08462_C244_4BCE_B291_9362A493469F

#include "scanner/yyscan_t.h"
#include "utility/types.h"

void scanner_register(yyscan_t, const char *);
Bool scanner_query(yyscan_t, const char *);

#endif /* INCLUDE_GUARD_9DB08462_C244_4BCE_B291_9362A493469F */
