#pragma once

#include <vector>
#include "System.h"
#include "PhysicsSystem.h"
#include "RenderSystem.h"
#include "GameObject.h"

class SystemManager
{
public:
	SystemManager();
	~SystemManager();

	void AddObject(GameObject* _object);
	void InitGraphics();
	void Update();

private:
	PhysicsSystem physics;
	RenderSystem render;
	std::vector<GameObject*> objects;
	GLfloat* VertexData;
};

