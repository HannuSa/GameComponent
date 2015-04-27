#include "GameObject.h"

GameObject::GameObject()
{}

GameObject::~GameObject()
{
}


void GameObject::AddComponent(Component* _component)
{
	_components.insert(std::make_pair(&typeid(*_component), _component));
}


void GameObject::RemoveComponent(Component* _comp)
{
	ComponentMap::iterator position =_components.find(&typeid(_comp));
	if (position != _components.end())
	{
		_components.erase(position);
	}
}