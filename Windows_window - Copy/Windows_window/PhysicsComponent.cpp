#include "PhysicsComponent.h"


PhysicsComponent::PhysicsComponent(glm::vec2 _pos) :Component(PHYSICS_COMP)
{
	Position = _pos;
}


PhysicsComponent::~PhysicsComponent()
{
}
