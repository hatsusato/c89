#ifndef INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC
#define INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC

#include "sexp.h"

#define PARSER_TAG(sym, ast) sexp_cons(sexp_symbol(#sym), ast)
#define PARSER_TOKEN(sym, scanner) \
  PARSER_TAG(sym, sexp_list1(scanner_token(scanner)))
#define PARSER_LIST_NIL(sym) PARSER_TAG(sym, sexp_nil())
#define PARSER_LIST_ATOM(sym, atom) PARSER_TAG(sym, sexp_list1(atom))
#define PARSER_LIST_PAIR(list, last) sexp_snoc(list, last)

Sexp *parser_sexp_push(Sexp *, Sexp *);

#endif /* INCLUDE_GUARD_CB25BAC5_5782_4FB4_A66E_3FFFB7B099AC */
