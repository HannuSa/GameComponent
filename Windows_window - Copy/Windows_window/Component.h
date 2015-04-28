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
	virtual ~Component();

	Type type;
};

