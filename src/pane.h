#include "cglm/types.h"
#include "model.h"

typedef struct Pane {
    vec3 position;
} Pane;

Pane* pane_create();
void pane_render(Pane* block, int shader);
Model* pane_model();
