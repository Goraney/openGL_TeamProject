#include "Scene.h"

Scene::Scene()
{
	objects = new vector<Object*>;
}

Scene::~Scene()
{

}

void Scene::BuildObjects()
{

}

void Scene::ReleaseObjects()
{

}

void Scene::ProcessInput()
{

}

void Scene::AnimateObjects()
{
	if ((objects) && objects->size() != 0)
	{
		for (int i = 0; i != objects->size(); ++i)
		{
			objects->at(i)->Translate(0.5f);
		}
	}
}