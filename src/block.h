#include "cglm/types.h"
#include "model.h"

typedef struct Block {
    vec3 position;
} Block;

Block* block_create();
void block_render(Block* block, int shader);
Model* block_model();
