#include "GameObject.h"


GameObject::GameObject()
{}

GameObject::~GameObject()
{
}


bool GameObject::AddComponent(Component* _comp)
{
	for (unsigned int i = 0; i < components.size(); i++)
	{
		if (_comp->type == components[i]->type)
		{
			components[i] = _comp;
			return false;
		}
	}
	components.push_back(_comp);
	return true;
}


void GameObject::RemoveComponent(Component* _comp)
{
	for (std::vector<Component*>::iterator it = components.begin();
		it < components.end(); it++)
	{
		if (_comp->type == (*it)->type)
		{
			components.erase(it);
		}
	}
}