#pragma once
#include <vector>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <UI/Window.h>
#include <UI/Button.h>
#include <Audio\AudioEngine.h>

class Menu : public GameEngineUI::Window
{
private:
	const char* DEFAULT_BTN_MODEL_NAME = "Models/UI/menuButton.png";
	std::vector<GameEngineUI::Button*> buttons_;
	void Init();
	void handleMouseClick(SDL_Event e);
public:
	Menu(SDL_Window* window);
	void CreateButtons();
	void Run();
	~Menu();
};