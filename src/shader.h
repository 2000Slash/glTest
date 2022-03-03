#include <cglm/mat4.h>

int shader_create(char* fragment_name);
void shader_bind_mat4(int program, mat4 mat, char* name);
void shader_bind_float(int program, float value, char* name);
