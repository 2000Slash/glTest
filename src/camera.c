#include "camera.h"
#include <cglm/cam.h>
#include <cglm/vec3.h>

Camera* camera_create() {
    Camera* cam = malloc(sizeof(Camera));
    glm_vec3_zero(cam->pos);
    glm_vec3_zero(cam->target);
    return cam;
}

vec3* camera_direction(Camera* cam) {
    vec3* dir = malloc(sizeof(vec3));
    glm_vec3_sub(cam->target, cam->pos, *dir);
    glm_vec3_norm(*dir);
    return dir;
}

vec3* camera_right(Camera* cam) {
    vec3* right = malloc(sizeof(vec3));
    vec3* dir = camera_direction(cam);
    vec3 up = {0, 1.f, 0};
    glm_vec3_crossn(up, *dir, *right);
    free(dir);
    return right;
}

vec3* camera_up(Camera* cam) {
    vec3* right = camera_right(cam);
    vec3* dir  = camera_direction(cam);
    vec3* up = malloc(sizeof(vec3));
    glm_vec3_crossn(*dir, *right, *up);
    free(right);
    free(dir);
    return up;
}

mat4* camera_view(Camera* cam) {
    mat4* view = malloc(sizeof(mat4));
    vec3* up = camera_up(cam);
    glm_lookat(cam->pos, cam->target, *up, *view);
    free(up);
    return view;
}
