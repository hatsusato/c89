#ifndef INCLUDE_GUARD_CA82BAF1_F8AF_418B_A275_3129D9D3F1FB
#define INCLUDE_GUARD_CA82BAF1_F8AF_418B_A275_3129D9D3F1FB

#include "ir/block/type.h"
#include "ir/table_type.h"
#include "ir/value/type.h"
#include "sexp_type.h"
#include "types.h"

Table *table_new(void);
void table_delete(Table *);
void table_insert(Table *, const char *, Value *);
Value *table_find(Table *, const char *);
Bool table_label_contains(Table *, const char *);
void table_label_insert(Table *, const char *, Block *);
Block *table_label_find(Table *, const char *);

#endif /* INCLUDE_GUARD_CA82BAF1_F8AF_418B_A275_3129D9D3F1FB */
