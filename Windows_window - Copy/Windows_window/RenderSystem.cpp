#include "RenderSystem.h"

#include <Windows.h>
#include "GL/glew.h"
#include "GL/wglew.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp">


RenderSystem::RenderSystem()
{
	//It works but it aint pretty
	VERTEX_DATA[0] = 300;
	VERTEX_DATA[1] = 200;
	VERTEX_DATA[2] = 0;
	VERTEX_DATA[3] = 1;

	VERTEX_DATA[4] = 300;
	VERTEX_DATA[5] = 400;
	VERTEX_DATA[6] = 0;
	VERTEX_DATA[7] = 0;

	VERTEX_DATA[8] = 600;
	VERTEX_DATA[9] = 400;
	VERTEX_DATA[10] = 1;
	VERTEX_DATA[11] = 0;

	VERTEX_DATA[12] = 600;
	VERTEX_DATA[13] = 200;
	VERTEX_DATA[14] = 1;
	VERTEX_DATA[15] = 1;
}

GLfloat* RenderSystem::getVertexData()
{
	return VERTEX_DATA;
}

RenderSystem::~RenderSystem()
{
	//Delete texture
	glDeleteTextures(1, &texture);

	//Destroy buffers
	glDeleteBuffers(2, buffers);
}

void RenderSystem::ErrorMessage(std::string error)
{
	MessageBoxA(0, error.c_str(), "Error in Code", 0);
}

void RenderSystem::CheckShaderErrors(GLuint shader)
{
	GLint result;
	int logLength;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
	char errorMsg[1200] = "\n";
	glGetShaderInfoLog(shader, logLength, NULL, errorMsg);
	ErrorMessage(std::string(errorMsg));
}

void RenderSystem::Initialize()
{
	static const GLchar* VERTEX_SOURCE =
		"attribute vec2 attrPosition;\n"
		"attribute vec2 textCoord;\n"

		"uniform mat4 unifProjection;\n"

		"varying vec2 f_textCoord;\n"

		"void main()\n"
		"{\n"
		"	gl_Position = unifProjection * vec4(attrPosition, 0.0, 1.0);\n"
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

	static const GLint INDEX_DATA[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	//OpenGl and shader stuff

	GLenum err = glewInit();
	const int r = wglSwapIntervalEXT(1);
	assert(r != 0);

	//Create shaders
	programObject = glCreateProgram();

	GLuint vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShaderObject, 1u, &VERTEX_SOURCE, NULL);

	glShaderSource(fragmentShaderObject, 1u, &FRAGMENT_SOURCE, NULL);

	GLint vertexCompileSuccess;
	glCompileShader(vertexShaderObject);
	glGetShaderiv(vertexShaderObject, GL_COMPILE_STATUS, &vertexCompileSuccess);
	if (vertexCompileSuccess != GL_TRUE)
	{
		CheckShaderErrors(vertexShaderObject);
		ErrorMessage("Vertex compile failed");
	}

	GLint fragmentCompileSuccess;
	glCompileShader(fragmentShaderObject);
	glGetShaderiv(fragmentShaderObject, GL_COMPILE_STATUS, &fragmentCompileSuccess);
	if (fragmentCompileSuccess != GL_TRUE)
	{
		CheckShaderErrors(fragmentShaderObject);
		ErrorMessage("Fragment compile failed");
	}

	glAttachShader(programObject, vertexShaderObject);
	glAttachShader(programObject, fragmentShaderObject);

	glLinkProgram(programObject);

	GLint LinkSuccess;
	glGetProgramiv(programObject, GL_LINK_STATUS, &LinkSuccess);

	if (LinkSuccess != GL_TRUE)
	{
		ErrorMessage("Linking failed");
	}

	//Enable attribute array

	positionIndex = glGetAttribLocation(programObject, "attrPosition");
	assert(positionIndex >= 0);
	glEnableVertexAttribArray(positionIndex);

	
	textureIndex = glGetAttribLocation(programObject, "textCoord");
	assert(textureIndex >= 0);
	glEnableVertexAttribArray(textureIndex);
	

	//Create vertex and index buffers

	glGenBuffers(4, buffers);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VERTEX_DATA), VERTEX_DATA, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0u);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INDEX_DATA), INDEX_DATA, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);

	//Setting uniforms

	glUseProgram(programObject);

	//Projection

	projectionIndex = glGetUniformLocation(programObject, "unifProjection");
	assert(projectionIndex != -1);

	glm::mat4 projectionTransform = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f);
	glUniformMatrix4fv(projectionIndex, 1, GL_FALSE, glm::value_ptr(projectionTransform));

	glUseProgram(0u);	
}


void RenderSystem::Update(RenderComponent* _comp)
{
	
	if (_comp != nullptr)
	{
		glClearColor(0, 1, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VERTEX_DATA), VERTEX_DATA, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0u);
		glUseProgram(programObject);

		//Create texture
		glGenTextures(1, &texture);

		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _comp->width, _comp->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _comp->image.data());
		GLenum glerr = glGetError();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		uniform_mytexture = glGetUniformLocation(programObject, "mytexture");

		glUniform1i(uniform_mytexture, 0);

		glActiveTexture(GL_TEXTURE0);

		//Draw
		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		//attrib, amount of dimensional attributes, type of atttributes , normalized?, reference, pointer to data
		glVertexAttribPointer(positionIndex, 2, GL_FLOAT, GL_FALSE, 16, reinterpret_cast<GLvoid*>(0));
		glVertexAttribPointer(textureIndex, 2, GL_FLOAT, GL_FALSE, 16, reinterpret_cast<GLvoid*>(8));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindTexture(GL_TEXTURE_2D, texture);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(0));
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glUseProgram(0u);
	}
}