#include <iostream>

#include <GameEngine/WindowManager.h>

int main(int argc, char **argv)
{
	GameEngine::WindowManager manager;

	manager.create("New Game window", 500, 500);
	return 0;
}