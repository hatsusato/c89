#ifndef INCLUDE_GUARD_0A0BAD8D_B420_4D3D_B9E5_6504EE1C3925
#define INCLUDE_GUARD_0A0BAD8D_B420_4D3D_B9E5_6504EE1C3925

#include "compare/type.h"
#include "map/type.h"
#include "types.h"

Map *map_new(Compare *);
void map_delete(Map *);
void map_insert(Map *, ElemType, ElemType);
ElemType *map_find(Map *, ElemType);
Bool map_contains(const Map *, ElemType);

#endif /* INCLUDE_GUARD_0A0BAD8D_B420_4D3D_B9E5_6504EE1C3925 */
