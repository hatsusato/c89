#include "visitor.h"

#include "json.h"
#include "type.h"
#include "util/util.h"
#include "vec.h"

void json_visitor_visit(struct json_visitor *self, struct json *json) {
  index_t i, count = json_count(json);
  switch (json->tag) {
  case JSON_TAG_OBJ:
    for (i = 0; i < count; i++) {
      struct json_pair *pair = json_vec_at(json->vec, i);
      if (util_streq(self->key, pair->key)) {
        pair->val = self->callback(self, pair->val);
      } else {
        json_visitor_visit(self, pair->val);
      }
    }
    break;
  case JSON_TAG_ARR:
    for (i = 0; i < count; i++) {
      struct json_pair *pair = json_vec_at(json->vec, i);
      json_visitor_visit(self, pair->val);
    }
    break;
  default:
    break;
  }
}
