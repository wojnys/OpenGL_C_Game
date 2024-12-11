 #version 450

in vec3 fragmentLocalPosition;

// texturovaci jednodna - ID pro texturu
uniform samplerCube textureUnitID;

out vec4 out_Color;

void main () {
    out_Color = texture(textureUnitID, fragmentLocalPosition);
} 

