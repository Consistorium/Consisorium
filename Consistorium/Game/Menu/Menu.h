#pragma once
#include <vector>

#include "../Page.h"
#include "../UI/Button.h"

class Menu : public Page
{
private:
	const char* DEFAULT_BTN_MODEL_NAME = "menuButton.png";
	std::vector<Button*> buttons_;
	void Init();
	void handleMouseClick(SDL_Event e);
public:
	Menu(SDL_Window* window);
	void CreateButtons();
	void Run();
	~Menu();
};