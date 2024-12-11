#include "AppVertexShader.h"
#include <cstddef>

AppVertexShader::AppVertexShader(const char* source) {

	this->vertexShaderID = compileShader(source, GL_VERTEX_SHADER);
}

GLuint AppVertexShader::getVertexShaderID() const
{
	return this->vertexShaderID;
}



