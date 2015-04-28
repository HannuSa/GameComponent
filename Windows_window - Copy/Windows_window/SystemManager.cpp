#include "SystemManager.h"


SystemManager::SystemManager()
{
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

void SystemManager::Update()
{
	PhysicsComponent* comp;
	objects[0]->GetComponent<PhysicsComponent>();
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		physics.Update(*objects[i]->GetComponent<PhysicsComponent>());
		render.Update(*objects[i]->GetComponent<RenderComponent>());
	}
}