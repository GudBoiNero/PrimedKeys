#version 330 core


uniform sampler2D textureSampler;
uniform vec2 texCoords;

void main() {
    vec4 color = texture(textureSampler, texCoords);
}