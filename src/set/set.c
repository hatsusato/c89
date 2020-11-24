#include "set.h"

#include <stdlib.h>

#include "compare.h"
#include "set/sort.h"
#include "utility.h"
#include "vector.h"

struct struct_Set {
  Vector *data;
  SetCompare cmp;
};

int set_compare(ElemType lhs, ElemType rhs, const void *extra) {
  return ((SetCompare)extra)(&lhs, &rhs);
}

static void set_sort(Set *set) {
  Compare *cmp = compare_new(set_compare);
  ElemType *begin = vector_begin(set->data);
  ElemType *end = vector_end(set->data);
  compare_set_extra(cmp, (CompareExtra)set->cmp);
  quick_sort(begin, end, cmp);
  compare_delete(cmp);
}
static const ElemType *set_search(const Set *set, ElemType key) {
  const ElemType *ret;
  Compare *cmp = compare_new(set_compare);
  ElemType *begin = vector_begin(set->data);
  ElemType *end = vector_end(set->data);
  compare_set_extra(cmp, (CompareExtra)set->cmp);
  ret = binary_search(key, begin, end, cmp);
  compare_delete(cmp);
  return ret;
}

Set *set_new(SetCompare cmp) {
  Set *set = UTILITY_MALLOC(Set);
  set->data = vector_new(NULL);
  set->cmp = cmp;
  return set;
}
void set_delete(Set *set) {
  assert(set);
  vector_delete(set->data);
  UTILITY_FREE(set);
}
ElemType set_insert(Set *set, ElemType elem) {
  const ElemType *found;
  assert(set);
  found = set_find(set, elem);
  if (!found) {
    vector_push(set->data, elem);
    set_sort(set);
    found = &elem;
  }
  return *found;
}
Bool set_contains(const Set *set, ElemType elem) {
  assert(set);
  return set_find(set, elem) != NULL;
}
const ElemType *set_find(const Set *set, ElemType key) {
  assert(set);
  return set_search(set, key);
}
const ElemType *set_begin(const Set *set) {
  assert(set);
  return vector_begin(set->data);
}
const ElemType *set_end(const Set *set) {
  assert(set);
  return vector_end(set->data);
}
