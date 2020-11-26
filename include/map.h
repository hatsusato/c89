#ifndef INCLUDE_GUARD_0A0BAD8D_B420_4D3D_B9E5_6504EE1C3925
#define INCLUDE_GUARD_0A0BAD8D_B420_4D3D_B9E5_6504EE1C3925

#include "compare_type.h"
#include "map/map_type.h"
#include "types.h"

Map *map_new(Compare *);
void map_delete(Map *);
void map_insert(Map *, ElemType, ElemType);

#endif /* INCLUDE_GUARD_0A0BAD8D_B420_4D3D_B9E5_6504EE1C3925 */
