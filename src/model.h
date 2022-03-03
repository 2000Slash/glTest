#ifndef MODEL
#define MODEL

typedef struct Model {
    unsigned int vao, ebo, vbo;
    int nvertices;
} Model;

Model* model_create(float vertices[], int nvertices, unsigned int indices[], int nindices);
void model_bind(Model* model);
void model_render(Model* model);
void model_free(Model* model);

#endif
