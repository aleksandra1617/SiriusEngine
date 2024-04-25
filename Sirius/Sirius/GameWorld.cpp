#include "GameWorld.h"

#include <iostream>
#include "Graphics/Renderer.h"
#include "Input/Input.h"

GameWorld::GameWorld()
{
	_renderer = new Renderer();
	_input = new Input();

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

	std::cout << "<GameWorld::InitSystems> Initializing systems complete." << std::endl;
}

void GameWorld::ProcessInput()
{
	while (_gameState != GameState::CLOSE && !_renderer->IsWindowClosing())
	{
		_input->ProcessInput(_renderer->GetMainWindow());
		_renderer->Render();
	}
}

void GameWorld::EndWorld()
{
	_renderer->Cleanup();
}

