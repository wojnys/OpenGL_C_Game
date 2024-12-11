// nadrazena trida -> 
	// z teto tridy budou dedit VERTEX_SHADER A FRAGMENT_SHADER

#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

class Shader {
	public:
		Shader();

	protected:
		GLuint compileShader(const std::string& source, GLenum type);
};

#endif