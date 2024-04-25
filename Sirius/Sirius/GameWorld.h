#pragma once

class Renderer;
class Input;

enum class GameState { INIT, LOAD, PLAY, SAVE, CLOSE };

class GameWorld
{
public:
	GameWorld();
	~GameWorld();

	void InitSystems();
	void ProcessInput();
	void EndWorld();

private:
	GameState _gameState;
	Renderer* _renderer;
	Input* _input;
};

