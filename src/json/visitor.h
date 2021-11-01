#ifndef INCLUDE_GUARD_BAC01668_22C9_47DA_ACA9_033FC7005651
#define INCLUDE_GUARD_BAC01668_22C9_47DA_ACA9_033FC7005651

struct json;

typedef void (*json_visitor_t)(struct json *, void *);

void json_visitor_visit(json_visitor_t, const char *, struct json *, void *);

#endif /* INCLUDE_GUARD_BAC01668_22C9_47DA_ACA9_033FC7005651 */
