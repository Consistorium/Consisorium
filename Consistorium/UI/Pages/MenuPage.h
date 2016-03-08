#pragma once
#include <vector>

#include "IPage.h"
#include "../Button.h"

class MenuPage : public IPage
{
private:
	const char* DEFAULT_BTN_MODEL_NAME = "menuButton.png";
	std::vector<Button*> buttons_;
	SDL_Window* window_;
	SDL_Surface* windowSurface_;

	void Init();
public:
	MenuPage(SDL_Window* window);
	void CreateButtons();
	void Run();
	~MenuPage();
};