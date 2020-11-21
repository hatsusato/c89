#ifndef INCLUDE_GUARD_DD5D0935_0DD4_46BA_8D0E_560243A08759
#define INCLUDE_GUARD_DD5D0935_0DD4_46BA_8D0E_560243A08759

#include "sexp_type.h"
#include "symbol.h"
#include "table_type.h"
#include "types.h"

Table *table_new(void);
void table_delete(Table *);
void table_push(Table *);
void table_pop(Table *);
Bool table_query(Table *, const char *);
SymbolSet *table_top(Table *);

#endif /* INCLUDE_GUARD_DD5D0935_0DD4_46BA_8D0E_560243A08759 */
