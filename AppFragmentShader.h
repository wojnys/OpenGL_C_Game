// trida bude dedit z SHADER

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"

#pragma once

class AppFragmentShader : public Shader {
public:
	AppFragmentShader(const char* source);
	GLuint getFragmentShaderID() const;

private:
	/*GLuint CompileShader(const std::string& source, unsigned int type);*/
	GLuint fragmentShaderID;

};
