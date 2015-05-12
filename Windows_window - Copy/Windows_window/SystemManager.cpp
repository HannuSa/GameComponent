#include "SystemManager.h"


SystemManager::SystemManager()
{
	VertexData = NULL;
}


SystemManager::~SystemManager()
{
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		delete(objects[i]);
	}
	objects.clear();
}

void SystemManager::AddObject(GameObject* _object)
{
	objects.push_back(_object);
}

void SystemManager::InitGraphics()
{
	render.Initialize();
}

void SystemManager::Update()
{
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		physics.Update(objects[i]->GetComponent<PhysicsComponent>(),render.getVertexData());
		render.Update(objects[i]->GetComponent<RenderComponent>());
	}
}