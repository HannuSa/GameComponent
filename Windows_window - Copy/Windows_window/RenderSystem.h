#pragma once
#include "System.h"
#include "RenderComponent.h"
class RenderSystem :
	public System
{
public:
	RenderSystem();
	~RenderSystem();
	void Update(RenderComponent _component);
};

