#ifndef INCLUDE_GUARD_A22A8A22_8237_41B8_A841_CCF37171764F
#define INCLUDE_GUARD_A22A8A22_8237_41B8_A841_CCF37171764F

struct struct_Node;
typedef struct struct_Node Node;
struct struct_List;
typedef struct struct_List List;

List* list_new(int, void*);
void list_delete(List*);
Node* list_begin(List*);
Node* list_end(List*);
int list_get_tag(Node*);
void* list_get_data(Node*);
void list_insert(Node*, List*);

#endif /* INCLUDE_GUARD_A22A8A22_8237_41B8_A841_CCF37171764F */
