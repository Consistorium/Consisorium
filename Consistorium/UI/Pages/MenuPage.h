#pragma once
#include <vector>

#include "Page.h"
#include "../Button.h"

class MenuPage : public Page
{
private:
	const char* DEFAULT_BTN_MODEL_NAME = "menuButton.png";
	std::vector<Button*> buttons_;
	void Init();
	void handleMouseClick(SDL_Event e);
public:
	MenuPage(SDL_Window* window);
	void CreateButtons();
	void Run();
	~MenuPage();
};