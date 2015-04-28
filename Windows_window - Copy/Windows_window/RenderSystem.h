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

private:
	GLuint programObject;
	GLuint buffers[2];
	GLint positionIndex, textureIndex;
	GLint projectionIndex, viewIndex, worldIndex;
	GLuint texture;
	float rotation;
	glm::mat4 worldTransform;
};

static const GLchar* VERTEX_SOURCE =
"attribute vec2 attrPosition;\n"
"attribute vec2 textCoord;\n"

"uniform mat4 unifProjection;\n"
"uniform mat4 unifView\n;"
"uniform mat4 unifWorld;\n"

"varying vec2 f_textCoord;\n"

"void main()\n"
"{\n"
"	gl_Position = unifProjection * unifView * unifWorld * vec4(attrPosition, 0.0, 1.0);\n"
"	f_textCoord = textCoord;\n"
"}"
;

static const GLchar* FRAGMENT_SOURCE =
"varying vec2 f_textCoord;\n"
"uniform sampler2D mytexture;\n"
"void main()\
{\
	gl_FragColor = texture2D(mytexture, f_textCoord);\
}\
";

static const GLfloat VERTEX_DATA[] =
{
	0.0f, 0.0f, 0.0f, 0.0f, 
	1.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f
};

static const GLint INDEX_DATA[] =
{
	0, 1, 2
};