#ifndef INCLUDE_GUARD_FC98E9F8_303C_4170_8AFE_2C7622F95044
#define INCLUDE_GUARD_FC98E9F8_303C_4170_8AFE_2C7622F95044

#include "struct.h"
#include "utility.h"

SymbolTable *table_new(void);
void table_delete(SymbolTable *);
void table_push(SymbolTable *);
void table_pop(SymbolTable *);
void table_register(SymbolTable *, const char *, Bool);
Bool table_query(const SymbolTable *, const char *);

#endif /* INCLUDE_GUARD_FC98E9F8_303C_4170_8AFE_2C7622F95044 */
