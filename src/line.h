#include "cglm/types.h"
#include "model.h"

typedef struct Line {
    unsigned int vao, vbo;
} Line;

Line* line_create(vec3* start, vec3* end);
void line_render(Line* line, int shader);
