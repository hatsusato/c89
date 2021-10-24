#ifndef INCLUDE_GUARD_AF5DEE63_3A1E_44DE_B166_B15DCBB95A37
#define INCLUDE_GUARD_AF5DEE63_3A1E_44DE_B166_B15DCBB95A37

struct set;

struct set *set_new(void);
void set_delete(struct set *);
const char *set_find(struct set *, const char *);
const char *set_insert(struct set *, const char *);

#endif /* INCLUDE_GUARD_AF5DEE63_3A1E_44DE_B166_B15DCBB95A37 */
