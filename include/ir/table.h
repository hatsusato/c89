#ifndef INCLUDE_GUARD_CA82BAF1_F8AF_418B_A275_3129D9D3F1FB
#define INCLUDE_GUARD_CA82BAF1_F8AF_418B_A275_3129D9D3F1FB

#include "ir/table_type.h"
#include "ir/value_type.h"
#include "sexp_type.h"

Table *table_new(void);
void table_delete(Table *);
void table_insert(Table *, Sexp *, Value *);
Value *table_find(Table *, Sexp *);

#endif /* INCLUDE_GUARD_CA82BAF1_F8AF_418B_A275_3129D9D3F1FB */
