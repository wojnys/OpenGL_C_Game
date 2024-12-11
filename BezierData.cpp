#include "BezierData.h"

glm::mat4 A = glm::mat4(
    glm::vec4(-1.0, 3.0, -3.0, 1.0),
    glm::vec4(3.0, -6.0, 3.0, 0.0),
    glm::vec4(-3.0, 3.0, 0.0, 0.0),
    glm::vec4(1.0, 0.0, 0.0, 0.0)
);

glm::mat4x3 B = glm::mat4x3(
    glm::vec3(-1, 0, 0),
    glm::vec3(0, 1, 0),
    glm::vec3(0, -1, 0),
    glm::vec3(1, 0, 0)
);
