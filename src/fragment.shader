#version 330 core
out vec4 FragColor;
in vec4 pos;

void main()
{
    FragColor = vec4(pos.x/0.5f, pos.y/0.5f, pos.x/0.5f, 1.0f);
}
