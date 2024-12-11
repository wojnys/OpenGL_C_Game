#pragma once 

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "EventType.h"
class Camera;

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(EventType eventType, const void* data) = 0;

};
