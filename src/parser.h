#ifndef INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC
#define INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC

#include "ast.h"
#include "scanner.h"
#include "sexp.h"

#define PARSER_TAG(sym, ast) sexp_list2(sexp_symbol(#sym), ast)
#define PARSER_TOKEN(sym, scanner) \
  PARSER_TAG(sym, sexp_list1(scanner_token(scanner)))
#define PARSER_LIST_NIL(sym) PARSER_TAG(sym, sexp_nil())
#define PARSER_LIST1(x0) sexp_list1(x0)
#define PARSER_LIST2(x0, x1) sexp_list2(x0, x1)
#define PARSER_LIST3(x0, x1, x2) sexp_list3(x0, x1, x2)
#define PARSER_LIST4(x0, x1, x2, x3) sexp_list4(x0, x1, x2, x3)
#define PARSER_LIST5(x0, x1, x2, x3, x4) sexp_list5(x0, x1, x2, x3, x4)
#define PARSER_LIST6(x0, x1, x2, x3, x4, x5) sexp_list6(x0, x1, x2, x3, x4, x5)

AstList parser_init(void);
AstList parser_token(int, yyscan_t);
AstList parser_append0(int);
AstList parser_append1(int, AstList);
AstList parser_append2(int, AstList, AstList);
AstList parser_append3(int, AstList, AstList, AstList);
AstList parser_append4(int, AstList, AstList, AstList, AstList);
AstList parser_binary(AstList, AstList, AstList);
AstList parser_empty(void);
AstList parser_list_empty(int);
AstList parser_list_new(int, AstList);
AstList parser_list_push(AstList, AstList);
AstList parser_list_finish(AstList);
List *parser_consume(List *);
Sexp *parser_sexp_push(Sexp *, Sexp *);

#endif /* INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC */
