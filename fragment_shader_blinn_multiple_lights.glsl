 #version 330
#define MAX_LIGHTS 3
in vec4 ex_worldPosition;
in vec3 vertexColor;
in vec3 ex_worldNorm;
out vec4 out_Color;

uniform int numLights;
uniform vec3 viewPos;

struct light
{
  vec3 position;
  vec4 color;
};

uniform light lights[MAX_LIGHTS];

void main(void) {
    vec3 result; 

    for (int i = 0; i < MAX_LIGHTS; i++) {       
        vec3 lightDir = normalize(lights[i].position - vec3(ex_worldPosition));

        // Homogenni slozka - 1.0 pro 3D prostor
        float distance = length(vec4(lights[i].position, 1.0f) - ex_worldPosition);
        float constant = 1;          
        float linear = 0.45;          
        float quadratic = 0.07;      
        float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

        float diff = max(dot(lightDir, normalize(ex_worldNorm)), 0.0);
        vec3 diffuse = diff * lights[i].color.rgb;

        diffuse *= attenuation;

        result += diffuse;
    }

    // Ensure the result is clamped between 0 and 1
    result = clamp(result, 0.0, 1.0);

    out_Color = vec4(result, 1.0);
}