#include "set.h"

#include "compare.h"
#include "set/sort.h"
#include "utility.h"
#include "vector.h"

struct struct_Set {
  Vector *data;
  Compare *cmp;
};

static void set_sort(Set *set) {
  ElemType *begin = vector_begin(set->data);
  ElemType *end = vector_end(set->data);
  quick_sort(begin, end, set->cmp);
}
static const ElemType *set_search(const Set *set, ElemType key) {
  ElemType *begin = vector_begin(set->data);
  ElemType *end = vector_end(set->data);
  return binary_search(key, begin, end, set->cmp);
}

Set *set_new(Compare *cmp) {
  Set *set = UTILITY_MALLOC(Set);
  set->data = vector_new(NULL);
  set->cmp = cmp;
  return set;
}
void set_delete(Set *set) {
  assert(set);
  compare_delete(set->cmp);
  vector_delete(set->data);
  UTILITY_FREE(set);
}
void set_insert(Set *set, ElemType elem) {
  assert(set);
  vector_push(set->data, elem);
  set_sort(set);
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
