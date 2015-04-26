#pragma once

#include "System.h"
#include "PhysicsComponent.h"

class PhysicsSystem :
	public System
{
public:
	PhysicsSystem();
	~PhysicsSystem();
	void Update(PhysicsComponent _component);
};

