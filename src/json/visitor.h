#ifndef INCLUDE_GUARD_BAC01668_22C9_47DA_ACA9_033FC7005651
#define INCLUDE_GUARD_BAC01668_22C9_47DA_ACA9_033FC7005651

struct json;
struct json_visitor2;

typedef void (*json_visitor_t)(struct json *, void *);
typedef void (*json_visitor2_t)(struct json_visitor2 *, struct json *);

struct json_visitor2 {
  json_visitor2_t visitor;
  void *extra;
};

void json_visitor_visit(json_visitor_t, const char *, struct json *, void *);
void json_visitor2_visit(struct json_visitor2 *, struct json *);

#endif /* INCLUDE_GUARD_BAC01668_22C9_47DA_ACA9_033FC7005651 */
