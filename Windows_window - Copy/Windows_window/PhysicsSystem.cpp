#include "PhysicsSystem.h"


PhysicsSystem::PhysicsSystem()
{
}


PhysicsSystem::~PhysicsSystem()
{
}


void PhysicsSystem::Update(PhysicsComponent *_component)
{
	if (_component != nullptr)
	{
		_component->Position.x += 1;
	}
}