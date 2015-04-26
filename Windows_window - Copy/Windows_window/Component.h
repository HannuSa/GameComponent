#pragma once

enum Type{
	COMPONENT = 0,
	RENDER_COMP,
	PHYSICS_COMP
};

class Component
{
public:
	Component(Type _type);
	~Component();

	Type type;
};

