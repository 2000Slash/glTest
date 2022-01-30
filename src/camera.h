#include <cglm/types.h>
#include <stdlib.h>
#include <cglm/cglm.h>
#include <cglm/vec3.h>
#include <cglm/mat4.h>

typedef struct Camera {
    vec3 pos;
    vec3 target;
} Camera;

Camera* camera_create();
vec3* camera_direction(Camera* cam);
vec3* camera_right(Camera* cam);
vec3* camera_up(Camera* cam);
mat4* camera_view(Camera* cam);
