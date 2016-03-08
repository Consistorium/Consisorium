#include <iostream>
#include <SDL_ttf.h>

#include "MenuPage.h"
#include "GamePage.h"

void* startButtonClickHandler(SDL_Window*  window)
{
	GamePage gamePage(window);
	gamePage.Run();
	return nullptr;
}

MenuPage::MenuPage(SDL_Window * window)
	:Page(window)
{

}

void MenuPage::CreateButtons()
{
	auto startButton = new Button(50, 150, DEFAULT_BTN_MODEL_NAME, "Start Game");
	startButton->setOnClick(&startButtonClickHandler);
	auto tutorialButton = new Button(50, 250, DEFAULT_BTN_MODEL_NAME, "Tutorial");
	auto exitButton = new Button(50, 350, DEFAULT_BTN_MODEL_NAME, "Exit");

	buttons_.push_back(startButton);
	buttons_.push_back(tutorialButton);
	buttons_.push_back(exitButton);
}

void MenuPage::Init()
{
	// Initialize SDL_ttf library
	if (TTF_Init() != 0)
	{
		std::cerr << "TTF_Init() Failed: " << TTF_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}

	CreateButtons();
}

void MenuPage::Run()
{
	Init();

	while (true)
	{
		for (size_t i = 0; i < buttons_.size(); i++)
		{
			SDL_BlitSurface(buttons_[i]->getModel(), &buttons_[i]->getModel()->clip_rect, windowSurface_, &buttons_[i]->getBounds());

			// Load a font
			TTF_Font *font;
			font = TTF_OpenFont("FreeSans.ttf", 24);
			if (font == NULL)
			{
				std::cerr << "TTF_OpenFont() Failed: " << TTF_GetError() << std::endl;
				TTF_Quit();
				return;
			}
			
			SDL_Color text_color = { 255, 255, 255 };
			SDL_Surface *buttonText = TTF_RenderText_Solid(font,
				buttons_[i]->get_text(),
				text_color);

			if (buttonText == NULL)
			{
				std::cerr << "TTF_RenderText_Solid() Failed: " << TTF_GetError() << std::endl;
				TTF_Quit();
				return;
			}

			SDL_BlitSurface(buttonText, &buttons_[i]->getModel()->clip_rect, windowSurface_, &buttons_[i]->getBounds());
		}

		SDL_UpdateWindowSurface(window_);
	}
}

MenuPage::~MenuPage()
{
}