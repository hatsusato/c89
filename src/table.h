#ifndef INCLUDE_GUARD_FC98E9F8_303C_4170_8AFE_2C7622F95044
#define INCLUDE_GUARD_FC98E9F8_303C_4170_8AFE_2C7622F95044

struct struct_SymbolTable;
typedef struct struct_SymbolTable SymbolTable;

SymbolTable *table_new(void);
void table_delete(SymbolTable *);
void table_push(SymbolTable *);
void table_pop(SymbolTable *);

#endif /* INCLUDE_GUARD_FC98E9F8_303C_4170_8AFE_2C7622F95044 */
