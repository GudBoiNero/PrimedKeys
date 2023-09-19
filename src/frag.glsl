#version 330 core

uniform sampler2D textureSampler;
in vec2 uvCoord;


void main() {
    vec4 color = texture(textureSampler, uvCoord);
    // 'color' now contains the RGB values of the texture at the specified UV coordinates
    // You can access individual components like color.r, color.g, color.b
    // Do further processing as needed.
}