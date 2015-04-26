#pragma once

#include <vector>
#include "Component.h"

class GameObject
{
public:
	GameObject();
	~GameObject();
	bool AddComponent(Component* _comp);
	void RemoveComponent(Component* _comp);

	std::vector<Component*> components;
};