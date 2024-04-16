#include "GameWorld.h"

#include "Graphics/Renderer.h"

GameWorld::GameWorld()
{
	_renderer = new Renderer();

	_gameState = GameState::INIT;
}

GameWorld::~GameWorld()
{
	delete _renderer;
}

void GameWorld::InitSystems()
{
	if (!_renderer->Init()) 
	{
		_gameState = GameState::CLOSE;
	}
}

void GameWorld::Update()
{
	while (_gameState != GameState::CLOSE && !_renderer->IsWindowClosing())
	{
		_renderer->Update();
	}
}

void GameWorld::EndWorld()
{
	_renderer->EndRender();
}

