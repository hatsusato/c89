#ifndef INCLUDE_GUARD_A22A8A22_8237_41B8_A841_CCF37171764F
#define INCLUDE_GUARD_A22A8A22_8237_41B8_A841_CCF37171764F

struct struct_List;
typedef struct struct_List List;

List *list_new(int, void *);
void list_delete(List *);
int list_tag(List *);
void *list_data(List *);

#endif /* INCLUDE_GUARD_A22A8A22_8237_41B8_A841_CCF37171764F */
