#ifndef INCLUDE_GUARD_A84E9F8A_C152_4807_9181_80EE16B4DFA5
#define INCLUDE_GUARD_A84E9F8A_C152_4807_9181_80EE16B4DFA5

#include "sexp_type.h"
#include "types.h"

struct struct_Ast;
typedef struct struct_Ast Ast;

typedef enum {
  AST_NULL,
#define HANDLE(name, str) name,
#include "enum/keyword.def"
#
#include "enum/token.def"
#
#include "enum/symbol.def"
#
#include "enum/expression.def"
#
#include "enum/declaration.def"
#
#include "enum/statement.def"
#
#include "enum/definition.def"
#undef HANDLE
  AST_TAG_COUNT
} AstTag;

Ast *ast_new(void);
void ast_delete(Ast *);
const char *ast_symbol(Ast *, const char *, Size);
const char *ast_show(AstTag);
AstTag ast_tag(Sexp *);

#endif /* INCLUDE_GUARD_A84E9F8A_C152_4807_9181_80EE16B4DFA5 */
