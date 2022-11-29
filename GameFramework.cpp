#include "GameFramework.h"

GameFramework::GameFramework()
{
	scene = nullptr;
	player = nullptr;
}

GameFramework::~GameFramework()
{

}

void GameFramework::OnCreate()
{
	BuildObjects();
}

void GameFramework::OnDestroy()
{
	ReleaseObjects();
}

void GameFramework::BuildObjects()
{
	scene = new Scene();
	scene->BuildObjects();

	player = new Player();
	scene->player = player;
}

void GameFramework::ReleaseObjects()
{
	scene->ReleaseObjects();
	delete scene;
}

void GameFramework::ProcessInput()
{

}

void GameFramework::AnimateObjects()
{
	scene->AnimateObjects();
	player->Animate();
}

void GameFramework::Update()
{
	ProcessInput();
	AnimateObjects();
}