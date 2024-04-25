// main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>

#include "GameWorld.h"

int main()
{
	GameWorld* world = new GameWorld();
	world->InitSystems();
	world->ProcessInput();

	return 0;
}