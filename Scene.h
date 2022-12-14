#pragma once
#include "Object.h"

class Scene
{
public:
	Scene();
	~Scene();

	void BuildObjects();
	void ReleaseObjects();

	void ProcessInput();
	void AnimateObjects();

public:
	Player* player;
	vector<Object*>* objects;
};

