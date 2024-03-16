#version 330 core
out vec4 FragColor;

in vec3 Color; // the input variable from the vertex shader (same name and same type)  
in vec2 Tex; // the input variable from the vertex shader (same name and same type)  

uniform sampler2D ourTexture;

void main()
{
    //FragColor = vec4(Color, 1.0f);
    FragColor = texture(ourTexture, Tex);
}