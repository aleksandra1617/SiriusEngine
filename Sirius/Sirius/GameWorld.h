#pragma once

class Renderer;

enum class GameState { INIT, LOAD, PLAY, SAVE, CLOSE };

class GameWorld
{
public:
	GameWorld();
	~GameWorld();

	void InitSystems();
	void Update();
	void EndWorld();

private:
	GameState _gameState;
	Renderer* _renderer;
};

