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
	std::vector<GameObject*> objects;

private:
	PhysicsSystem physics;
	RenderSystem render;
	GLfloat* VertexData;
};

