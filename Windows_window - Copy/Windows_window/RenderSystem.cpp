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
	/*programObject = 0;
	buffers[0] = 0;
	buffers[0] = 0;*/
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

	glGenBuffers(2, buffers);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VERTEX_DATA), VERTEX_DATA, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0u);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INDEX_DATA), INDEX_DATA, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);


	//Setting uniforms

	glUseProgram(programObject);

	GLint uniform_mytexture;
	uniform_mytexture = glGetUniformLocation(programObject, "mytexture");
	glUniform1i(uniform_mytexture, 0);

	//Projection

	projectionIndex = glGetUniformLocation(programObject, "unifProjection");
	assert(projectionIndex != -1);

	//FOV, aspect ratio, Near draw, Far draw
	glm::mat4 projectionTransform = glm::perspective(60.0f, 800.0f / 600.0f, 0.01f, 1000.0f);
	glUniformMatrix4fv(projectionIndex, 1, GL_FALSE, glm::value_ptr(projectionTransform));

	//View
	float Camerarotation = 1;

	viewIndex = glGetUniformLocation(programObject, "unifView");
	assert(viewIndex != -1);

	glm::mat4 viewTransform = glm::translate(glm::vec3(0.0f, 0.0f, -5.0f));
	glUniformMatrix4fv(viewIndex, 1, GL_FALSE, reinterpret_cast<float*>(&viewTransform));

	//World stuff
	rotation = 1;
	worldIndex = glGetUniformLocation(programObject, "unifWorld");
	assert(worldIndex != -1);

	worldTransform = glm::translate(glm::vec3(0.0f, 0.0f, -1.0f));
	glUniformMatrix4fv(worldIndex, 1, GL_FALSE, reinterpret_cast<float*>(&worldTransform));

	glUseProgram(0u);	
}


void RenderSystem::Update(RenderComponent _comp)
{
	glClearColor(0, 1, 0, 0);

	//Create texture
	texture;
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, 4, _comp.width, _comp.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _comp.image.data());
	GLenum glerr = glGetError();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glActiveTexture(GL_TEXTURE0);

	glClear(GL_COLOR_BUFFER_BIT);

	//Draw
	glUseProgram(programObject);

	//World rotation happens here
	rotation += 1.0f;
	worldTransform = glm::mat4(); glm::translate(glm::vec3(0.0f, 0.0f, -5.0f)) ;
	glUniformMatrix4fv(worldIndex, 1, GL_FALSE, reinterpret_cast<float*>(&worldTransform));

	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	//attrib, amount of dimensional attributes, type of atttributes , normalized?, reference, pointer to data
	glVertexAttribPointer(positionIndex, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<GLvoid*>(0));
	glVertexAttribPointer(textureIndex, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<GLvoid*>(8));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glUseProgram(0u);
}