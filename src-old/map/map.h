#ifndef INCLUDE_GUARD_0A0BAD8D_B420_4D3D_B9E5_6504EE1C3925
#define INCLUDE_GUARD_0A0BAD8D_B420_4D3D_B9E5_6504EE1C3925

#include "map/typedef.h"
#include "utility/types.h"

Map *map_new(void);
void map_delete(Map *);
void map_clear(Map *);
void map_insert(Map *, const char *, MapElem);
MapElem map_find(Map *, const char *);

#endif /* INCLUDE_GUARD_0A0BAD8D_B420_4D3D_B9E5_6504EE1C3925 */
