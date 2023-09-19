#version 330 core

out vec4 FragColor; 

vec2 texCoords = {0.0, 0.0};
uniform sampler2D textureSampler;

void main() {
    vec4 color = texture(textureSampler, texCoords);

    FragColor = color;
}