#include "AppFragmentShader.h"

AppFragmentShader::AppFragmentShader(const char* source) {
	//Shader(source, GL_FRAGMENT_SHADER);
	//this->fragmentShaderID = CompileShader(source, GL_FRAGMENT_SHADER);
	
	// nove
	this->fragmentShaderID = compileShader(source, GL_FRAGMENT_SHADER);
}


GLuint AppFragmentShader::getFragmentShaderID() const
{
	return this->fragmentShaderID;
}


