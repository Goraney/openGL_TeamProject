#pragma once
#include "Scene.h"

class GameFramework
{
public:
	GameFramework();
	~GameFramework();

	void OnCreate();
	void OnDestroy();

	void BuildObjects();
	void ReleaseObjects();

	void ProcessInput();
	void AnimateObjects();

	void AddObject();

	void Update();

public:
	Scene* scene;
	Player* player;
	
};

