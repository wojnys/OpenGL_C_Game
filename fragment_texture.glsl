#version 450

in vec2 vt_out;

// texturovaci jednodna - ID pro texturu
uniform sampler2D textureUnitID;

out vec4 out_Color;

void main () {
    out_Color = texture(textureUnitID, vt_out);
}

