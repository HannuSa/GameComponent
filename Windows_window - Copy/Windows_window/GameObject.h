#pragma once

#include <typeinfo>
#include <unordered_map>
#include <vector>
#include "Component.h"

class GameObject
{
public:
	GameObject();
	~GameObject();
	void AddComponent(Component* _comp);

	template<typename T>
	T* GetComponent();
	void RemoveComponent(Component* _comp);

	std::vector<Component*> components;
private:
	using ComponentMap = std::unordered_map<const std::type_info*, Component*>;

	ComponentMap _components;
};

template<typename T>
T* GameObject::GetComponent()
{
	ComponentMap::const_iterator position = _components.find(&typeid(T));

	if (position == _components.end())
	{
		return nullptr;
	}
	else
		return static_cast<T*>(position->second);
}