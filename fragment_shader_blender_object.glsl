#version 450

in vec2 uv;

uniform sampler2D textureUnitID;

out vec4 out_Color;

void main () {
    out_Color = texture(textureUnitID, uv);
}

