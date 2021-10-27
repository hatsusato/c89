#ifndef INCLUDE_GUARD_CE86B38E_9EFD_4EB5_99FA_CA123C9ACB68
#define INCLUDE_GUARD_CE86B38E_9EFD_4EB5_99FA_CA123C9ACB68

#include "util/type.h"

struct cell;
struct set;

bool_t typedef_contains(const struct cell *);
void typedef_register(const struct cell *, struct set *);

#endif /* INCLUDE_GUARD_CE86B38E_9EFD_4EB5_99FA_CA123C9ACB68 */
