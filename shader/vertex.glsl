#version 330 core
// Vertex position (usually constant)
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

// Sprite position
uniform vec2 pos;

out vec2 texCoord;

void main() {
    const vec2 OFFSET = vec2(-1.f, -1.f);

    gl_Position = vec4(aPos.xy + pos.xy + OFFSET, 0.0f, 1.0f);

    texCoord = aTexCoord;
}