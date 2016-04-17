#pragma once
#include <vector>

#include "SDL/SDL.h"
#include "UI/Window.h"
#include "UI/Button.h"

class Menu : public GameEngine::Window
{
private:
	const char* DEFAULT_BTN_MODEL_NAME = "Models/UI/menuButton.png";
	std::vector<GameEngine::Button*> buttons_;

	void Init() override;

	void handleMouseClick(SDL_Event e);
public:
	Menu(SDL_Window* window);

	void CreateButtons();

	void Run() override;
};