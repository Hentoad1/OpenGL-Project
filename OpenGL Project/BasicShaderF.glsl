#version 330 core
out vec4 FragColor;

in vec3 Color; // the input variable from the vertex shader (same name and same type)  

void main()
{
    FragColor = vec4(Color, 1.0f);
}