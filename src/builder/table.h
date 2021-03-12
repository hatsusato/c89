#ifndef INCLUDE_GUARD_CA82BAF1_F8AF_418B_A275_3129D9D3F1FB
#define INCLUDE_GUARD_CA82BAF1_F8AF_418B_A275_3129D9D3F1FB

#include "module.h"

struct struct_Table;
typedef struct struct_Table Table;

Table *table_new(void);
void table_delete(Table *);
void table_clear(Table *);
void table_push(Table *);
void table_pop(Table *);
void table_insert_global(Table *, const char *, Global *);
void table_insert_local(Table *, const char *, Instruction *);
Value *table_find(Table *, const char *, Module *);
void table_label_insert(Table *, const char *, Block *);
Block *table_label_find(Table *, const char *);

#endif /* INCLUDE_GUARD_CA82BAF1_F8AF_418B_A275_3129D9D3F1FB */
