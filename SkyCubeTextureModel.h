#pragma once

#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CompositeTransformation.h"
#include "ModelBase.h"

// virtualni trida AbstractModel (zde budou spolecne metody)
//	s teto tridy bude dedit Model a TextureModel
class SkyCubeTextureModel : public ModelBase
{
public:
	SkyCubeTextureModel(const float points[], size_t size, GLenum shapeType, int first, int count);
	~SkyCubeTextureModel();
	void bind();
	void unbind();

	GLenum getShapeType() const;
	int getFirst() const;
	int getCount() const;


private:
	GLuint VBO, VAO;

	GLenum shapeType;
	int first;
	int count;
};


