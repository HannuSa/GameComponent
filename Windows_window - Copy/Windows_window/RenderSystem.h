#pragma once
#include "System.h"
#include "RenderComponent.h"
#include "GL/glew.h"
#include "glm/glm.hpp"

class RenderSystem :
	public System
{
public:
	RenderSystem();
	~RenderSystem();
	void Initialize();
	void ErrorMessage(std::string error);
	void CheckShaderErrors(GLuint shader);
	void Update(RenderComponent* _component);
	GLfloat* getVertexData();
private:
	GLuint programObject;
	GLuint buffers[4];
	GLint positionIndex, textureIndex;
	GLint projectionIndex, viewIndex, worldIndex;
	GLuint texture;
	GLint uniform_mytexture;
	float rotation;
	glm::mat4 worldTransform;
	GLfloat VERTEX_DATA[16];
};
