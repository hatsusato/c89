#ifndef INCLUDE_GUARD_06236191_5488_4569_8D7C_EE618E9BD306
#define INCLUDE_GUARD_06236191_5488_4569_8D7C_EE618E9BD306

#include "ast/tag.h"
#include "utility/types.h"

Sexp *convert_list(Sexp *);
Sexp *convert_cons_tag(SyntaxTag, Sexp *);
Sexp *convert_ast(Sexp *);

#endif /* INCLUDE_GUARD_06236191_5488_4569_8D7C_EE618E9BD306 */
