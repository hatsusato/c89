#ifndef INCLUDE_GUARD_8FD4DA21_88F9_44C7_9BDC_CEE87486F9A0
#define INCLUDE_GUARD_8FD4DA21_88F9_44C7_9BDC_CEE87486F9A0

struct dict *dict_new(void);
void dict_delete(struct dict *);
void dict_insert(struct dict *, const char *, void *);

#endif /* INCLUDE_GUARD_8FD4DA21_88F9_44C7_9BDC_CEE87486F9A0 */
