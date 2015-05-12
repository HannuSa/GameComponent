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

void PhysicsSystem::Update(PhysicsComponent* _component, GLfloat* vertexData)
{
	if (_component != nullptr)
	{
		_component->Position.x += 1;

		vertexData[0] = _component->Position.x;
		vertexData[4] = _component->Position.x;
		vertexData[8] = _component->Position.x+100;
		vertexData[12]= _component->Position.x+100;

		//_component->Position.y = 200;
		
		//If uncommented, wont draw anything
		/*vertexData[1] = _component->Position.y;
		vertexData[5] = _component->Position.y;
		vertexData[9] = _component->Position.y + 100;
		vertexData[13] = _component->Position.y + 100;*/
		
	}
}