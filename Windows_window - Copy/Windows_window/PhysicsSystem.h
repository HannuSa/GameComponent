#pragma once

#include "GL/glew.h"

#include "System.h"
#include "PhysicsComponent.h"

class PhysicsSystem :
	public System
{
public:
	PhysicsSystem();
	~PhysicsSystem();
	void Update(PhysicsComponent* _component);
	void Update(PhysicsComponent* _component, GLfloat* vertexData);
};

