#pragma once
    //const char* vertex_shader =
    //	"#version 330 core\n"
    //	"layout(location=0) in vec3 vp;"
    //	"layout(location=1) in vec3 color;"
    //	"out vec3 fragColor;"
    //	"uniform mat4 transform;"
    //	"void main () {"
    //	"     gl_Position = transform * vec4(vp, 1.0);"
    //	"     fragColor = color;"
    //	"}";


    //const char* fragment_shader =
    //	"#version 330\n"
    //	"in vec3 fragColor;"
    //	"out vec4 frag_colour;"
    //	"void main () {"
    //	"     frag_colour = vec4(fragColor, 1.0);"
    //	"}";

    //const char* vertex_shader =
    //    "#version 330\n"
    //    "uniform mat4 modelMatrix;"
    //    "uniform mat4 projectMatrix;"
    //    "uniform mat4 viewMatrix;"
    //    "out vec3 vertexColor;"
    //    "layout(location=0) in vec3 vp;"
    //    "layout(location=1) in vec3 vn;"
    //    "void main () {"
    //    "     vertexColor=vn;"
    //    "     gl_Position = projectMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);"
    //    "}";


    //const char* fragment_shader =
    //    "#version 330\n"
    //    "out vec4 frag_colour;"
    //    "in vec3 vertexColor;"
    //    "void main () {"
    //    "     frag_colour = vec4(vertexColor, 0.0);"
    //    "}";

    //const char* fragment_shader_red =
    //    "#version 330\n"
    //    "out vec4 frag_colour;"
    //    "in vec3 vertexColor;"
    //    "void main () {"
    //    "     frag_colour = vec4(1.0, 0.0, 0.0, 1.0);"
    //    "}";

    ///////// lambert vertex shader
    //const char* vertex_sh =
    //    "#version 330\n"
    //    "uniform mat4 modelMatrix;"
    //    "uniform mat4 projectMatrix;"
    //    "uniform mat4 viewMatrix;"
    //    "out vec3 vertexColor;"
    //    "out vec4 ex_worldPosition;"
    //    "out vec3 ex_worldNormal;"
    //    "layout(location=0) in vec3 vp;"
    //    "layout(location=1) in vec3 vn;"
    //    "void main () {"
    //    "     vertexColor=vn;"
    //    "     gl_Position = projectMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);"
    //    "      ex_worldPosition = modelMatrix * vec4(vp, 1.0f); "
    //    "}";

    ///////// lambert fragment shader
    //const char* fragment_sh =
    //    "#version 330\n"
    //    "in vec4 ex_worldPosition;"
    //    "in vec3 ex_worldNormal;"
    //    "in vec3 vertexColor;"
    //    "out vec4 out_Color;"
    //    "void main(void) {"
    //    "    vec3 lightPosition = vec3(10.0, 10.0, 10.0);"
    //    "    vec3 lightVector = normalize(lightPosition - vec3(ex_worldPosition));"
    //    "    float dot_product = max(dot(lightVector, normalize(vertexColor)), 0.0);"
    //    "    vec4 diffuse = dot_product * vec4(0.385, 0.647, 0.812, 1.0);"
    //    "    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);"
    //    "    out_Color = ambient + diffuse;"
    //    "}";