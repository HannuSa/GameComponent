#pragma once
#include "Component.h"
#include "glm\vec2.hpp"

class PhysicsComponent:
	public Component
{
public:
	PhysicsComponent(glm::vec2 _pos);
	~PhysicsComponent();
	glm::vec2 Position;
};

